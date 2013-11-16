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
    p0.set(1.0f, 2.0f, 3.0f);
    p1.set(4.0f, 5.0f, 6.0f);
  }
  
  virtual void TearDown() {
  }
  
  fusion::Vector3 p0;
  fusion::Vector3 p1;
};

TEST_F(Vector3Test, AccessorMethods) {
  EXPECT_FLOAT_EQ(1.0f, p0.x());
  EXPECT_FLOAT_EQ(2.0f, p0.y());
  EXPECT_FLOAT_EQ(3.0f, p0.z());
}

TEST_F(Vector3Test, AssignmentOperator) {
  p0 = p1;

  EXPECT_FLOAT_EQ(p1.x(), p0.x());
  EXPECT_FLOAT_EQ(p1.y(), p0.y());
  EXPECT_FLOAT_EQ(p1.z(), p0.z());
}

TEST_F(Vector3Test, SubscriptAccessorOperator) {
  EXPECT_FLOAT_EQ(1.0f, p0[0]);
  EXPECT_FLOAT_EQ(2.0f, p0[1]);
  EXPECT_FLOAT_EQ(3.0f, p0[2]);
}

TEST_F(Vector3Test, SubscriptMutatorOperator) {
  p0[0] = 100.0f;
  p0[1] = 200.0f;
  p0[2] = 300.0f;

  EXPECT_FLOAT_EQ(100.0f, p0[0]);
  EXPECT_FLOAT_EQ(200.0f, p0[1]);
  EXPECT_FLOAT_EQ(300.0f, p0[2]);
}

TEST_F(Vector3Test, CompoundAdditionOperator) {
  p0 += p1;

  // p0 = p0 + p1
  EXPECT_FLOAT_EQ(1.0f + 4.0f, p0.x());
  EXPECT_FLOAT_EQ(2.0f + 5.0f, p0.y());
  EXPECT_FLOAT_EQ(3.0f + 6.0f, p0.z());
  
  // p1 unchanged
  EXPECT_FLOAT_EQ(4.0f, p1.x());
  EXPECT_FLOAT_EQ(5.0f, p1.y());
  EXPECT_FLOAT_EQ(6.0f, p1.z());
}

TEST_F(Vector3Test, CompoundSubtractionOperator) {
  p0 -= p1;

  // p0 = p0 - p1
  EXPECT_FLOAT_EQ(1.0f - 4.0f, p0.x());
  EXPECT_FLOAT_EQ(2.0f - 5.0f, p0.y());
  EXPECT_FLOAT_EQ(3.0f - 6.0f, p0.z());
  
  // p1 unchanged
  EXPECT_FLOAT_EQ(4.0f, p1.x());
  EXPECT_FLOAT_EQ(5.0f, p1.y());
  EXPECT_FLOAT_EQ(6.0f, p1.z());
}

TEST_F(Vector3Test, CompoundScalarMultiplicationOperator) {
  p0 *= 2.0f;

  // p0 = p0 * 2
  EXPECT_FLOAT_EQ(1.0f * 2.0f, p0.x());
  EXPECT_FLOAT_EQ(2.0f * 2.0f, p0.y());
  EXPECT_FLOAT_EQ(3.0f * 2.0f, p0.z());
}

TEST_F(Vector3Test, CompoundVectorMultiplicationOperator) {
  p0 *= p1;

  // p0 = p0 * p1
  EXPECT_FLOAT_EQ(-3.0f, p0.x());
  EXPECT_FLOAT_EQ(6.0f, p0.y());
  EXPECT_FLOAT_EQ(-3.0f, p0.z());
  
  // p1 unchanged
  EXPECT_FLOAT_EQ(4.0f, p1.x());
  EXPECT_FLOAT_EQ(5.0f, p1.y());
  EXPECT_FLOAT_EQ(6.0f, p1.z());
}

#if 0
TEST(Vector3Test, DefaultConstructor) {
  const Vector3 v;

  EXPECT_FLOAT_EQ(0.0f, v.x());
  EXPECT_FLOAT_EQ(0.0f, v.y());
  EXPECT_FLOAT_EQ(0.0f, v.z());
}

TEST(Vector3Test, CopyConstructor) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(v1);

  EXPECT_FLOAT_EQ(v1.x(), v2.x());
  EXPECT_FLOAT_EQ(v1.y(), v2.y());
  EXPECT_FLOAT_EQ(v1.z(), v2.z());
}

TEST(Vector3Test, ArrayInitializationConstructor) {
  const float a[] = {1.0f, 2.0f, 3.0f};
  const Vector3 v(a);

  EXPECT_FLOAT_EQ(a[0], v.x());
  EXPECT_FLOAT_EQ(a[1], v.y());
  EXPECT_FLOAT_EQ(a[2], v.z());
}

TEST(Vector3Test, InitializationConstructor) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const Vector3 v(x, y, z);

  EXPECT_FLOAT_EQ(x, v.x());
  EXPECT_FLOAT_EQ(y, v.y());
  EXPECT_FLOAT_EQ(z, v.z());
}

