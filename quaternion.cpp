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

/**
 * @brief   Default constructor.
 * @details Initializes the quaternion to the quaternion identity. The identity
 *          represents no rotation.
 */
Quaternion::Quaternion() :
    w(1.0f),
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

/**
 * @brief   Copy constructor.
 * @details Copies the components of a quaternion into the new quaternion.
 *
 * @param[in] q The quaternion to copy from.
 */
Quaternion::Quaternion(const Quaternion &q) :
    w(q.w),
    x(q.x),
    y(q.y),
    z(q.z)
{
}

/**
 * @brief   Initialization constructor.
 * @details Creates a quaternion with the specified values @p w, @p x, @p y,
 *          and @p z.
 *
 * @param[in] w The real scalar component.
 * @param[in] x The imaginary vector X axis component.
 * @param[in] y The imaginary vector Y axis component.
 * @param[in] z The imaginary vector Z axis component.
 */
Quaternion::Quaternion(const float w, const float x, const float y, const float z) :
    w(w),
    x(x),
    y(y),
    z(z)
{
}

/**
 * @brief   Computes the conjugate.
 * @details The quaternion conjugate is defined as a quaternion with its
 *          imaginary vector component negated.
 * @f[
 *   q^{*} = q_{0} - q_{1}i - q_{2}j - q_{3}k
 * @f]
 *
 * @return A copy of the quaternion conjugate.
 */
Quaternion Quaternion::conjugate() const
{
    return Quaternion(w, -x, -y, -z);
}

/**
 * @brief   Converts the quaternion to an axis-angle.
 * @details Converts from a quaternion representation of rotation to the
 *          equivalent axis-angle representation of rotation.
 * @f[
 *   \begin{aligned}
 *   q &= s + \vec{v} \\
 *   \theta &= 2 \arccos(s) \\
 *   \omega &= \begin{cases}
 *   \frac{\vec{v}}{\sin(\theta / 2)} & \text{if $\theta \neq 0$} \\
 *   0 & \text{otherwise}
 *   \end{cases}
 *   \end{aligned}
 * @f]
 * @pre The quaternion must be a versor (unit quaternion).
 *
 * @param[out] wx    The X position of the axis.
 * @param[out] wy    The Y position of the axis.
 * @param[out] wz    The Z position of the axis.
 * @param[out] angle The angle the axis is rotated by.
 */
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

/**
 * @brief   Converts the quaternion to Euler angles.
 * @details Converts from a quaternion representation of rotation to the
 *          equivalent set of Euler angles representing three dimensions of
 *          rotation.
 * @f[
 *   \begin{bmatrix} \phi \\ \theta \\ \psi \end{bmatrix} =
 *   \begin{bmatrix}
 *   \text{atan2}(2({q_0}{q_1} + {q_2}{q_3}),
 *   1 - 2(q_{1}^{2} + q_{2}^{2})) \\
 *   \arcsin(2({q_0}{q_2} - {q_3}{q_1})) \\
 *   \text{atan2}(2({q_0}{q_3} + {q_1}{q_2}),
 *   1 - 2(q_{2}^{2} + q_{3}^{2}))
 *   \end{bmatrix}
 * @f]
 * @pre The quaternion must be a versor (unit quaternion).
 *
 * @param[out] roll  The roll angle.
 * @param[out] pitch The pitch angle.
 * @param[out] yaw   The yaw angle.
 */
void Quaternion::convertToEulerAngles(float &roll, float &pitch, float &yaw) const
{
    roll = atan2(2.0f * ((w * x) + (y * z)), 1.0f - (2.0f * ((x * x) + (y * y))));
    pitch = asin(2.0f * ((w * y) - (z * x)));
    yaw = atan2(2.0f * ((w * z) + (x * y)), 1.0f - (2.0f * ((y * y) + (z * z))));
}

/**
 * @brief   Dot product multiplication.
 * @details Performs dot product multiplication on quaternions. For cross
 *          product multiplication, use the C++ operator for multiplication.
 * @f[
 *   a \cdot b = {a_0}{b_0} + {a_1}{b_1} + {a_2}{b_2} +{a_3}{b_3}
 * @f]
 * @see     Quaternion::operator*=()
 *
 * @param[in] q The quaternion to multiply by.
 * @return      The scalar dot product of two quaternions.
 */
float Quaternion::dot(const Quaternion &q) const
{
    return (w * q.w) + (x * q.x) + (y * q.y) + (z * q.z);
}

/**
 * @brief   Computes the inverse.
 * @details The quaternion inverse is defined as a quaternion conjugate
 *          divided by the norm of the quaternion squared.
 * @f[
 *   q^{-1} = \frac{q^{*}}{\|q\|^{2}}
 * @f]
 *
 * @retval inverse  The quaternion inverse.
 * @retval identity The quaternion identity if the norm is zero.
 * @return          The inverse or no rotation if the quaternion has a norm of
 *                  zero.
 */
Quaternion Quaternion::inverse() const
{
    const float n = norm();
    if (0.0f == n)
    {
        return Quaternion();
    }
    return conjugate() / (n * n);
}

/**
 * @brief   Computes the norm.
 * @details The quaternion norm is defined as the square root of all of the
 *          quaternion components first squared and then added together.
 * @f[
 *   \|q\| = \sqrt{q_{0}^{2} + q_{1}^2 + q_{2}^{2} + q_{3}^{2}}
 * @f]
 *
 * @return The scalar norm or magnitude.
 */
