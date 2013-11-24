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

ComplementaryFilter::ComplementaryFilter() {
  // Filter
  orientation = Quaternion::identity();
  accelerometer_data_ = Vector3(0.0f, 0.0f, 0.0f);
  gyroscope_data_ = Vector3(0.0f, 0.0f, 0.0f);
  magnetometer_data_ = Vector3(0.0f, 0.0f, 0.0f);

  // ComplementaryFilter
  beta_ = 1.0f;
  zeta_ = 1.0f;
  delta_time_ = 0.0f;
  Eb_hat_ = Quaternion(0.0f, 1.0f, 0.0f, 0.0f);
  SEq_hat_ = Quaternion::identity();
  
  // Testing
  k_i_ = 0.0f;
  k_p_ = 1.0f;
  e_i_ = Vector3(0.0f, 0.0f, 0.0f);
  q_ = Quaternion::identity();
}

ComplementaryFilter::~ComplementaryFilter() {}

void ComplementaryFilter::setSampleRate(float rate) {
  if (rate > 0.0f) {
    delta_time_ = rate;
  } else {
    delta_time_ = 0.0f;
  }
}

void ComplementaryFilter::setGyroscopeError(float error) {
  beta_ = sqrt(3.0f / 4.0f) * error;
}

void ComplementaryFilter::setGyroscopeDrift(float drift) {
  zeta_ = sqrt(3.0f / 4.0f) * drift;
}

void ComplementaryFilter::update() {
  const Quaternion Eg_hat_ = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);  // Gravity.
  float J_g[3][4];    // Accelerometer objective function's Jacobian matrix.
  float J_b[3][4];    // Magnetometer objective function's Jacobian matrix.
  Quaternion Sw;      // Gyroscope measurements in rad/s.
  Quaternion Sw_err;  // Angular estimated direction of gyroscope error.
  Quaternion Sw_b;    // The gyroscope biases.
  Quaternion Sa_hat;  // Accelerometer measurements in sensor frame.
  Quaternion Sm_hat;  // Magnetometer measurements in sensor frame.
  Quaternion Eh_hat;  // Computed flux in the earth frame.
  Quaternion f_g;     // Result of the accelerometer objective function.
  Quaternion f_b;     // Result of the magnetometer objective function.
  Quaternion gradient_b;     // The gradient descent of magnetometer data.
  Quaternion SEq_dot_omega;  // Quaternion rate from gyroscope elements.
  Quaternion SEq_hat_dot;    // Estimated direction of gyroscope error.

  // Check for a valid sample rate value and that we at least have IMU sensor
  // readings.
  if (delta_time_ <= 0.0f || !hasData(gyroscope_data_) ||
      !hasData(accelerometer_data_)) {
    return;
  }

  // Auxiliary variables to avoid redundant arithmetic/function calls.
  bool has_magnetometer_data = hasData(magnetometer_data_);
  Quaternion two_SEq = 2.0f * SEq_hat_;

  // Normalize the accelerometer measurements.
  Sa_hat = Quaternion(0.0f, accelerometer_data_).fastNormalized();

  // Compute the objective function.
  f_g = SEq_hat_.conjugated() * Eg_hat_ * SEq_hat_ - Sa_hat;

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

  // Compute the gradient (matrix multiplication: JT_g * f_g).
  SEq_hat_dot =
    Quaternion(J_g[0][0]*f_g[1] + J_g[1][0]*f_g[2] + J_g[2][0]*f_g[3],
               J_g[0][1]*f_g[1] + J_g[1][1]*f_g[2] + J_g[2][1]*f_g[3],
               J_g[0][2]*f_g[1] + J_g[1][2]*f_g[2] + J_g[2][2]*f_g[3],
               J_g[0][3]*f_g[1] + J_g[1][3]*f_g[2] + J_g[2][3]*f_g[3]);

  // Use the magnetometer if it is available (MARG).
  if (has_magnetometer_data) {
    // Auxiliary variables to avoid redundant arithmetic/function calls.
    Quaternion two_Eb_x_SEq = two_SEq * Eb_hat_.x();
    Quaternion two_Eb_z_SEq = two_SEq * Eb_hat_.z();

    // Normalize the magnetometer measurements.
    Sm_hat = Quaternion(0.0f, magnetometer_data_).fastNormalized();

    // Compute the objective function.
    f_b = SEq_hat_.conjugated() * Eb_hat_ * SEq_hat_ - Sm_hat;

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

    // Compute the gradient (matrix multiplication: JT_b * f_b).
    gradient_b =
      Quaternion(J_b[0][0]*f_b[1] + J_b[1][0]*f_b[2] + J_b[2][0]*f_b[3],
                 J_b[0][1]*f_b[1] + J_b[1][1]*f_b[2] + J_b[2][1]*f_b[3],
                 J_b[0][2]*f_b[1] + J_b[1][2]*f_b[2] + J_b[2][2]*f_b[3],
                 J_b[0][3]*f_b[1] + J_b[1][3]*f_b[2] + J_b[2][3]*f_b[3]);

    // Compute the gradient (matrix multiplication: JT_gb * f_gb).
    SEq_hat_dot += gradient_b;
  }

  // Normalize the gradient to estimate the direction of gyroscope error.
  SEq_hat_dot.fastNormalize();

  // Set the gyroscope measurements.
  Sw = Quaternion(0.0f, gyroscope_data_);

  // Compute angular estimated direction of gyroscope error.
  Sw_err = two_SEq.conjugated() * SEq_hat_dot;

  // Compute and remove the gyroscope biases.
  Sw_b += Sw_err * delta_time_ * zeta_;
  Sw -= Sw_b;

  // Compute the quaternion rate measured by the gyroscope.
  SEq_dot_omega = 0.5f * SEq_hat_ * Sw;

  // Compute then integrate the estimated quaternion rate.
  SEq_hat_ += (SEq_dot_omega - (SEq_hat_dot*beta_)) * delta_time_;

  // Normalize the quaternion.
  SEq_hat_.fastNormalize();

  // Set orientation to the current quaternion estimate.
  orientation = SEq_hat_;

  if (has_magnetometer_data) {
    // Compute magnetic flux in the earth frame.
    Eh_hat = SEq_hat_ * Sm_hat * SEq_hat_.conjugated();

    // Normalize the flux vector to have only x and z components.
    Eb_hat_ = Quaternion(0.0f,
      sqrt(Eh_hat.x()*Eh_hat.x() + Eh_hat.y()*Eh_hat.y()), 0.0f, Eh_hat.z());
  }
}


