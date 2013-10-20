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
#include "../utility/quaternion.h"
#include "../utility/vector.h"

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

TEST(QuaternionTest, GetVector) {
  const Vector3 v0(1.0f, 2.0f, 3.0f);
  const Quaternion q(v0, 99.99f);
  const Vector3 v1(q.vector());

  EXPECT_FLOAT_EQ(v0.x(), v1.x());
  EXPECT_FLOAT_EQ(v0.y(), v1.y());
  EXPECT_FLOAT_EQ(v0.z(), v1.z());
}

TEST(QuaternionTest, SetVector) {
  const Vector3 v(1.0f, 2.0f, 3.0f);
  Quaternion q;
  q.vector(v);

  EXPECT_FLOAT_EQ(v.x(), q.x());
  EXPECT_FLOAT_EQ(v.y(), q.y());
  EXPECT_FLOAT_EQ(v.z(), q.z());
}

TEST(QuaternionTest, SubscriptOperator) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const float w = 4.0f;
  const Quaternion q(x, y, z, w);

  EXPECT_FLOAT_EQ(x, q[0]);
  EXPECT_FLOAT_EQ(y, q[1]);
  EXPECT_FLOAT_EQ(z, q[2]);
  EXPECT_FLOAT_EQ(w, q[3]);
}

TEST(QuaternionTest, AssignmentOperator) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1 = q0;

  EXPECT_FLOAT_EQ(q0.x(), q1.x());
  EXPECT_FLOAT_EQ(q0.y(), q1.y());
  EXPECT_FLOAT_EQ(q0.z(), q1.z());
  EXPECT_FLOAT_EQ(q0.w(), q1.w());
}

TEST(QuaternionTest, UnaryNegationOperator) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(-q0);

  EXPECT_FLOAT_EQ(-q0.x(), q1.x());
  EXPECT_FLOAT_EQ(-q0.y(), q1.y());
  EXPECT_FLOAT_EQ(-q0.z(), q1.z());
  EXPECT_FLOAT_EQ(-q0.w(), q1.w());
}

TEST(QuaternionTest, AdditionOperator) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(5.0f, 6.0f, 7.0f, 8.0f);
  const Quaternion q2 = q0 + q1;

  EXPECT_FLOAT_EQ(6.0f, q2.x());
  EXPECT_FLOAT_EQ(8.0f, q2.y());
  EXPECT_FLOAT_EQ(10.0f, q2.z());
  EXPECT_FLOAT_EQ(12.0f, q2.w());
}

TEST(QuaternionTest, SubtractionOperator) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(5.0f, 6.0f, 7.0f, 8.0f);
  const Quaternion q2 = q1 - q0;

  EXPECT_FLOAT_EQ(4.0f, q2.x());
  EXPECT_FLOAT_EQ(4.0f, q2.y());
  EXPECT_FLOAT_EQ(4.0f, q2.z());
  EXPECT_FLOAT_EQ(4.0f, q2.w());
}

TEST(QuaternionTest, QuaternionMultiplicationOperator) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(5.0f, 6.0f, 7.0f, 8.0f);
  const Quaternion q2 = q0 * q1;

  EXPECT_FLOAT_EQ(24.0f, q2.x());
  EXPECT_FLOAT_EQ(48.0f, q2.y());
  EXPECT_FLOAT_EQ(48.0f, q2.z());
  EXPECT_FLOAT_EQ(-6.0f, q2.w());
}

TEST(QuaternionTest, ScalarMultiplicationOperator) {
  const float s = 2.0f;
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1 = q0 * s;

  EXPECT_FLOAT_EQ(2.0f, q1.x());
  EXPECT_FLOAT_EQ(4.0f, q1.y());
  EXPECT_FLOAT_EQ(6.0f, q1.z());
  EXPECT_FLOAT_EQ(8.0f, q1.w());
}

TEST(QuaternionTest, QuaternionDivisionOperator) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(5.0f, 6.0f, 7.0f, 8.0f);
  const Quaternion q2 = q1 / q0;
  const Quaternion q3 = q1 * q0.inverse();

  EXPECT_FLOAT_EQ(q3.x(), q2.x());
  EXPECT_FLOAT_EQ(q3.y(), q2.y());
  EXPECT_FLOAT_EQ(q3.z(), q2.z());
  EXPECT_FLOAT_EQ(q3.w(), q2.w());
}

TEST(QuaternionTest, ScalarDivisionOperator) {
  const float s = 2.0f;
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1 = q0 / s;

  EXPECT_FLOAT_EQ(0.5f, q1.x());
  EXPECT_FLOAT_EQ(1.0f, q1.y());
  EXPECT_FLOAT_EQ(1.5f, q1.z());
  EXPECT_FLOAT_EQ(2.0f, q1.w());
}

