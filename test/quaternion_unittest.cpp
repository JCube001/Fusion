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

class QuaternionTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    q1 = fusion::Quaternion(1.0f, 2.0f, 3.0f, 4.0f);
    q2 = fusion::Quaternion(5.0f, 6.0f, 7.0f, 8.0f);
    q3 = q1;
  }

  virtual void TearDown() {
  }

  void assert_q1_unmodified() {
    ASSERT_FLOAT_EQ(1.0f, q1.w());
    ASSERT_FLOAT_EQ(2.0f, q1.x());
    ASSERT_FLOAT_EQ(3.0f, q1.y());
    ASSERT_FLOAT_EQ(4.0f, q1.z());
  }

  void assert_q2_unmodified() {
    ASSERT_FLOAT_EQ(5.0f, q2.w());
    ASSERT_FLOAT_EQ(6.0f, q2.x());
    ASSERT_FLOAT_EQ(7.0f, q2.y());
    ASSERT_FLOAT_EQ(8.0f, q2.z());
  }

  fusion::Quaternion q0;
  fusion::Quaternion q1;
  fusion::Quaternion q2;
  fusion::Quaternion q3;
};

TEST_F(QuaternionTest, DefaultConstructor) {
  ASSERT_FLOAT_EQ(1.0f, q0.w());
  ASSERT_FLOAT_EQ(0.0f, q0.x());
  ASSERT_FLOAT_EQ(0.0f, q0.y());
  ASSERT_FLOAT_EQ(0.0f, q0.z());
}

TEST_F(QuaternionTest, CopyConstructor) {
  fusion::Quaternion t(q1);

  ASSERT_FLOAT_EQ(q1.w(), t.w());
  ASSERT_FLOAT_EQ(q1.x(), t.x());
  ASSERT_FLOAT_EQ(q1.y(), t.y());
  ASSERT_FLOAT_EQ(q1.z(), t.z());
}

TEST_F(QuaternionTest, ComponentInitializationConstructor) {
  fusion::Vector3 v(200.0f, 300.0f, 400.0f);
  fusion::Quaternion t(100.0f, v);

  ASSERT_FLOAT_EQ(100.0f, t.w());
  ASSERT_FLOAT_EQ(200.0f, t.x());
  ASSERT_FLOAT_EQ(300.0f, t.y());
  ASSERT_FLOAT_EQ(400.0f, t.z());
}

TEST_F(QuaternionTest, ArrayInitializationConstructor) {
  float arr[4] = {100.0f, 200.0f, 300.0f, 400.0f};
  fusion::Quaternion t(arr);

  ASSERT_FLOAT_EQ(100.0f, t.w());
  ASSERT_FLOAT_EQ(200.0f, t.x());
  ASSERT_FLOAT_EQ(300.0f, t.y());
  ASSERT_FLOAT_EQ(400.0f, t.z());
}

TEST_F(QuaternionTest, InitializationConstructor) {
  fusion::Quaternion t(100.0f, 200.0f, 300.0f, 400.0f);

  ASSERT_FLOAT_EQ(100.0f, t.w());
  ASSERT_FLOAT_EQ(200.0f, t.x());
  ASSERT_FLOAT_EQ(300.0f, t.y());
  ASSERT_FLOAT_EQ(400.0f, t.z());
}

TEST_F(QuaternionTest, AccessorMethods) {
  fusion::Vector3 v(2.0f, 3.0f, 4.0f);

  ASSERT_FLOAT_EQ(1.0f, q1.w());
  ASSERT_FLOAT_EQ(2.0f, q1.x());
  ASSERT_FLOAT_EQ(3.0f, q1.y());
  ASSERT_FLOAT_EQ(4.0f, q1.z());

  ASSERT_FLOAT_EQ(1.0f, q1.scalar());
  ASSERT_TRUE(v == q1.vector());
}

TEST_F(QuaternionTest, MutatorMethods) {
  q1.setScalar(100.0f);
  q1.setVector(fusion::Vector3(200.0f, 300.0f, 400.0f));

  ASSERT_FLOAT_EQ(100.0f, q1.w());
  ASSERT_FLOAT_EQ(200.0f, q1.x());
  ASSERT_FLOAT_EQ(300.0f, q1.y());
  ASSERT_FLOAT_EQ(400.0f, q1.z());
}

