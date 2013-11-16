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
#include "../utility/vector.h"

class Vector3Test : public ::testing::Test {
 protected:
  virtual void SetUp() {
    p1.set(1.0f, 2.0f, 3.0f);
    p2.set(4.0f, 5.0f, 6.0f);
    p3.set(1.0f, 2.0f, 3.0f);
  }

  virtual void TearDown() {
  }

  void assert_p1_unmodified() {
    ASSERT_FLOAT_EQ(1.0f, p1.x());
    ASSERT_FLOAT_EQ(2.0f, p1.y());
    ASSERT_FLOAT_EQ(3.0f, p1.z());
  }

  void assert_p2_unmodified() {
    ASSERT_FLOAT_EQ(4.0f, p2.x());
    ASSERT_FLOAT_EQ(5.0f, p2.y());
    ASSERT_FLOAT_EQ(6.0f, p2.z());
  }

  fusion::Vector3 p0;
  fusion::Vector3 p1;
  fusion::Vector3 p2;
  fusion::Vector3 p3;
};

TEST_F(Vector3Test, DefaultConstructor) {
  ASSERT_FLOAT_EQ(0.0f, p0.x());
  ASSERT_FLOAT_EQ(0.0f, p0.y());
  ASSERT_FLOAT_EQ(0.0f, p0.z());
}

TEST_F(Vector3Test, CopyConstructor) {
  fusion::Vector3 t(p1);

  ASSERT_FLOAT_EQ(p1.x(), t.x());
  ASSERT_FLOAT_EQ(p1.y(), t.y());
  ASSERT_FLOAT_EQ(p1.z(), t.z());
}

TEST_F(Vector3Test, ArrayInitializationConstructor) {
  float arr[3] = {100.0f, 200.0f, 300.0f};
  fusion::Vector3 t(arr);

  ASSERT_FLOAT_EQ(arr[0], t.x());
  ASSERT_FLOAT_EQ(arr[1], t.y());
  ASSERT_FLOAT_EQ(arr[2], t.z());
}

TEST_F(Vector3Test, InitializationConstructor) {
  fusion::Vector3 t(100.0f, 200.0f, 300.0f);

  ASSERT_FLOAT_EQ(100.0f, t.x());
  ASSERT_FLOAT_EQ(200.0f, t.y());
  ASSERT_FLOAT_EQ(300.0f, t.z());
}

TEST_F(Vector3Test, MutatorMethods) {
  p1.set(100.0f, 200.0f, 300.0f);

  ASSERT_FLOAT_EQ(100.0f, p1.x());
  ASSERT_FLOAT_EQ(200.0f, p1.y());
  ASSERT_FLOAT_EQ(300.0f, p1.z());
}

TEST_F(Vector3Test, AccessorMethods) {
  ASSERT_FLOAT_EQ(1.0f, p1.x());
  ASSERT_FLOAT_EQ(2.0f, p1.y());
  ASSERT_FLOAT_EQ(3.0f, p1.z());
}

TEST_F(Vector3Test, AssignmentOperator) {
  p1 = p2;

  ASSERT_FLOAT_EQ(p2.x(), p1.x());
  ASSERT_FLOAT_EQ(p2.y(), p1.y());
  ASSERT_FLOAT_EQ(p2.z(), p1.z());
}

TEST_F(Vector3Test, SubscriptAccessorOperator) {
  ASSERT_FLOAT_EQ(1.0f, p1[0]);
  ASSERT_FLOAT_EQ(2.0f, p1[1]);
  ASSERT_FLOAT_EQ(3.0f, p1[2]);
}

TEST_F(Vector3Test, SubscriptMutatorOperator) {
  p1[0] = 100.0f;
  p1[1] = 200.0f;
  p1[2] = 300.0f;

  ASSERT_FLOAT_EQ(100.0f, p1[0]);
  ASSERT_FLOAT_EQ(200.0f, p1[1]);
  ASSERT_FLOAT_EQ(300.0f, p1[2]);
}

TEST_F(Vector3Test, CompoundAdditionOperator) {
  p1 += p2;

  ASSERT_FLOAT_EQ(1.0f + 4.0f, p1.x());
  ASSERT_FLOAT_EQ(2.0f + 5.0f, p1.y());
  ASSERT_FLOAT_EQ(3.0f + 6.0f, p1.z());

  assert_p2_unmodified();
}