TEST(Vector3Test, GetX) {
  const float x = 1.0f;
  const Vector3 v(x, 99.99f, 99.99f);

  EXPECT_FLOAT_EQ(x, v.x());
}

TEST(Vector3Test, GetY) {
  const float y = 1.0f;
  const Vector3 v(99.99f, y, 99.99f);

  EXPECT_FLOAT_EQ(y, v.y());
}

TEST(Vector3Test, GetZ) {
  const float z = 1.0f;
  const Vector3 v(99.99f, 99.99f, z);

  EXPECT_FLOAT_EQ(z, v.z());
}

TEST(Vector3Test, SubscriptOperator) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const Vector3 v(x, y, z);

  EXPECT_FLOAT_EQ(x, v[0]);
  EXPECT_FLOAT_EQ(y, v[1]);
  EXPECT_FLOAT_EQ(z, v[2]);
}

TEST(Vector3Test, AssignmentOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2 = v1;

  EXPECT_FLOAT_EQ(v1.x(), v2.x());
  EXPECT_FLOAT_EQ(v1.y(), v2.y());
  EXPECT_FLOAT_EQ(v1.z(), v2.z());
}

TEST(Vector3Test, UnaryNegationOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(-v1);

  EXPECT_FLOAT_EQ(-v1.x(), v2.x());
  EXPECT_FLOAT_EQ(-v1.y(), v2.y());
  EXPECT_FLOAT_EQ(-v1.z(), v2.z());
}

TEST(Vector3Test, AdditionOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);
  const Vector3 v3 = v1 + v2;

  EXPECT_FLOAT_EQ(5.0f, v3.x());
  EXPECT_FLOAT_EQ(7.0f, v3.y());
  EXPECT_FLOAT_EQ(9.0f, v3.z());
}

TEST(Vector3Test, SubtractionOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);
  const Vector3 v3 = v1 - v2;

  EXPECT_FLOAT_EQ(-3.0f, v3.x());
  EXPECT_FLOAT_EQ(-3.0f, v3.y());
  EXPECT_FLOAT_EQ(-3.0f, v3.z());
}

TEST(Vector3Test, VectorMultiplicationOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);
  const Vector3 v3 = v1 * v2;
  const Vector3 v4 = v2 * v1;

  EXPECT_FLOAT_EQ(-3.0f, v3.x());
  EXPECT_FLOAT_EQ(6.0f, v3.y());
  EXPECT_FLOAT_EQ(-3.0f, v3.z());

  EXPECT_FLOAT_EQ(3.0f, v4.x());
  EXPECT_FLOAT_EQ(-6.0f, v4.y());
  EXPECT_FLOAT_EQ(3.0f, v4.z());
}

TEST(Vector3Test, ScalarMultiplicationOperator) {
  const float s = 2.0f;
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2 = v1 * s;

  EXPECT_FLOAT_EQ(2.0f, v2.x());
  EXPECT_FLOAT_EQ(4.0f, v2.y());
  EXPECT_FLOAT_EQ(6.0f, v2.z());
}

TEST(Vector3Test, ScalarDivisionOperator) {
  const float s = 2.0f;
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2 = v1 / s;

  EXPECT_FLOAT_EQ(0.5f, v2.x());
  EXPECT_FLOAT_EQ(1.0f, v2.y());
  EXPECT_FLOAT_EQ(1.5f, v2.z());
}

TEST(Vector3Test, EqualToOperator) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const Vector3 v1(x, y, z);
  const Vector3 v2(x, y, z);
  const Vector3 v3(x, y, 99.99f);

  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
}

TEST(Vector3Test, NotEqualToOperator) {
  const float x = 1.0f;
  const float y = 2.0f;
  const float z = 3.0f;
  const Vector3 v1(x, y, z);
  const Vector3 v2(x, y, z);
  const Vector3 v3(x, y, 99.99f);

  EXPECT_TRUE(v1 != v3);
  EXPECT_FALSE(v1 != v2);
}

TEST(Vector3Test, LessThanOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);

  EXPECT_TRUE(v1 < v2);
  EXPECT_FALSE(v2 < v1);
  EXPECT_FALSE(v1 < v1);
}

TEST(Vector3Test, GreaterThanOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);

  EXPECT_TRUE(v2 > v1);
  EXPECT_FALSE(v1 > v2);
  EXPECT_FALSE(v1 > v1);
}

TEST(Vector3Test, LessThanOrEqualToOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);

  EXPECT_TRUE(v1 <= v1);
  EXPECT_TRUE(v1 <= v2);
  EXPECT_FALSE(v2 <= v1);
}

TEST(Vector3Test, GreaterThanOrEqualToOperator) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);

  EXPECT_TRUE(v2 >= v1);
  EXPECT_TRUE(v2 >= v2);
  EXPECT_FALSE(v1 >= v2);
}

TEST(Vector3Test, DotProductMultiplication) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);

  EXPECT_FLOAT_EQ(32.0f, Vector3::dot(v1, v2));
  EXPECT_FLOAT_EQ(32.0f, Vector3::dot(v2, v1));
}

