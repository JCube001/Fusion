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

#include "./complementary.h"

ComplementaryFilter::ComplementaryFilter(void)
  : Filter(),
    data {0.0f, 0.0f, 0.0f, 0.0f},
    _alpha(0.0f),
    _deltaTime(0.0f) {}

ComplementaryFilter::ComplementaryFilter(const DOF d, const float a)
  : Filter(d),
    data {0.0f, 0.0f, 0.0f, 0.0f},
    _alpha(a),
    _deltaTime(0.0f) {}

ComplementaryFilter::~ComplementaryFilter() {}

void ComplementaryFilter::alpha(const float a) {
  if (0.0f <= a && a <= 1.0f) {
    _alpha = a;
  }
}

void ComplementaryFilter::deltaTime(const float dt) {
  if (dt > 0.0f) {
    _deltaTime = dt;
  } else {
    _deltaTime = 0.0f;
  }
}

// TODO(JCube001): Redo with quaternions.
void ComplementaryFilter::process() {
  Vector3 estimated_direction, measured_direction, half_error;
  Quaternion temporary_quaternion;
  
  // If the delta time is zero, then do nothing.
  if (_deltaTime == 0.0f) {
    return;
  }

  if (_dof == 9DOF &&
      magnetometer_data.x() != 0.0f &&
      magnetometer_data.y() != 0.0f &&
      magnetometer_data.z() != 0.0f) {
    // Normalize the magnetometer measurement.
    measured_direction = _magnetometerData.normalize();

    // Reference the direction of Earth's magnetic field.

    // Estimate the direction of Earth's magnetic field.

    // The error is the sum of the cross product between the estimated and the
    // measured direction of field vectors.
    half_error += estimated_direction * measured_direction;
  }

  if (accelerometer_data.x() != 0.0f &&
      accelerometer_data.y() != 0.0f &&
      accelerometer_data.z() != 0.0f) {
    // TODO(JCube001): Weigh accelerometer.
  }

  if (gyroscope_data.x() != 0.0f &&
      gyroscope_data.y() != 0.0f &&
      gyroscope_data.z() != 0.0f) {
    // TODO(JCube001): Weigh gyroscope.
  }

// Old code.
#if 0
  float rollAcc, pitchAcc;
  float yawHeading;

  // Accumulate the change in gyroscope position
  this->angle.roll += this->_gyroData[0] * this->_deltaTime;
  this->angle.pitch += this->_gyroData[1] * this->_deltaTime;
  this->angle.yaw += this->_gyroData[2] * this->_deltaTime;

  // Turning around the Y axis results in a vector on the X axis
  rollAcc = atan2(this->_accelData[1], this->_accelData[2]) * RAD_TO_DEG;
  this->angle.roll = (this->angle.roll * this->_alpha) +
    (rollAcc * (1 - this->_alpha));

  // Turning around the X axis results in a vector on the Y axis
  pitchAcc = atan2(this->_accelData[0], this->_accelData[2]) * RAD_TO_DEG;
  this->angle.pitch = (this->angle.pitch * this->_alpha) +
    (pitchAcc * (1 - this->_alpha));

  // Angle of the vector y,x is the compass heading
  yawHeading = atan2(this->_compassData[1], this->_compassData[0]) * RAD_TO_DEG;
  this->angle.yaw = (this->angle.yaw * this->_alpha) +
    (yawHeading * (1 - this->_alpha));
#endif
}
