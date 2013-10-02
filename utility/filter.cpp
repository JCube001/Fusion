#include "filter.h"

Filter::Filter(void) {
  this->accelData[0] = 0;
  this->accelData[1] = 0;
  this->accelData[2] = 0;
  
  this->compassData[0] = 0;
  this->compassData[1] = 0;
  this->compassData[2] = 0;
  
  this->gyroData[0] = 0;
  this->gyroData[1] = 0;
  this->gyroData[2] = 0;
}

void Filter::setAccelXYZ(const float x, const float y, const float z) {
  this->accelData[0] = x;
  this->accelData[1] = y;
  this->accelData[2] = z;
}

void Filter::setCompassXYZ(const float x, const float y, const float z) {
  this->compassData[0] = x;
  this->compassData[1] = y;
  this->compassData[2] = z;
}

void Filter::setGyroXYZ(const float x, const float y, const float z) {
  this->gyroData[0] = x;
  this->gyroData[1] = y;
  this->gyroData[2] = z;
}
