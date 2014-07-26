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

#ifndef QUATERNION_H
#define QUATERNION_H

struct Quaternion
{
    Quaternion();
    Quaternion(const Quaternion &q);
    Quaternion(float scalar, float x, float y, float z);
    Quaternion conjugate() const;
    void convertToAxisAngle(float &ax, float &ay, float &az, float &angle);
    void convertToEulerAngles(float &roll, float &pitch, float &yaw);
    float dot(const Quaternion &q) const;
    Quaternion inverse() const;
    float norm() const;
    void normalize();
    Quaternion normalized() const;
    Quaternion &operator=(const Quaternion &q);
    Quaternion &operator+=(const Quaternion &q);
    Quaternion &operator-=(const Quaternion &q);
    Quaternion &operator*=(float factor);
    Quaternion &operator*=(const Quaternion &q);
    Quaternion &operator/=(float divisor);

    friend inline bool operator==(const Quaternion &q1, const Quaternion &q2);
    friend inline bool operator!=(const Quaternion &q1, const Quaternion &q2);
    friend inline const Quaternion operator+(Quaternion q1, const Quaternion &q2);
    friend inline const Quaternion operator-(const Quaternion &q);
    friend inline const Quaternion operator-(Quaternion q1, const Quaternion &q2);
    friend inline const Quaternion operator*(float factor, Quaternion q);
    friend inline const Quaternion operator*(Quaternion q, float factor);
    friend inline const Quaternion operator*(Quaternion q1, const Quaternion &q2);
    friend inline const Quaternion operator/(Quaternion q, float divisor);

    float scalar;
    float x;
    float y;
    float z;
};

inline bool operator==(const Quaternion &q1, const Quaternion &q2)
{
    return (q1.scalar == q2.scalar) && (q1.x == q2.x) && (q1.y == q2.y) && (q1.z == q2.z);
}

inline bool operator!=(const Quaternion &q1, const Quaternion &q2)
{
    return !operator==(q1, q2);
}

inline const Quaternion operator+(Quaternion q1, const Quaternion &q2)
{
    q1 += q2;
    return q1;
}

inline const Quaternion operator-(const Quaternion &q)
{
    return Quaternion(-q.scalar, -q.x, -q.y, -q.z);
}

inline const Quaternion operator-(Quaternion q1, const Quaternion &q2)
{
    q1 -= q2;
    return q1;
}

inline const Quaternion operator*(float factor, Quaternion q)
{
    q *= factor;
    return q;
}

inline const Quaternion operator*(Quaternion q, float factor)
{
    q *= factor;
    return q;
}

inline const Quaternion operator*(Quaternion q1, const Quaternion &q2)
{
    q1 *= q2;
    return q1;
}

inline const Quaternion operator/(Quaternion q, float divisor)
{
    q /= divisor;
    return q;
}

#endif // QUATERNION_H

