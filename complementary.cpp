#include "complementary.h"

ComplementaryFilter::ComplementaryFilter(void)
  : angle{0, 0, 0},
    _alpha(0),
    _deltaTime(0)
{
}

void ComplementaryFilter::setAlpha(const float a) {
  if (a >= 0 && a <= 1)
    this->_alpha = a;
}

void ComplementaryFilter::setDeltaTime(const float dt) {
  if (dt > 0)
    this->_deltaTime = dt;
  else
    this->_deltaTime = 0;
}

void ComplementaryFilter::process(void) {
  float rollAcc, pitchAcc;
  float yawHeading;
  
  // Accumulate the change in gyroscope position
  this->angle.roll += this->_gyroData[0] * this->_deltaTime;
  this->angle.pitch += this->_gyroData[1] * this->_deltaTime;
  this->angle.yaw += this->_gyroData[2] * this->_deltaTime;
  
  // Turning around the Y axis results in a vector on the X axis
  rollAcc = atan2(this->_accelData[1], this->_accelData[2]) * RAD_TO_DEG;
  this->angle.roll = (this->angle.roll * this->_alpha) + (rollAcc * (1 - this->_alpha));
  
  // Turning around the X axis results in a vector on the Y axis
  pitchAcc = atan2(this->_accelData[0], this->_accelData[2]) * RAD_TO_DEG;
  this->angle.pitch = (this->angle.pitch * this->_alpha) + (pitchAcc * (1 - this->_alpha));
  
  // Angle of the vector y,x is the compass heading
  yawHeading = atan2(this->_compassData[1], this->_compassData[0]) * RAD_TO_DEG;
  this->angle.yaw = (this->angle.yaw * this->_alpha) + (yawHeading * (1 - this->_alpha));
}
