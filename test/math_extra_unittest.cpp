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

#include <gtest/gtest.h>
#include <cmath>
#include "../utility/math_extra.h"

TEST(MathExtraTest, InverseSquareRoot) {
  float base_1 = 1.0f / sqrt(16.0f);
  float r_1 = invSqrt(16.0f);

  float base_2 = 1.0f / sqrt(37.0f);
  float r_2 = invSqrt(37.0f);

  EXPECT_NEAR(base_1, r_1, 1.0e-3f);
  EXPECT_NEAR(base_2, r_2, 1.0e-3f);
}