TEST(QuaternionTest, EqualToOperator) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const float w = 4.0f;
  const Quaternion q0(x, y, z, w);
  const Quaternion q1(x, y, z, w);
  const Quaternion q2(x, y, 99.99f, w);

  EXPECT_TRUE(q0 == q1);
  EXPECT_FALSE(q0 == q2);
}

TEST(QuaternionTest, NotEqualToOperator) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const float w = 4.0f;
  const Quaternion q0(x, y, z, w);
  const Quaternion q1(x, y, z, w);
  const Quaternion q2(x, y, 99.99f, w);

  EXPECT_TRUE(q0 != q2);
  EXPECT_FALSE(q0 != q1);
}

TEST(QuaternionTest, Conjugate) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const float w = 4.0f;
  const Quaternion q0(x, y, z, w);
  const Quaternion q1 = q0.conjugate();

  EXPECT_FLOAT_EQ(-x, q1.x());
  EXPECT_FLOAT_EQ(-y, q1.y());
  EXPECT_FLOAT_EQ(-z, q1.z());
  EXPECT_FLOAT_EQ(w, q1.w());
}

TEST(QuaternionTest, ConvertFromEulerAngles) {
  const float DEG_TO_RAD = static_cast<float>(M_PI / 180.0f);
  const float roll = 10.0f * DEG_TO_RAD;
  const float pitch = 25.0f * DEG_TO_RAD;
  const float yaw = 50.0f * DEG_TO_RAD;
  const Quaternion q = Quaternion::convertFromEulerAngles(roll, pitch, yaw);

  EXPECT_FLOAT_EQ(-0.01400572f, q.x());
  EXPECT_FLOAT_EQ(0.23137496f, q.y());
  EXPECT_FLOAT_EQ(0.39393390f, q.z());
  EXPECT_FLOAT_EQ(0.88942990f, q.w());
}

TEST(QuaternionTest, ConvertToEulerAngles) {
  const float DEG_TO_RAD = static_cast<float>(M_PI / 180.0f);
  const float roll = 10.0f * DEG_TO_RAD;
  const float pitch = 25.0f * DEG_TO_RAD;
  const float yaw = 50.0f * DEG_TO_RAD;
  const Quaternion q(-0.01400572f, 0.23137496f, 0.39393390f, 0.88942990f);
  const float* e = Quaternion::convertToEulerAngles(q);

  EXPECT_FLOAT_EQ(roll, e[0]);
  EXPECT_FLOAT_EQ(pitch, e[1]);
  EXPECT_FLOAT_EQ(yaw, e[2]);
}

TEST(QuaternionTest, DotProductMultiplication) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(5.0f, 6.0f, 7.0f, 8.0f);

  EXPECT_FLOAT_EQ(70.0f, Quaternion::dot(q0, q1));
  EXPECT_FLOAT_EQ(70.0f, Quaternion::dot(q1, q0));
}

TEST(QuaternionTest, Identity) {
  const Quaternion q = Quaternion::identity();

  EXPECT_FLOAT_EQ(0.0f, q.x());
  EXPECT_FLOAT_EQ(0.0f, q.y());
  EXPECT_FLOAT_EQ(0.0f, q.z());
  EXPECT_FLOAT_EQ(1.0f, q.w());
}

TEST(QuaternionTest, Inverse) {
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1 = q0.inverse();

  EXPECT_FLOAT_EQ(-1.0f / 30.0f, q1.x());
  EXPECT_FLOAT_EQ(-1.0f / 15.0f, q1.y());
  EXPECT_FLOAT_EQ(-1.0f / 10.0f, q1.z());
  EXPECT_FLOAT_EQ(2.0f / 15.0f, q1.w());
}

TEST(QuaternionTest, Lerp) {
  const float t0 = 0.0f;
  const float t1 = 0.5f;
  const float t2 = 1.0f;
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(5.0f, 6.0f, 7.0f, 8.0f);
  const Quaternion q2(3.0f, 4.0f, 5.0f, 6.0f);
  const Quaternion q3(Quaternion::lerp(q0, q1, t0));
  const Quaternion q4(Quaternion::lerp(q0, q1, t1));
  const Quaternion q5(Quaternion::lerp(q0, q1, t2));

  EXPECT_FLOAT_EQ(q0.x(), q3.x());
  EXPECT_FLOAT_EQ(q0.y(), q3.y());
  EXPECT_FLOAT_EQ(q0.z(), q3.z());
  EXPECT_FLOAT_EQ(q0.w(), q3.w());

  EXPECT_FLOAT_EQ(q2.x(), q4.x());
  EXPECT_FLOAT_EQ(q2.y(), q4.y());
  EXPECT_FLOAT_EQ(q2.z(), q4.z());
  EXPECT_FLOAT_EQ(q2.w(), q4.w());

  EXPECT_FLOAT_EQ(q1.x(), q5.x());
  EXPECT_FLOAT_EQ(q1.y(), q5.y());
  EXPECT_FLOAT_EQ(q1.z(), q5.z());
  EXPECT_FLOAT_EQ(q1.w(), q5.w());
}

