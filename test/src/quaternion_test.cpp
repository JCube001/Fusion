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

TEST(QuaternionTest, Dot)
{
}