TEST_F(QuaternionTest, AssignmentOperator) {
  q1 = q2;

  ASSERT_FLOAT_EQ(q2.w(), q1.w());
  ASSERT_FLOAT_EQ(q2.x(), q1.x());
  ASSERT_FLOAT_EQ(q2.y(), q1.y());
  ASSERT_FLOAT_EQ(q2.z(), q1.z());
}

TEST_F(QuaternionTest, SubscriptAccessorOperator) {
  ASSERT_FLOAT_EQ(1.0f, q1[0]);
  ASSERT_FLOAT_EQ(2.0f, q1[1]);
  ASSERT_FLOAT_EQ(3.0f, q1[2]);
  ASSERT_FLOAT_EQ(4.0f, q1[3]);
}

TEST_F(QuaternionTest, SubscriptMutatorOperator) {
  q1[0] = 100.0f;
  q1[1] = 200.0f;
  q1[2] = 300.0f;
  q1[3] = 400.0f;

  ASSERT_FLOAT_EQ(100.0f, q1.w());
  ASSERT_FLOAT_EQ(200.0f, q1.x());
  ASSERT_FLOAT_EQ(300.0f, q1.y());
  ASSERT_FLOAT_EQ(400.0f, q1.z());
}

TEST_F(QuaternionTest, CompoundAdditionOperator) {
  q1 += q2;

  ASSERT_FLOAT_EQ(1.0f + 5.0f, q1.w());
  ASSERT_FLOAT_EQ(2.0f + 6.0f, q1.x());
  ASSERT_FLOAT_EQ(3.0f + 7.0f, q1.y());
  ASSERT_FLOAT_EQ(4.0f + 8.0f, q1.z());

  assert_q2_unmodified();
}

TEST_F(QuaternionTest, CompoundSubtractionOperator) {
  q1 -= q2;

  ASSERT_FLOAT_EQ(1.0f - 5.0f, q1.w());
  ASSERT_FLOAT_EQ(2.0f - 6.0f, q1.x());
  ASSERT_FLOAT_EQ(3.0f - 7.0f, q1.y());
  ASSERT_FLOAT_EQ(4.0f - 8.0f, q1.z());

  assert_q2_unmodified();
}

TEST_F(QuaternionTest, CompoundScalarMultiplicationOperator) {
  q1 *= 2.0f;

  ASSERT_FLOAT_EQ(1.0f * 2.0f, q1.w());
  ASSERT_FLOAT_EQ(2.0f * 2.0f, q1.x());
  ASSERT_FLOAT_EQ(3.0f * 2.0f, q1.y());
  ASSERT_FLOAT_EQ(4.0f * 2.0f, q1.z());
}

TEST_F(QuaternionTest, CompoundQuaternionMultiplicationOperator) {
  q1 *= q2;

  // External result from
  // http://www.wolframalpha.com/input/?i=Quaternion%281%2C+2%2C+3%2C+4%29+*+Quaternion%285%2C+6%2C+7%2C+8%29
  ASSERT_FLOAT_EQ(-60.0f, q1.w());
  ASSERT_FLOAT_EQ(12.0f, q1.x());
  ASSERT_FLOAT_EQ(30.0f, q1.y());
  ASSERT_FLOAT_EQ(24.0f, q1.z());

  assert_q2_unmodified();
}

TEST_F(QuaternionTest, CompoundScalarDivisionOperator) {
  q1 /= 2.0f;

  ASSERT_FLOAT_EQ(1.0f / 2.0f, q1.w());
  ASSERT_FLOAT_EQ(2.0f / 2.0f, q1.x());
  ASSERT_FLOAT_EQ(3.0f / 2.0f, q1.y());
  ASSERT_FLOAT_EQ(4.0f / 2.0f, q1.z());
}

