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

#include "q.h"

Quaternion::Quaternion() :
    scalar(1.0f),
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

Quaternion::Quaternion(const Quaternion &q) :
    scalar(q.scalar),
    x(q.x),
    y(q.y),
    z(q.z)
{
}

Quaternion::Quaternion(float scalar, float x, float y, float z) :
    scalar(scalar),
    x(x),
    y(y),
    z(z)
{
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion(scalar, -x, -y, -z);
}

float dot(const Quaternion &q) const
{
    return (scalar * q.scalar) + (x * q.x) + (y * q.y) + (z * q.z);
}

Quaternion inverse() const
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
    return sqrt((scalar * scalar) + (x * x) + (y * y) + (z * z));
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
    scalar = q.scalar;
    x = q.x;
    y = q.y;
    z = q.z;
    return *this;
}

Quaternion &Quaternion::operator+=(const Quaternion &q)
{
    scalar += q.scalar;
    x += q.x;
    y += q.y;
    z += q.z;
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &q)
{
    scalar -= q.scalar;
    x -= q.x;
    y -= q.y;
    z -= q.z;
    return *this;
}

Quaternion &Quaternion::operator*=(float factor)
{
    scalar *= factor;
    x *= factor;
    y *= factor;
    z *= factor;
    return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &q)
{
    scalar = (scalar * q.scalar) - (x * q.x) - (y * q.y) - (z * q.z);
    x = (scalar * q.x) + (x * q.scalar) + (y * q.z) - (z * q.y);
    y = (scalar * q.y) - (x * q.z) + (y * q.scalar) + (z * q.x);
    z = (scalar * q.z) + (x * q.y) - (y * q.x) + (z * q.scalar);
}

Quaternion &Quaternion::operator/=(float divisor)
{
    scalar /= divisor;
    x /= divisor;
    y /= divisor;
    z /= divisor;
    return *this;
}

