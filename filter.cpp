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

#include "filter.h"

namespace fusion {

Filter::Filter()
  : orientation(Quaternion::identity()),
    accelerometer_data_(Vector3(0.0f, 0.0f, 0.0f)),
    gyroscope_data_(Vector3(0.0f, 0.0f, 0.0f)),
    magnetometer_data_(Vector3(0.0f, 0.0f, 0.0f)) {}

Filter::~Filter() {}

void Filter::accelerometer(const float x, const float y, const float z) {
  accelerometer_data_ = Vector3(x, y, z);
}

void Filter::gyroscope(const float x, const float y, const float z) {
  gyroscope_data_ = Vector3(x, y, z);
}

void Filter::magnetometer(const float x, const float y, const float z) {
  magnetometer_data_ = Vector3(x, y, z);
}

bool Filter::hasData(Vector3& data) {
  if (data != Vector3(0.0f, 0.0f, 0.0f)) {
    return true;
  }
  
  return false;
}

}  // namespace fusion