TEST_F(QuaternionTest, CompoundDivisionOperator) {
  q1 /= q2;

  // External result from
  // http://www.wolframalpha.com/input/?i=Quaternion%281%2C+2%2C+3%2C+4%29+*+Quaternion%285%2F174%2C+-1%2F29%2C+-7%2F174%2C+-4%2F87%29
  ASSERT_NEAR(35.0f / 87.0f, q1.w(), 1.0e-3f);
  ASSERT_NEAR(4.0f / 87.0f, q1.x(), 1.0e-3f);
  ASSERT_NEAR(0.0f, q1.y(), 1.0e-3f);
  ASSERT_NEAR(8.0f / 87.0f, q1.z(), 1.0e-3f);

  assert_q2_unmodified();
}

TEST_F(QuaternionTest, QuaternionAdditionOperator) {
  q0 = q1 + q2;

  ASSERT_FLOAT_EQ(1.0f + 5.0f, q0.w());
  ASSERT_FLOAT_EQ(2.0f + 6.0f, q0.x());
  ASSERT_FLOAT_EQ(3.0f + 7.0f, q0.y());
  ASSERT_FLOAT_EQ(4.0f + 8.0f, q0.z());

  assert_q1_unmodified();
  assert_q2_unmodified();
}

TEST_F(QuaternionTest, QuaternionSubtractionOperator) {
  q0 = q1 - q2;

  ASSERT_FLOAT_EQ(1.0f - 5.0f, q0.w());
  ASSERT_FLOAT_EQ(2.0f - 6.0f, q0.x());
  ASSERT_FLOAT_EQ(3.0f - 7.0f, q0.y());
  ASSERT_FLOAT_EQ(4.0f - 8.0f, q0.z());

  assert_q1_unmodified();
  assert_q2_unmodified();
}

TEST_F(QuaternionTest, UnaryNegationOperator) {
  q0 = -q1;

  ASSERT_FLOAT_EQ(-1.0f, q0.w());
  ASSERT_FLOAT_EQ(-2.0f, q0.x());
  ASSERT_FLOAT_EQ(-3.0f, q0.y());
  ASSERT_FLOAT_EQ(-4.0f, q0.z());

  assert_q1_unmodified();
  assert_q2_unmodified();
}

TEST_F(QuaternionTest, ScalarLeftMultiplicationOperator) {
  q0 = 2.0f * q1;

  ASSERT_FLOAT_EQ(2.0f * 1.0f, q0.w());
  ASSERT_FLOAT_EQ(2.0f * 2.0f, q0.x());
  ASSERT_FLOAT_EQ(2.0f * 3.0f, q0.y());
  ASSERT_FLOAT_EQ(2.0f * 4.0f, q0.z());

  assert_q1_unmodified();
}

TEST_F(QuaternionTest, ScalarRightMultiplicationOperator) {
  q0 = q1 * 2.0f;

  ASSERT_FLOAT_EQ(1.0f * 2.0f, q0.w());
  ASSERT_FLOAT_EQ(2.0f * 2.0f, q0.x());
  ASSERT_FLOAT_EQ(3.0f * 2.0f, q0.y());
  ASSERT_FLOAT_EQ(4.0f * 2.0f, q0.z());

  assert_q1_unmodified();
}

TEST_F(QuaternionTest, QuaternionMultiplicationOperator) {
  q0 = q1 * q2;

  // External result from
  // http://www.wolframalpha.com/input/?i=Quaternion%281%2C+2%2C+3%2C+4%29+*+Quaternion%285%2C+6%2C+7%2C+8%29
  ASSERT_FLOAT_EQ(-60.0f, q0.w());
  ASSERT_FLOAT_EQ(12.0f, q0.x());
  ASSERT_FLOAT_EQ(30.0f, q0.y());
  ASSERT_FLOAT_EQ(24.0f, q0.z());

  assert_q1_unmodified();
  assert_q2_unmodified();
}

TEST_F(QuaternionTest, ScalarDivisionOperator) {
  q0 = q1 / 2.0f;

  ASSERT_FLOAT_EQ(1.0f / 2.0f, q0.w());
  ASSERT_FLOAT_EQ(2.0f / 2.0f, q0.x());
  ASSERT_FLOAT_EQ(3.0f / 2.0f, q0.y());
  ASSERT_FLOAT_EQ(4.0f / 2.0f, q0.z());

  assert_q1_unmodified();
}