// Testing below this point

void ComplementaryFilter::setIntegralGain(float k_i) {
  k_i_ = k_i;
}

void ComplementaryFilter::setProportionalGain(float k_p) {
  k_p_ = k_p;
}

void ComplementaryFilter::update_mahony() {
  // Short name local variables.
  Vector3 a = accelerometer_data_;
  Vector3 g = gyroscope_data_;
  Vector3 m = magnetometer_data_;

  // Auxiliary variables to avoid redundant arithematic.
  float q1q1 = q_.w() * q_.w();
  float q1q2 = q_.w() * q_.x();
  float q1q3 = q_.w() * q_.y();
  float q1q4 = q_.w() * q_.z();

  float q2q2 = q_.x() * q_.x();
  float q2q3 = q_.x() * q_.y();
  float q2q4 = q_.x() * q_.z();

  float q3q3 = q_.y() * q_.y();
  float q3q4 = q_.y() * q_.z();

  float q4q4 = q_.z() * q_.z();

  // Normalize the accelerometer measurements.
  a.fastNormalize();

  // Noramlize the magnetometer measurements.
  m.fastNormalize();

  // Reference the direction of earth's magnetic field.
  Vector3 h(2.0f*m.x()*(0.5f - q3q3 - q4q4) +
            2.0f*m.y()*(q2q3 - q1q4) +
            2.0f*m.z()*(q2q4 + q1q3),
            2.0f*m.x()*(q2q3 + q1q4) +
            2.0f*m.y()*(0.5f - q2q2 - q4q4) +
            2.0f*m.z()*(q3q4 - q1q2),
            0.0f);

  Vector3 b(sqrt(h.x()*h.x() + h.y()*h.y()),
            0.0f,
            2.0f*m.x()*(q2q4 - q1q3) +
            2.0f*m.y()*(q3q4 + q1q2) +
            2.0f*m.z()*(0.5f - q2q2 - q3q3));

  // Estimate the direction of gravity.
  Vector3 v(2.0f*(q2q4 - q1q3),
            2.0f*(q1q2 + q3q4),
            q1q1 - q2q2 - q3q3 + q4q4);

  // Estimate the direction of earth's magnetic field.
  Vector3 w(2.0f*b.x()*(0.5f - q3q3 - q4q4) +
            2.0f*b.z()*(q2q4 - q1q3),
            2.0f*b.x()*(q2q3 - q1q4) +
            2.0f*b.z()*(q1q2 + q3q4),
            2.0f*b.x()*(q1q3 + q2q4) +
            2.0f*b.z()*(0.5f - q2q2 - q3q3));

  // Compute the error as the cross product between the estimated and measured
  // direction of gravity.
  Vector3 e(a*v + m*w);

  if (k_i_ > 0.0f) {
    e_i_ += e;
  } else {
    e_i_ = Vector3(0.0f, 0.0f, 0.0f);
  }

  // Apply feedback terms to the gyroscope measurements.
  g += k_p_*e + k_i_*e_i_;

  // Integrate the rate of change of the quaternion.
  //q_ += (???) * (0.5f*delta_time_);
  float pa = q_.x();
  float pb = q_.y();
  float pc = q_.z();
  q_ = Quaternion(
    q_.w() + (-q_.y()*g.x() - q_.y()*g.y() - q_.z()*g.z()) * (0.5f*delta_time_),
    pa + (q_.w()*g.x() + pb*g.z() - pc*g.y()) * (0.5f*delta_time_),
    pb + (q_.w()*g.y() - pa*g.z() + pc*g.x()) * (0.5f*delta_time_),
    pc + (q_.w()*g.z() + pa*g.y() - pb*g.x()) * (0.5f*delta_time_));
  

  // Normalize the quaternion.
  q_.fastNormalize();
  
  // Set the output quaternion to the current orientation estimate.
  orientation = q_;
}

}  // namespace fusion