TEST_F(Vector3Test, CompoundSubtractionOperator) {
  p1 -= p2;

  ASSERT_FLOAT_EQ(1.0f - 4.0f, p1.x());
  ASSERT_FLOAT_EQ(2.0f - 5.0f, p1.y());
  ASSERT_FLOAT_EQ(3.0f - 6.0f, p1.z());

  assert_p2_unmodified();
}

TEST_F(Vector3Test, CompoundScalarMultiplicationOperator) {
  p1 *= 2.0f;

  ASSERT_FLOAT_EQ(1.0f * 2.0f, p1.x());
  ASSERT_FLOAT_EQ(2.0f * 2.0f, p1.y());
  ASSERT_FLOAT_EQ(3.0f * 2.0f, p1.z());
}

TEST_F(Vector3Test, CompoundVectorMultiplicationOperator) {
  p1 *= p2;

  ASSERT_FLOAT_EQ(-3.0f, p1.x());
  ASSERT_FLOAT_EQ(6.0f, p1.y());
  ASSERT_FLOAT_EQ(-3.0f, p1.z());

  assert_p2_unmodified();
}

TEST_F(Vector3Test, CompoundScalarDivisionOperator) {
  p1 /= 2.0f;

  ASSERT_FLOAT_EQ(1.0f / 2.0f, p1.x());
  ASSERT_FLOAT_EQ(2.0f / 2.0f, p1.y());
  ASSERT_FLOAT_EQ(3.0f / 2.0f, p1.z());
}

TEST_F(Vector3Test, VectorAdditionOperator) {
  p0 = p1 + p2;

  ASSERT_FLOAT_EQ(1.0f + 4.0f, p0.x());
  ASSERT_FLOAT_EQ(2.0f + 5.0f, p0.y());
  ASSERT_FLOAT_EQ(3.0f + 6.0f, p0.z());

  assert_p1_unmodified();
  assert_p2_unmodified();
}

TEST_F(Vector3Test, VectorSubtractionOperator) {
  p0 = p1 - p2;

  ASSERT_FLOAT_EQ(1.0f - 4.0f, p0.x());
  ASSERT_FLOAT_EQ(2.0f - 5.0f, p0.y());
  ASSERT_FLOAT_EQ(3.0f - 6.0f, p0.z());

  assert_p1_unmodified();
  assert_p2_unmodified();
}

TEST_F(Vector3Test, UnaryNegationOperator) {
  p0 = -p1;

  ASSERT_FLOAT_EQ(-1.0f, p0.x());
  ASSERT_FLOAT_EQ(-2.0f, p0.y());
  ASSERT_FLOAT_EQ(-3.0f, p0.z());

  assert_p1_unmodified();
}

TEST_F(Vector3Test, ScalarLeftMultiplicationOperator) {
  p0 = 2.0f * p1;

  ASSERT_FLOAT_EQ(2.0f * 1.0f, p0.x());
  ASSERT_FLOAT_EQ(2.0f * 2.0f, p0.y());
  ASSERT_FLOAT_EQ(2.0f * 3.0f, p0.z());

  assert_p1_unmodified();
}

TEST_F(Vector3Test, ScalarRightMultiplicationOperator) {
  p0 = p1 * 2.0f;

  ASSERT_FLOAT_EQ(1.0f * 2.0f, p0.x());
  ASSERT_FLOAT_EQ(2.0f * 2.0f, p0.y());
  ASSERT_FLOAT_EQ(3.0f * 2.0f, p0.z());

  assert_p1_unmodified();
}

TEST_F(Vector3Test, VectorMultiplicationOperator) {
  p0 = p1 * p2;

  ASSERT_FLOAT_EQ(-3.0f, p0.x());
  ASSERT_FLOAT_EQ(6.0f, p0.y());
  ASSERT_FLOAT_EQ(-3.0f, p0.z());

  assert_p1_unmodified();
  assert_p2_unmodified();
}

TEST_F(Vector3Test, ScalarDivisionOperator) {
  p0 = p1 / 2.0f;

  ASSERT_FLOAT_EQ(1.0f / 2.0f, p0.x());
  ASSERT_FLOAT_EQ(2.0f / 2.0f, p0.y());
  ASSERT_FLOAT_EQ(3.0f / 2.0f, p0.z());

  assert_p1_unmodified();
}

TEST_F(Vector3Test, EqualToOperator) {
  ASSERT_TRUE(p1 == p3);
  ASSERT_FALSE(p1 == p2);
}

TEST_F(Vector3Test, NotEqualToOperator) {
  ASSERT_TRUE(p1 != p2);
  ASSERT_FALSE(p1 != p3);
}