TEST_F(QuaternionTest, QuaternionDivisionOperator) {
  q0 = q1 / q2;

  // External result from
  // http://www.wolframalpha.com/input/?i=Quaternion%281%2C+2%2C+3%2C+4%29+*+Quaternion%285%2F174%2C+-1%2F29%2C+-7%2F174%2C+-4%2F87%29
  ASSERT_NEAR(35.0f / 87.0f, q0.w(), 1.0e-3f);
  ASSERT_NEAR(4.0f / 87.0f, q0.x(), 1.0e-3f);
  ASSERT_NEAR(0.0f, q0.y(), 1.0e-3f);
  ASSERT_NEAR(8.0f / 87.0f, q0.z(), 1.0e-3f);

  assert_q1_unmodified();
  assert_q2_unmodified();
}

TEST_F(QuaternionTest, EqualToOperator) {
  ASSERT_TRUE(q1 == q3);
  ASSERT_FALSE(q1 == q2);
}

TEST_F(QuaternionTest, NotEqualToOperator) {
  ASSERT_TRUE(q1 != q2);
  ASSERT_FALSE(q1 != q3);
}

TEST_F(QuaternionTest, Conjugate) {
  q1.conjugate();

  ASSERT_FLOAT_EQ(1.0f, q1.w());
  ASSERT_FLOAT_EQ(-2.0f, q1.x());
  ASSERT_FLOAT_EQ(-3.0f, q1.y());
  ASSERT_FLOAT_EQ(-4.0f, q1.z());
}

TEST_F(QuaternionTest, Conjugated) {
  q0 = q1.conjugated();

  ASSERT_FLOAT_EQ(1.0f, q0.w());
  ASSERT_FLOAT_EQ(-2.0f, q0.x());
  ASSERT_FLOAT_EQ(-3.0f, q0.y());
  ASSERT_FLOAT_EQ(-4.0f, q0.z());

  assert_q1_unmodified();
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_ConvertFromAxisAngle) {
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_ConvertFromEulerAngles) {
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_ConvertToAxisAngle) {
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_ConvertToEulerAngles) {
}

TEST_F(QuaternionTest, QuaternionDotProduct) {
  float r = fusion::Quaternion::dot(q1, q2);

  ASSERT_FLOAT_EQ(1.0f*5.0f + 2.0f*6.0f + 3.0f*7.0f + 4.0f*8.0f, r);
}

TEST_F(QuaternionTest, FastNormalize) {
  q1.fastNormalize();

  ASSERT_GE(1.0f, q1.w());
  ASSERT_GE(1.0f, q1.x());
  ASSERT_GE(1.0f, q1.y());
  ASSERT_GE(1.0f, q1.z());

  EXPECT_NEAR(1.0f / sqrt(30.0f), q1.w(), 1.0e-3f);
  EXPECT_NEAR(sqrt(2.0f / 15.0f), q1.x(), 1.0e-3f);
  EXPECT_NEAR(sqrt(3.0f / 10.0f), q1.y(), 1.0e-3f);
  EXPECT_NEAR(2.0f*sqrt(2.0f / 15.0f), q1.z(), 1.0e-3f);
}

TEST_F(QuaternionTest, FastNormalized) {
  q0 = q1.fastNormalized();

  assert_q1_unmodified();

  ASSERT_GE(1.0f, q0.w());
  ASSERT_GE(1.0f, q0.x());
  ASSERT_GE(1.0f, q0.y());
  ASSERT_GE(1.0f, q0.z());

  EXPECT_NEAR(1.0f / sqrt(30.0f), q0.w(), 1.0e-3f);
  EXPECT_NEAR(sqrt(2.0f / 15.0f), q0.x(), 1.0e-3f);
  EXPECT_NEAR(sqrt(3.0f / 10.0f), q0.y(), 1.0e-3f);
  EXPECT_NEAR(2.0f*sqrt(2.0f / 15.0f), q0.z(), 1.0e-3f);
}

