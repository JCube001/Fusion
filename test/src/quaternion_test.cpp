#include <cmath>
#include "gtest/gtest.h"
#include "quaternion.h"

TEST(QuaternionTest, Default)
{
    const Quaternion q;
    EXPECT_EQ(1.0f, q.w);
    EXPECT_EQ(0.0f, q.x);
    EXPECT_EQ(0.0f, q.y);
    EXPECT_EQ(0.0f, q.z);
}

TEST(QuaternionTest, Copy)
{
    const Quaternion temp(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion q(temp);
    EXPECT_EQ(1.0f, q.w);
    EXPECT_EQ(2.0f, q.x);
    EXPECT_EQ(3.0f, q.y);
    EXPECT_EQ(4.0f, q.z);
}

TEST(QuaternionTest, Initialize)
{
    const Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_EQ(1.0f, q.w);
    EXPECT_EQ(2.0f, q.x);
    EXPECT_EQ(3.0f, q.y);
    EXPECT_EQ(4.0f, q.z);
}

TEST(QuaternionTest, Conjugate)
{
    const Quaternion temp(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion q = temp.conjugate();
    EXPECT_EQ(1.0f, q.w);
    EXPECT_EQ(-2.0f, q.x);
    EXPECT_EQ(-3.0f, q.y);
    EXPECT_EQ(-4.0f, q.z);
}

TEST(QuaternionTest, ConvertToAxisAngle)
{
    const Quaternion q(0.707107f, 0.0f, 0.0f, 0.707107f);
    float x, y, z, angle;
    q.convertToAxisAngle(x, y, z, angle);
    EXPECT_FLOAT_EQ(0.0f, x);
    EXPECT_FLOAT_EQ(0.0f, y);
    EXPECT_FLOAT_EQ(0.707107f, z);
    EXPECT_NEAR(1.57079633f, angle, 1.0e-4f);
}

TEST(QuaternionTest, ConvertToEulerAngles)
{
    const Quaternion q(0.707107f, 0.0f, 0.0f, 0.707107f);
    float roll, pitch, yaw;
    q.convertToEulerAngles(roll, pitch, yaw);
    EXPECT_FLOAT_EQ(0.0f, roll);
    EXPECT_FLOAT_EQ(0.0f, pitch);
    EXPECT_NEAR(1.57079633f, yaw, 1.0e-4f);
}

TEST(QuaternionTest, DotProductMultiplication)
{
    const Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion q2(2.0f, 2.0f, 2.0f, 2.0f);
    EXPECT_EQ(20.0f, q1.dot(q2));
}

TEST(QuaternionTest, Inverse)
{
    const Quaternion temp(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion q = temp.inverse();
    EXPECT_FLOAT_EQ(1.0f / 30.0f, q.w);
    EXPECT_FLOAT_EQ(-1.0f / 15.0f, q.x);
    EXPECT_FLOAT_EQ(-1.0f / 10.0f, q.y);
    EXPECT_FLOAT_EQ(-2.0f / 15.0f, q.z);
}

TEST(QuaternionTest, Norm)
{
    const Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(std::sqrt(30.0f), q.norm());
}

TEST(QuaternionTest, Normalize)
{
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    q.normalize();
    EXPECT_FLOAT_EQ(1.0f / std::sqrt(30.0f), q.w);
    EXPECT_FLOAT_EQ(std::sqrt(2.0f / 15.0f), q.x);
    EXPECT_FLOAT_EQ(std::sqrt(3.0f / 10.0f), q.y);
    EXPECT_FLOAT_EQ(2.0f * std::sqrt(2.0f / 15.0f), q.z);
}

TEST(QuaternionTest, Normalized)
{
    const Quaternion temp(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion q = temp.normalized();
    EXPECT_FLOAT_EQ(1.0f / std::sqrt(30.0f), q.w);
    EXPECT_FLOAT_EQ(std::sqrt(2.0f / 15.0f), q.x);
    EXPECT_FLOAT_EQ(std::sqrt(3.0f / 10.0f), q.y);
    EXPECT_FLOAT_EQ(2.0f * std::sqrt(2.0f / 15.0f), q.z);
}

TEST(QuaternionTest, Assignment)
{
    const Quaternion temp(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion q = temp;
    EXPECT_EQ(1.0f, q.w);
    EXPECT_EQ(2.0f, q.x);
    EXPECT_EQ(3.0f, q.y);
    EXPECT_EQ(4.0f, q.z);
}

TEST(QuaternionTest, CompoundAddition)
{
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion q2(1.0f, 1.0f, 1.0f, 1.0f);
    q1 += q2;
    EXPECT_EQ(2.0f, q1.w);
    EXPECT_EQ(3.0f, q1.x);
    EXPECT_EQ(4.0f, q1.y);
    EXPECT_EQ(5.0f, q1.z);
}

TEST(QuaternionTest, CompoundSubtraction)
{
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    const Quaternion q2(1.0f, 1.0f, 1.0f, 1.0f);
    q1 -= q2;
    EXPECT_EQ(0.0f, q1.w);
    EXPECT_EQ(1.0f, q1.x);
    EXPECT_EQ(2.0f, q1.y);
    EXPECT_EQ(3.0f, q1.z);
}

TEST(QuaternionTest, CompoundScalarMultiplication)
{
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    const float f = 2.0f;
    q *= f;
    EXPECT_EQ(2.0f, q.w);
    EXPECT_EQ(4.0f, q.x);
    EXPECT_EQ(6.0f, q.y);
    EXPECT_EQ(8.0f, q.z);
}

TEST(QuaternionTest, CompoundCrossProductMultiplication)
{
    Quaternion q1(0.707107f, 0.0f, 0.0f, 0.707107f);
    const Quaternion q2(0.707107f, 0.0f, 0.707107f, 0.0f);
    q1 *= q2;
    EXPECT_NEAR(0.5f, q1.w, 0.1f);
    EXPECT_NEAR(-0.5f, q1.x, 0.1f);
    EXPECT_NEAR(0.5f, q1.y, 0.1f);
    EXPECT_NEAR(0.5f, q1.z, 0.1f);
}

TEST(QuaternionTest, CompoundScalarDivision)
{
    Quaternion q(2.0f, 4.0f, 6.0f, 8.0f);
    const float f = 2.0f;
    q /= f;
    EXPECT_EQ(1.0f, q.w);
    EXPECT_EQ(2.0f, q.x);
    EXPECT_EQ(3.0f, q.y);
    EXPECT_EQ(4.0f, q.z);
}