float Quaternion::norm() const
{
    return sqrt((w * w) + (x * x) + (y * y) + (z * z));
}

/**
 * @brief   Normalizes the quaternion.
 * @details Computes and sets the quaternion to be normalized. This produces a
 *          versor (unit quaternion).
 */
void Quaternion::normalize()
{
    *this /= norm();
}

/**
 * @brief   Computes the normalized quaternion.
 * @details Computes what the normalized quaternion is but does not modify the
 *          internal structure of the quaternion this is invoked against.
 * @f[
 *   \hat{q} = \frac{q}{\|q\|}
 * @f]
 *
 * @return A copy of the quaternion versor.
 */
Quaternion Quaternion::normalized() const
{
    return *this / norm();
}

/**
 * @brief   Assignment operator.
 * @details Assigns the quaternion to have the same values for its components
 *          as another.
 *
 * @param[in] q The quaternion to set equal to.
 * @return      The assigned quaternion.
 */
Quaternion &Quaternion::operator=(const Quaternion &q)
{
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
    return *this;
}

/**
 * @brief   Compound addition operator.
 * @details Compound addition between two quaternions.
 * @f[
 *   a + b = \begin{bmatrix}
 *   a_0 + b_0 &
 *   a_1 + b_1 &
 *   a_2 + b_2 &
 *   a_3 + b_3
 *   \end{bmatrix}
 * @f]
 *
 * @param[in] q The quaternion to add by.
 * @return      The result of addition.
 */
Quaternion &Quaternion::operator+=(const Quaternion &q)
{
    w += q.w;
    x += q.x;
    y += q.y;
    z += q.z;
    return *this;
}

/**
 * @brief   Compound subtraction operator.
 * @details Compound subtraction between two quaternions.
 * @f[
 *   a - b = \begin{bmatrix}
 *   a_0 - b_0 &
 *   a_1 - b_1 &
 *   a_2 - b_2 &
 *   a_3 - b_3
 *   \end{bmatrix}
 * @f]
 *
 * @param[in] q The quaternion to subtract by.
 * @return      The result of subtraction.
 */
Quaternion &Quaternion::operator-=(const Quaternion &q)
{
    w -= q.w;
    x -= q.x;
    y -= q.y;
    z -= q.z;
    return *this;
}

/**
 * @brief   Compound scalar multiplication operator.
 * @details Compound multiplication between a quaternion and a scalar. The
 *          resulting quaternion represents the same rotation as before it was
 *          scaled.
 * @f[
 *   q \times s = \begin{bmatrix}
 *   q_0 \times s &
 *   q_1 \times s &
 *   q_2 \times s &
 *   q_3 \times s
 *   \end{bmatrix}
 * @f]
 *
 * @param[in] factor The scalar factor to multiply by.
 * @return           The result of multiplication.
 */
Quaternion &Quaternion::operator*=(const float factor)
{
    w *= factor;
    x *= factor;
    y *= factor;
    z *= factor;
    return *this;
}

/**
 * @brief   Compound cross multiplication operator.
 * @details Compound cross multiplication between two quaternions. The
 *          resulting quaternion represents a new rotation.
 * @f[
 *   a \times b = \begin{bmatrix}
 *   {a_0}{b_0} - {a_1}{b_1} - {a_2}{b_2} - {a_3}{b_3} \\
 *   {a_0}{b_1} + {a_1}{b_0} + {a_2}{b_3} - {a_3}{b_2} \\
 *   {a_0}{b_2} - {a_1}{b_3} + {a_2}{b_0} + {a_3}{b_1} \\
 *   {a_0}{b_3} + {a_1}{b_2} - {a_2}{b_1} + {a_3}{b_0}
 *   \end{bmatrix}
 * @f]
 *
 * @param[in] q The quaternion to multiply by.
 * @return      The result of cross product multiplication.
 */
Quaternion &Quaternion::operator*=(const Quaternion &q)
{
    const Quaternion t = *this;
    w = (t.w * q.w) - (t.x * q.x) - (t.y * q.y) - (t.z * q.z);
    x = (t.w * q.x) + (t.x * q.w) + (t.y * q.z) - (t.z * q.y);
    y = (t.w * q.y) - (t.x * q.z) + (t.y * q.w) + (t.z * q.x);
    z = (t.w * q.z) + (t.x * q.y) - (t.y * q.x) + (t.z * q.w);
    return *this;
}

/**
 * @brief   Compound scalar division operator.
 * @details Compound division between a quaternion and a scalar. The resulting
 *          quaternion represents the same rotation as before it was scaled.
 * @f[
 *   \frac{q}{s} = \begin{bmatrix}
 *   \frac{q_0}{s} &
 *   \frac{q_1}{s} &
 *   \frac{q_2}{s} &
 *   \frac{q_3}{s}
 *   \end{bmatrix}
 * @f]
 *
 * @param[in] divisor The scalar divisor to divide by.
 * @return            The result of division.
 */
Quaternion &Quaternion::operator/=(const float divisor)
{
    w /= divisor;
    x /= divisor;
    y /= divisor;
    z /= divisor;
    return *this;
}