TEST_F(QuaternionTest, Identity) {
  fusion::Quaternion t = fusion::Quaternion::identity();

  ASSERT_FLOAT_EQ(1.0f, t.w());
  ASSERT_FLOAT_EQ(0.0f, t.x());
  ASSERT_FLOAT_EQ(0.0f, t.y());
  ASSERT_FLOAT_EQ(0.0f, t.z());
}

TEST_F(QuaternionTest, Inverse) {
  q0 = q1.inverse();

  assert_q1_unmodified();

  EXPECT_NEAR(1.0f / 30.0f, q0.w(), 1.0e-3f);
  EXPECT_NEAR(-1.0f / 15.0f, q0.x(), 1.0e-3f);
  EXPECT_NEAR(-1.0f / 10.0f, q0.y(), 1.0e-3f);
  EXPECT_NEAR(-2.0f / 15.0f, q0.z(), 1.0e-3f);
}

TEST_F(QuaternionTest, Invert) {
  q1.invert();

  EXPECT_NEAR(1.0f / 30.0f, q1.w(), 1.0e-3f);
  EXPECT_NEAR(-1.0f / 15.0f, q1.x(), 1.0e-3f);
  EXPECT_NEAR(-1.0f / 10.0f, q1.y(), 1.0e-3f);
  EXPECT_NEAR(-2.0f / 15.0f, q1.z(), 1.0e-3f);
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_Lerp) {
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_Nlerp) {
}

TEST_F(QuaternionTest, Norm) {
  float r = q1.norm();

  ASSERT_FLOAT_EQ(sqrt(1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f + 4.0f*4.0f), r);
}

TEST_F(QuaternionTest, Normalize) {
  q1.normalize();

  ASSERT_GE(1.0f, q1.w());
  ASSERT_GE(1.0f, q1.x());
  ASSERT_GE(1.0f, q1.y());
  ASSERT_GE(1.0f, q1.z());

  EXPECT_NEAR(1.0f / sqrt(30.0f), q1.w(), 1.0e-3f);
  EXPECT_NEAR(sqrt(2.0f / 15.0f), q1.x(), 1.0e-3f);
  EXPECT_NEAR(sqrt(3.0f / 10.0f), q1.y(), 1.0e-3f);
  EXPECT_NEAR(2.0f*sqrt(2.0f / 15.0f), q1.z(), 1.0e-3f);
}

TEST_F(QuaternionTest, Normalized) {
  q0 = q1.normalized();

  assert_q1_unmodified();

  ASSERT_GE(1.0f, q0.w());
  ASSERT_GE(1.0f, q0.x());
  ASSERT_GE(1.0f, q0.y());
  ASSERT_GE(1.0f, q0.z());

  EXPECT_NEAR(1.0f / sqrt(30.0f), q0.w(), 1.0e-3f);
  EXPECT_NEAR(sqrt(2.0f / 15.0f), q0.x(), 1.0e-3f);
  EXPECT_NEAR(sqrt(3.0f / 10.0f), q0.y(), 1.0e-3f);
  EXPECT_NEAR(2.0f*sqrt(2.0f / 15.0f), q0.z(), 1.0e-3f);
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_RotateVector) {
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_Slerp) {
}

// TODO(JCube001): Implement
TEST_F(QuaternionTest, DISABLED_Squad) {
}

TEST_F(QuaternionTest, Swap) {
  fusion::swap(q1, q2);

  ASSERT_FALSE(q1 == q2);

  EXPECT_FLOAT_EQ(5.0f, q1.w());
  EXPECT_FLOAT_EQ(6.0f, q1.x());
  EXPECT_FLOAT_EQ(7.0f, q1.y());
  EXPECT_FLOAT_EQ(8.0f, q1.z());

  EXPECT_FLOAT_EQ(1.0f, q2.w());
  EXPECT_FLOAT_EQ(2.0f, q2.x());
  EXPECT_FLOAT_EQ(3.0f, q2.y());
  EXPECT_FLOAT_EQ(4.0f, q2.z());
}
