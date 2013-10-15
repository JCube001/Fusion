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

#include "./filter.h"

Filter::Filter(void)
  : _accelData {0, 0, 0},
    _compassData {0, 0, 0},
    _gyroData {0, 0, 0} {}

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
