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

#include "../complementary.h"
#include <gtest/gtest.h>

class ComplementaryFilterTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    f0.setSampleRate(1.0f);
    f0.setAccelerometer(0.0f, 0.0f, 0.0f);
    f0.setGyroscope(0.0f, 0.0f, 0.0f);
    f0.setMagnetometer(0.0f, 0.0f, 0.0f);
  }

  virtual void TearDown() {
  }

  fusion::ComplementaryFilter f0;
};

/**
 * @brief Test that updating on no data yields no rotation (the identity).
 */
TEST_F(ComplementaryFilterTest, NoData) {
  f0.update();

  ASSERT_FLOAT_EQ(1.0f, f0.orientation.w());
  ASSERT_FLOAT_EQ(0.0f, f0.orientation.x());
  ASSERT_FLOAT_EQ(0.0f, f0.orientation.y());
  ASSERT_FLOAT_EQ(0.0f, f0.orientation.z());
}

/**
 * @brief Test control flow is valid for when no magnetometer data is set.
 */
TEST_F(ComplementaryFilterTest, UpdateWithoutMagnetometer) {
  f0.setAccelerometer(0.0f, 0.0f, 9.82f);  // Gravity.
  f0.setGyroscope(0.0f, 0.0f, 1.570796f);  // 90 degrees in radians.
  f0.update();

  // Expected output is a 90 degree rotation about the z-axis.
  EXPECT_NEAR(-0.7071f, f0.orientation.w(), 1.0e-3f) <<
    "W: " << f0.orientation.w();
  EXPECT_FLOAT_EQ(0.0f, f0.orientation.x()) << "X: " << f0.orientation.x();
  EXPECT_FLOAT_EQ(0.0f, f0.orientation.y()) << "Y: " << f0.orientation.y();
  EXPECT_NEAR(-0.7071f, f0.orientation.z(), 1.0e-3f) <<
    "Z: " << f0.orientation.z();
}

/**
 * @brief Test control flow is valid when magnetometer data is set.
 */
TEST_F(ComplementaryFilterTest, DISABLED_UpdateWithMagnetometer) {
  // TODO(JCube001): Implement
}
