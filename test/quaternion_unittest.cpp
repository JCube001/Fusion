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

#include "../utility/quaternion.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(QuaternionTest, DefaultConstructor) {
  const Quaternion q;

  EXPECT_FLOAT_EQ(0.0f, q.x());
  EXPECT_FLOAT_EQ(0.0f, q.y());
  EXPECT_FLOAT_EQ(0.0f, q.z());
  EXPECT_FLOAT_EQ(0.0f, q.w());
}

TEST(QuaternionTest, CopyConstructor) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(q0);

  EXPECT_FLOAT_EQ(q0.x(), q1.x());
  EXPECT_FLOAT_EQ(q0.y(), q1.y());
  EXPECT_FLOAT_EQ(q0.z(), q1.z());
  EXPECT_FLOAT_EQ(q0.w(), q1.w());
}

TEST(QuaternionTest, ComponentInitializationConstructor) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const float w = 4.0f;
  const Vector3 v(x, y, z);
  const Quaternion q(v, w);

  EXPECT_FLOAT_EQ(x, q.x());
  EXPECT_FLOAT_EQ(y, q.y());
  EXPECT_FLOAT_EQ(z, q.z());
  EXPECT_FLOAT_EQ(w, q.w());
}

TEST(QuaternionTest, ArrayInitializationConstructor) {
  const float a[] = {1.0f, 2.0f, 3.0f, 4.0f};
  const Quaternion q(a);

  EXPECT_FLOAT_EQ(a[0], q.x());
  EXPECT_FLOAT_EQ(a[1], q.y());
  EXPECT_FLOAT_EQ(a[2], q.z());
  EXPECT_FLOAT_EQ(a[3], q.w());
}

TEST(QuaternionTest, InitializationConstructor) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const float w = 4.0f;
  const Quaternion q(x, y, z, w);

  EXPECT_FLOAT_EQ(x, q.x());
  EXPECT_FLOAT_EQ(y, q.y());
  EXPECT_FLOAT_EQ(z, q.z());
  EXPECT_FLOAT_EQ(w, q.w());
}

TEST(QuaternionTest, GetX) {
  const float x = 1.0f;
  const Quaternion q(x, 99.99f, 99.99f, 99.99f);

  EXPECT_FLOAT_EQ(x, q.x());
}

TEST(QuaternionTest, GetY) {
  const float y = 1.0f;
  const Quaternion q(99.99f, y, 99.99f, 99.99f);

  EXPECT_FLOAT_EQ(y, q.y());
}

TEST(QuaternionTest, GetZ) {
  const float z = 1.0f;
  const Quaternion q(99.99f, 99.99f, z, 99.99f);

  EXPECT_FLOAT_EQ(z, q.z());
}

TEST(QuaternionTest, GetW) {
  const float w = 1.0f;
  const Quaternion q(99.99f, 99.99f, 99.99f, w);

  EXPECT_FLOAT_EQ(w, q.w());
}

TEST(QuaternionTest, GetScalar) {
  const float s = 1.0f;
  const Quaternion q(99.99f, 99.99f, 99.99f, s);

  EXPECT_FLOAT_EQ(s, q.scalar());
}

TEST(QuaternionTest, SetScalar) {
  const float s = 1.0f;
  Quaternion q;
  q.scalar(s);

  EXPECT_FLOAT_EQ(s, q.scalar());
}
