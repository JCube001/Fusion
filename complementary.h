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

#ifndef COMPLEMENTARY_H_
#define COMPLEMENTARY_H_

#include "./filter.h"

class ComplementaryFilter : public Filter {
 public:
  typedef struct eulerAngles_s {
    float roll;
    float pitch;
    float yaw;
  } eulerAngles;

  // Output angles (degrees)
  eulerAngles angle;

  ComplementaryFilter(void);

  void setAlpha(const float a);
  void setDeltaTime(const float dt);

  void process(void);

 protected:
  float _alpha;      // The percentage of gyroscope data to use
  float _deltaTime;  // The time in seconds since the last good sensor reading
};

#endif  // COMPLEMENTARY_H_
