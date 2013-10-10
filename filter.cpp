#include "filter.h"

Filter::Filter(void)
  : _accelData{0, 0, 0},
    _compassData{0, 0, 0},
    _gyroData{0, 0, 0}
{
}

void Filter::setAccelXYZ(const float x, const float y, const float z) {
  this->_accelData[0] = x;
  this->_accelData[1] = y;
  this->_accelData[2] = z;
}

void Filter::setCompassXYZ(const float x, const float y, const float z) {
  this->_compassData[0] = x;
  this->_compassData[1] = y;
  this->_compassData[2] = z;
}

void Filter::setGyroXYZ(const float x, const float y, const float z) {
  this->_gyroData[0] = x;
  this->_gyroData[1] = y;
  this->_gyroData[2] = z;
}