TEST(Vector3Test, Lerp) {
  const float a1 = 0.0f;
  const float a2 = 0.5f;
  const float a3 = 1.0f;
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);
  const Vector3 v3(2.5f, 3.5f, 4.5f);
  const Vector3 v4(Vector3::lerp(v1, v2, a1));
  const Vector3 v5(Vector3::lerp(v1, v2, a2));
  const Vector3 v6(Vector3::lerp(v1, v2, a3));

  EXPECT_FLOAT_EQ(v1.x(), v4.x());
  EXPECT_FLOAT_EQ(v1.y(), v4.y());
  EXPECT_FLOAT_EQ(v1.z(), v4.z());

  EXPECT_FLOAT_EQ(v3.x(), v5.x());
  EXPECT_FLOAT_EQ(v3.y(), v5.y());
  EXPECT_FLOAT_EQ(v3.z(), v5.z());

  EXPECT_FLOAT_EQ(v2.x(), v6.x());
  EXPECT_FLOAT_EQ(v2.y(), v6.y());
  EXPECT_FLOAT_EQ(v2.z(), v6.z());
}

TEST(Vector3Test, TripleProductMultiplication) {
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);
  const Vector3 v3(7.0f, 8.0f, 9.0f);

  EXPECT_FLOAT_EQ(0.0f, Vector3::tripleProduct(v1, v2, v3));
}

TEST(Vector3Test, Nlerp) {
  const float a1 = 0.0f;
  const float a2 = 0.5f;
  const float a3 = 1.0f;
  const float v1_norm = static_cast<float>(sqrt(14.0f));
  const float v2_norm = static_cast<float>(sqrt(77.0f));
  const float v3_norm = static_cast<float>(sqrt(38.75f));
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);
  const Vector3 v3(2.5f, 3.5f, 4.5f);
  const Vector3 v4(Vector3::nlerp(v1, v2, a1));
  const Vector3 v5(Vector3::nlerp(v1, v2, a2));
  const Vector3 v6(Vector3::nlerp(v1, v2, a3));

  EXPECT_FLOAT_EQ(v1.x() / v1_norm, v4.x());
  EXPECT_FLOAT_EQ(v1.y() / v1_norm, v4.y());
  EXPECT_FLOAT_EQ(v1.z() / v1_norm, v4.z());

  EXPECT_FLOAT_EQ(v3.x() / v3_norm, v5.x());
  EXPECT_FLOAT_EQ(v3.y() / v3_norm, v5.y());
  EXPECT_FLOAT_EQ(v3.z() / v3_norm, v5.z());

  EXPECT_FLOAT_EQ(v2.x() / v2_norm, v6.x());
  EXPECT_FLOAT_EQ(v2.y() / v2_norm, v6.y());
  EXPECT_FLOAT_EQ(v2.z() / v2_norm, v6.z());
}

TEST(Vector3Test, Norm) {
  const Vector3 v(1.0f, 2.0f, 3.0f);

  EXPECT_FLOAT_EQ(static_cast<float>(sqrt(14.0f)), v.norm());
}

TEST(Vector3Test, Normalize) {
  const float v1_norm = static_cast<float>(sqrt(14.0f));
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(v1.normalize());

  EXPECT_FLOAT_EQ(v1.x() / v1_norm, v2.x());
  EXPECT_FLOAT_EQ(v1.y() / v1_norm, v2.y());
  EXPECT_FLOAT_EQ(v1.z() / v1_norm, v2.z());
}

TEST(Vector3Test, Slerp) {
  const float a1 = 0.0f;
  const float a2 = 0.75f;
  const float a3 = 1.0f;
  const float v1_norm = static_cast<float>(sqrt(14.0f));
  const float v2_norm = static_cast<float>(sqrt(77.0f));
  const Vector3 v1(1.0f, 2.0f, 3.0f);
  const Vector3 v2(4.0f, 5.0f, 6.0f);
  const Vector3 v3(0.41050804f, 0.56364781f, 0.71678758f);
  const Vector3 v4(Vector3::slerp(v1, v2, a1));
  const Vector3 v5(Vector3::slerp(v1, v2, a2));
  const Vector3 v6(Vector3::slerp(v1, v2, a3));

  EXPECT_FLOAT_EQ(v1.x() / v1_norm, v4.x());
  EXPECT_FLOAT_EQ(v1.y() / v1_norm, v4.y());
  EXPECT_FLOAT_EQ(v1.z() / v1_norm, v4.z());

  EXPECT_FLOAT_EQ(v3.x(), v5.x());
  EXPECT_FLOAT_EQ(v3.y(), v5.y());
  EXPECT_FLOAT_EQ(v3.z(), v5.z());

  EXPECT_FLOAT_EQ(v2.x() / v2_norm, v6.x());
  EXPECT_FLOAT_EQ(v2.y() / v2_norm, v6.y());
  EXPECT_FLOAT_EQ(v2.z() / v2_norm, v6.z());
}
#endif
