/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2013 JCube001

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

#include "complementary.h"

namespace fusion {

ComplementaryFilter::ComplementaryFilter()
  : Filter(),
    beta_(sqrt(3.0f / 4.0f)),
    zeta_(0.0f),
    delta_time_(0.0f),
    Eb_hat_(Quaternion(0.0f, 1.0f, 0.0f, 0.0f)),
    SEq_hat_(Quaternion::identity()) {}

ComplementaryFilter::~ComplementaryFilter() {}

void ComplementaryFilter::deltaTime(float dt) {
  if (dt > 0.0f) {
    delta_time_ = dt;
  } else {
    delta_time_ = 0.0f;
  }
}

void ComplementaryFilter::update() {
  float J_g[3][4];    // Accelerometer objective function's Jacobian matrix.
  float J_b[3][4];    // Magnetometer objective function's Jacobian matrix.
  Quaternion Sw;      // Gyroscope measurements in rad/s.
  Quaternion Sa_hat;  // Accelerometer measurements in sensor frame.
  Quaternion Sm_hat;  // Magnetometer measurements in sensor frame.
  Quaternion Eh_hat;  // Computed flux in the earth frame.
  Quaternion f_g;     // Result of the accelerometer objective function.
  Quaternion f_b;     // Result of the magnetometer objective function.
  Quaternion SEq_dot_omega;  // Quaternion rate from gyroscope elements.
  Quaternion SEq_hat_dot;    // Estimated direction of gyroscope error.

  // Check for a valid sample rate value and that we at least have IMU sensor
  // readings.
  if (delta_time_ <= 0.0f || !hasData(gyroscope_data_) ||
      !hasData(accelerometer_data_)) {
    return;
  }

  // Auxilliary variables to avoid redundant arithematic/function calls.
  bool has_magnetometer_data = hasData(magnetometer_data_);
  Quaternion two_SEq = SEq_hat_ * 2.0f;

  // Normalize the accelerometer measurements.
  Sa_hat = Quaternion(0.0f, accelerometer_data_).fastNormalize();

  // Compute the objective function.
  f_g = SEq_hat_.conjugate() * Eg_hat_ * SEq_hat_ - Sa_hat;

  // Compute the Jacobian matrix.
  J_g[0][0] = -two_SEq.y();
  J_g[0][1] = two_SEq.z();
  J_g[0][2] = -two_SEq.w();
  J_g[0][3] = two_SEq.x();
  J_g[1][0] = two_SEq.x();
  J_g[1][1] = two_SEq.w();
  J_g[1][2] = two_SEq.z();
  J_g[1][3] = two_SEq.y();
  J_g[2][0] = 0.0f;
  J_g[2][1] = -2.0f * two_SEq.x();
  J_g[2][2] = -2.0f * two_SEq.y();
  J_g[2][3] = 0.0f;

  // Use the magnetometer if it is available (MARG).
  if (has_magnetometer_data) {
    // Auxilliary variables to avoid redundant arithematic/function calls.
    Quaternion two_Eb_x_SEq = two_SEq * Eb_hat_.x();
    Quaternion two_Eb_z_SEq = two_SEq * Eb_hat_.z();

    // Normalize the magnetometer measurements.
    Sm_hat = Quaternion(0.0f, magnetometer_data_).fastNormalize();

    // Compute the objective function.
    f_b = SEq_hat_.conjugate() * Eb_hat_ * SEq_hat_ - Sm_hat;

    // Compute the Jacobian matrix.
    J_b[0][0] = -two_Eb_z_SEq.y();
    J_b[0][1] = two_Eb_z_SEq.z();
    J_b[0][2] = -2.0f * two_Eb_x_SEq.y() - two_Eb_z_SEq.w();
    J_b[0][3] = -2.0f * two_Eb_x_SEq.z() + two_Eb_z_SEq.x();
    J_b[1][0] = -two_Eb_x_SEq.z() + two_Eb_z_SEq.x();
    J_b[1][1] = two_Eb_x_SEq.y() + two_Eb_z_SEq.w();
    J_b[1][2] = two_Eb_x_SEq.x() + two_Eb_z_SEq.z();
    J_b[1][3] = -two_Eb_x_SEq.w() + two_Eb_z_SEq.y();
    J_b[2][0] = two_Eb_x_SEq.y();
    J_b[2][1] = two_Eb_x_SEq.z() - 2.0f * two_Eb_z_SEq.x();
    J_b[2][2] = two_Eb_x_SEq.w() - 2.0f * two_Eb_z_SEq.y();
    J_b[2][3] = two_Eb_x_SEq.x();

    // Compute the gradient (matrix multiplication: JT_gb * f_gb)
    SEq_hat_dot = Quaternion();  // TODO(JCube001): Finish
  } else {
    // Compute the gradient (matrix multiplication: JT_g * f_g)
    SEq_hat_dot =
      Quaternion(J_g[0][0]*f_g[1] + J_g[1][0]*f_g[2] + J_g[2][0]*f_g[3],
                 J_g[0][1]*f_g[1] + J_g[1][1]*f_g[2] + J_g[2][1]*f_g[3],
                 J_g[0][2]*f_g[1] + J_g[1][2]*f_g[2] + J_g[2][2]*f_g[3],
                 J_g[0][3]*f_g[1] + J_g[1][3]*f_g[2] + J_g[2][3]*f_g[3]);
  }

  // Normalize the gradient to estimate the direction of gyroscope error.
  SEq_hat_dot = SEq_hat_dot.fastNormalize();

  // Set the gyroscope measurements.
  Sw = Quaternion(0.0f, gyroscope_data_);

  if (has_magnetometer_data) {
    // Compute angular estimated direction of gyroscope error.

    // Compute and remove the gyroscope bias.
  }

  // Compute the quaternion rate measured by the gyroscope.
  SEq_dot_omega = (SEq_hat_ * Sw) * 0.5f;

  // Compute then integrate the estimated quaternion rate.
  SEq_hat_ += (SEq_dot_omega - (SEq_hat_dot*beta_)) * delta_time_;

  // Normalize the quaternion.
  SEq_hat_ = SEq_hat_.fastNormalize();

  // Set orientation to the current quaternion estimate.
  orientation = SEq_hat_;

  if (has_magnetometer_data) {
    // Compute magnetic flux in the earth frame.
    Eh_hat = SEq_hat_ * Sm_hat * SEq_hat_.conjugate();

    // Normalize the flux vector to have only x and z components.
    Eb_hat_ = Quaternion(0.0f,
      sqrt(Eh_hat.x()*Eh_hat.x() + Eh_hat.y()*Eh_hat.y()), 0.0f, Eh_hat.z());
  }
}

}  // namespace fusion
