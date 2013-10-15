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

#ifndef FILTER_H_
#define FILTER_H_

#include <math.h>

#if !defined(_FUSION_TEST)
  #if (ARDUINO >= 100)
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
#else
  #define PI  (M_PI)
#endif

#include "./utility/quaternion.h"

#define RAD_TO_DEG  (180.0f / PI)

class Filter {
 public:
  Filter(void);

  void setAccelXYZ(const float x, const float y, const float z);
  void setCompassXYZ(const float x, const float y, const float z);
  void setGyroXYZ(const float x, const float y, const float z);

  virtual void process(void) = 0;

 protected:
  float _accelData[3];
  float _compassData[3];
  float _gyroData[3];
};

#endif  // FILTER_H_
