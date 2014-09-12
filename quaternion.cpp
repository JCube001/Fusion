/*
The MIT License (MIT)

Copyright (c) 2013, 2014 Jacob McGladdery

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
*/

/**
 * @file  quaternion.cpp
 * @brief Quaternion implementation.
 */

#include <math.h>
#include "quaternion.h"

Quaternion::Quaternion() :
    w(1.0f),
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

Quaternion::Quaternion(const Quaternion &q) :
    w(q.w),
    x(q.x),
    y(q.y),
    z(q.z)
{
}

Quaternion::Quaternion(const float w, const float x, const float y, const float z) :
    w(w),
    x(x),
    y(y),
    z(z)
{
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion(w, -x, -y, -z);
}

void Quaternion::convertToAxisAngle(float &wx, float &wy, float &wz, float &angle) const
{
    angle = 2.0f * acos(w);
    const float sin_half_angle = sin(angle / 2.0f);
    if (0 != angle)
    {
        wx = x / sin_half_angle;
        wy = y / sin_half_angle;
        wz = z / sin_half_angle;
    }
    else
    {
        wx = 0.0f;
        wy = 0.0f;
        wz = 0.0f;
    }
}

void Quaternion::convertToEulerAngles(float &roll, float &pitch, float &yaw) const
{
    roll = atan2(2.0f * ((w * x) + (y * z)), 1.0f - (2.0f * ((x * x) + (y * y))));
    pitch = asin(2.0f * ((w * y) - (z * x)));
    yaw = atan2(2.0f * ((w * z) + (x * y)), 1.0f - (2.0f ((y * y) + (z * z))));
}

float Quaternion::dot(const Quaternion &q) const
{
    return (w * q.w) + (x * q.x) + (y * q.y) + (z * q.z);
}

Quaternion Quaternion::inverse() const
{
    const float n = norm();
    if (0.0f == n)
    {
        return Quaternion();
    }
    return conjugate() / (n * n);
}

float Quaternion::norm() const
{
    return sqrt((w * w) + (x * x) + (y * y) + (z * z));
}

void Quaternion::normalize()
{
    *this /= norm();
}

Quaternion Quaternion::normalized() const
{
    return *this / norm();
}

Quaternion &Quaternion::operator=(const Quaternion &q)
{
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
    return *this;
}

Quaternion &Quaternion::operator+=(const Quaternion &q)
{
    w += q.w;
    x += q.x;
    y += q.y;
    z += q.z;
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &q)
{
    w -= q.w;
    x -= q.x;
    y -= q.y;
    z -= q.z;
    return *this;
}

Quaternion &Quaternion::operator*=(float factor)
{
    w *= factor;
    x *= factor;
    y *= factor;
    z *= factor;
    return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &q)
{
    const Quaternion t = *this;
    w = (t.w * q.w) - (t.x * q.x) - (t.y * q.y) - (t.z * q.z);
    x = (t.w * q.x) + (t.x * q.w) + (t.y * q.z) - (t.z * q.y);
    y = (t.w * q.y) - (t.x * q.z) + (t.y * q.w) + (t.z * q.x);
    z = (t.w * q.z) + (t.x * q.y) - (t.y * q.x) + (t.z * q.w);
    return *this;
}

Quaternion &Quaternion::operator/=(float divisor)
{
    w /= divisor;
    x /= divisor;
    y /= divisor;
    z /= divisor;
    return *this;
}
