/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2013, 2014 JCube001

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

Quaternion::Quaternion(float w, float x, float y, float z) :
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

void Quaternion::convertToAxisAngle(float &ax, float &ay, float &az, float &angle) const
{
    ax = x;
    ay = y;
    az = z;
    angle = 2.0f * acos(w);
}

void Quaternion::convertToEulerAngles(float &roll, float &pitch, float &yaw) const
{
    roll = atan2((y * z) + (w * x), 0.5f - ((x * x) + (y * y)));
    pitch = asin(-2.0f * ((x * z) + (w * y)));
    yaw = atan2((x * y) + (w * z), 0.5f - ((y * y) + (z * z)));
}

float Quaternion::dot(const Quaternion &q) const
{
    return (w * q.w) + (x * q.x) + (y * q.y) + (z * q.z);
}

Quaternion Quaternion::inverse() const
{
    const float n = norm();
    if (n == 0.0f)
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
    Quaternion t = *this;
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

