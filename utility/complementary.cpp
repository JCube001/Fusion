#include "complementary.h"

ComplementaryFilter::ComplementaryFilter(void) {
  this->angle.roll = 0;
  this->angle.pitch = 0;
  this->angle.yaw = 0;
  
  this->deltaTime = 0;
  this->alpha = 0;
  this->findYaw = false;
}

void ComplementaryFilter::setAlpha(const float a) {
  if (a >= 0 && a <= 1)
    this->alpha = a;
}

void ComplementaryFilter::setDeltaTime(const float dt) {
  if (dt > 0)
    this->deltaTime = dt;
  else
    this->deltaTime = 0;
}

void ComplementaryFilter::process(void) {
  float rollAcc, pitchAcc;
  float yawHeading;
  
  // Accumulate the change in gyroscope position
  this->angle.roll += this->gyroData[0] * this->deltaTime;
  this->angle.pitch += this->gyroData[1] * this->deltaTime;
  this->angle.yaw += this->gyroData[2] * this->deltaTime;
  
  // Turning around the Y axis results in a vector on the X axis
  rollAcc = atan2(this->accelData[1], this->accelData[2]) * RAD_TO_DEG;
  this->angle.roll = (this->angle.roll * this->alpha) + (rollAcc * (1 - this->alpha));
  
  // Turning around the X axis results in a vector on the Y axis
  pitchAcc = atan2(this->accelData[0], this->accelData[2]) * RAD_TO_DEG;
  this->angle.pitch = (this->angle.pitch * this->alpha) + (pitchAcc * (1 - this->alpha));
  
  // Angle of the vector y,x is the compass heading
  yawHeading = atan2(this->compassData[1], this->compassData[0]) * RAD_TO_DEG;
  this->angle.yaw = (this->angle.yaw * this->alpha) + (yawHeading * (1 - this->alpha));
}