TEST(QuaternionTest, Nlerp) {
  const float t0 = 0.0f;
  const float t1 = 0.5f;
  const float t2 = 1.0f;
  const float q0_norm = static_cast<float>(sqrt(30.0f));
  const float q1_norm = static_cast<float>(sqrt(174.0f));
  const float q2_norm = static_cast<float>(sqrt(86.0f));
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(5.0f, 6.0f, 7.0f, 8.0f);
  const Quaternion q2(3.0f, 4.0f, 5.0f, 6.0f);
  const Quaternion q3(Quaternion::nlerp(q0, q1, t0));
  const Quaternion q4(Quaternion::nlerp(q0, q1, t1));
  const Quaternion q5(Quaternion::nlerp(q0, q1, t2));

  EXPECT_FLOAT_EQ(q0.x() / q0_norm, q3.x());
  EXPECT_FLOAT_EQ(q0.y() / q0_norm, q3.y());
  EXPECT_FLOAT_EQ(q0.z() / q0_norm, q3.z());
  EXPECT_FLOAT_EQ(q0.w() / q0_norm, q3.w());

  EXPECT_FLOAT_EQ(q2.x() / q2_norm, q4.x());
  EXPECT_FLOAT_EQ(q2.y() / q2_norm, q4.y());
  EXPECT_FLOAT_EQ(q2.z() / q2_norm, q4.z());
  EXPECT_FLOAT_EQ(q2.w() / q2_norm, q4.w());

  EXPECT_FLOAT_EQ(q1.x() / q1_norm, q5.x());
  EXPECT_FLOAT_EQ(q1.y() / q1_norm, q5.y());
  EXPECT_FLOAT_EQ(q1.z() / q1_norm, q5.z());
  EXPECT_FLOAT_EQ(q1.w() / q1_norm, q5.w());
}

TEST(QuaternionTest, Norm) {
  const Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);

  EXPECT_FLOAT_EQ(static_cast<float>(sqrt(30.0f)), q.norm());
}

TEST(QuaternionTest, Normalize) {
  const float q0_norm = static_cast<float>(sqrt(30.0f));
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(q0.normalize());

  EXPECT_FLOAT_EQ(q0.x() / q0_norm, q1.x());
  EXPECT_FLOAT_EQ(q0.y() / q0_norm, q1.y());
  EXPECT_FLOAT_EQ(q0.z() / q0_norm, q1.z());
  EXPECT_FLOAT_EQ(q0.w() / q0_norm, q1.w());
}

TEST(QuaternionTest, RotateVector) {
  const Vector3 v0(1.0f, 0.0f, 0.0f);
  const Quaternion q(0.7071068f, 0.0f, 0.7071068f, 0.0f);
  const Vector3 v1 = q.rotateVector(v0);

  EXPECT_FLOAT_EQ(0.0f, v1.x());
  EXPECT_FLOAT_EQ(0.0f, v1.y());
  EXPECT_FLOAT_EQ(1.0f, v1.z());
}

TEST(QuaternionTest, Slerp) {
  const float t0 = 0.0f;
  const float t1 = 0.5f;
  const float t2 = 1.0f;
  const float q0_norm = static_cast<float>(sqrt(30.0f));
  const float q1_norm = static_cast<float>(sqrt(174.0f));
  const Quaternion q0(1.0f, 2.0f, 3.0f, 4.0f);
  const Quaternion q1(5.0f, 6.0f, 7.0f, 8.0f);
  const Quaternion q2(0.28302330f, 0.41323282f, 0.54344235f, 0.67365187f);
  const Quaternion q3(Quaternion::slerp(q0, q1, t0));
  const Quaternion q4(Quaternion::slerp(q0, q1, t1));
  const Quaternion q5(Quaternion::slerp(q0, q1, t2));

  EXPECT_FLOAT_EQ(q0.x() / q0_norm, q3.x());
  EXPECT_FLOAT_EQ(q0.y() / q0_norm, q3.y());
  EXPECT_FLOAT_EQ(q0.z() / q0_norm, q3.z());
  EXPECT_FLOAT_EQ(q0.w() / q0_norm, q3.w());

  EXPECT_FLOAT_EQ(q2.x(), q4.x());
  EXPECT_FLOAT_EQ(q2.y(), q4.y());
  EXPECT_FLOAT_EQ(q2.z(), q4.z());
  EXPECT_FLOAT_EQ(q2.w(), q4.w());

  EXPECT_FLOAT_EQ(q1.x() / q1_norm, q5.x());
  EXPECT_FLOAT_EQ(q1.y() / q1_norm, q5.y());
  EXPECT_FLOAT_EQ(q1.z() / q1_norm, q5.z());
  EXPECT_FLOAT_EQ(q1.w() / q1_norm, q5.w());
}

TEST(QuaternionTest, Squad) {
  FAIL() << "Test not yet implemented";
}