TEST_F(Vector3Test, LessThanOperator) {
  ASSERT_TRUE(p1 < p2);
  ASSERT_FALSE(p2 < p1);
}

TEST_F(Vector3Test, GreaterThanOperator) {
  ASSERT_TRUE(p2 > p1);
  ASSERT_FALSE(p1 > p2);
}

TEST_F(Vector3Test, LessThanOrEqualToOperator) {
  ASSERT_TRUE(p1 <= p2);
  ASSERT_TRUE(p1 <= p3);
  ASSERT_FALSE(p2 <= p1);
}

TEST_F(Vector3Test, GreaterThanOrEqualToOperator) {
  ASSERT_TRUE(p2 >= p1);
  ASSERT_TRUE(p1 >= p3);
  ASSERT_FALSE(p1 >= p2);
}

TEST_F(Vector3Test, VectorDotProduct) {
  float r = fusion::Vector3::dot(p1, p2);

  ASSERT_FLOAT_EQ(1.0f*4.0f + 2.0f*5.0f + 3.0f*6.0f, r);
}

TEST_F(Vector3Test, FastNormalize) {
  p1.fastNormalize();

  ASSERT_GE(1.0f, p1.x());
  ASSERT_GE(1.0f, p1.y());
  ASSERT_GE(1.0f, p1.z());

  EXPECT_NEAR(1.0f / sqrt(14.0f), p1.x(), 1.0e-3f);
  EXPECT_NEAR(sqrt(2.0f / 7.0f), p1.y(), 1.0e-3f);
  EXPECT_NEAR(3.0f / sqrt(14.0f), p1.z(), 1.0e-3f);
}

TEST_F(Vector3Test, FastNormalized) {
  p0 = p1.fastNormalized();

  assert_p1_unmodified();

  ASSERT_GE(1.0f, p0.x());
  ASSERT_GE(1.0f, p0.y());
  ASSERT_GE(1.0f, p0.z());

  EXPECT_NEAR(1.0f / sqrt(14.0f), p0.x(), 1.0e-3f);
  EXPECT_NEAR(sqrt(2.0f / 7.0f), p0.y(), 1.0e-3f);
  EXPECT_NEAR(3.0f / sqrt(14.0f), p0.z(), 1.0e-3f);
}

// TODO(JCube001): Lerp
TEST_F(Vector3Test, DISABLED_Lerp) {
}

// TODO(JCube001): TripleProduct
TEST_F(Vector3Test, DISABLED_TripleProduct) {
}

// TODO(JCube001): Nlerp
TEST_F(Vector3Test, DISABLED_Nlerp) {
}

TEST_F(Vector3Test, Norm) {
  float r = p1.norm();

  ASSERT_FLOAT_EQ(sqrt(1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f), r);
}

TEST_F(Vector3Test, Normalize) {
  p1.normalize();

  ASSERT_GE(1.0f, p1.x());
  ASSERT_GE(1.0f, p1.y());
  ASSERT_GE(1.0f, p1.z());

  EXPECT_NEAR(1.0f / sqrt(14.0f), p1.x(), 1.0e-3f);
  EXPECT_NEAR(sqrt(2.0f / 7.0f), p1.y(), 1.0e-3f);
  EXPECT_NEAR(3.0f / sqrt(14.0f), p1.z(), 1.0e-3f);
}

TEST_F(Vector3Test, Normalized) {
  p0 = p1.normalized();

  assert_p1_unmodified();

  ASSERT_GE(1.0f, p0.x());
  ASSERT_GE(1.0f, p0.y());
  ASSERT_GE(1.0f, p0.z());

  EXPECT_NEAR(1.0f / sqrt(14.0f), p0.x(), 1.0e-3f);
  EXPECT_NEAR(sqrt(2.0f / 7.0f), p0.y(), 1.0e-3f);
  EXPECT_NEAR(3.0f / sqrt(14.0f), p0.z(), 1.0e-3f);
}

// TODO(JCube001): Slerp
TEST_F(Vector3Test, DISABLED_Slerp) {
}

TEST_F(Vector3Test, Swap) {
  fusion::swap(p1, p2);

  ASSERT_FALSE(p1 == p2);

  EXPECT_FLOAT_EQ(4.0f, p1.x());
  EXPECT_FLOAT_EQ(5.0f, p1.y());
  EXPECT_FLOAT_EQ(6.0f, p1.z());

  EXPECT_FLOAT_EQ(1.0f, p2.x());
  EXPECT_FLOAT_EQ(2.0f, p2.y());
  EXPECT_FLOAT_EQ(3.0f, p2.z());
}
