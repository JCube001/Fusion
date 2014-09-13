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
 * @file quaternion.h
 * @brief Quaternion mathematics structure.
 */

#ifndef QUATERNION_H
#define QUATERNION_H

/**
 * @brief   Quaternion.
 * @details A quaternion is a four-dimensional vector space over the real
 *          numbers. They are a number system which extends the complex
 *          numbers.
 */
struct Quaternion
{
    Quaternion();
    Quaternion(const Quaternion &q);
    Quaternion(const float w, const float x, const float y, const float z);
    Quaternion conjugate() const;
    void convertToAxisAngle(float &wx, float &wy, float &wz, float &angle) const;
    void convertToEulerAngles(float &roll, float &pitch, float &yaw) const;
    float dot(const Quaternion &q) const;
    Quaternion inverse() const;
    float norm() const;
    void normalize();
    Quaternion normalized() const;
    Quaternion &operator=(const Quaternion &q);
    Quaternion &operator+=(const Quaternion &q);
    Quaternion &operator-=(const Quaternion &q);
    Quaternion &operator*=(const float factor);
    Quaternion &operator*=(const Quaternion &q);
    Quaternion &operator/=(const float divisor);

    friend inline bool operator==(const Quaternion &q1, const Quaternion &q2);
    friend inline bool operator!=(const Quaternion &q1, const Quaternion &q2);
    friend inline const Quaternion operator+(Quaternion q1, const Quaternion &q2);
    friend inline const Quaternion operator-(const Quaternion &q);
    friend inline const Quaternion operator-(Quaternion q1, const Quaternion &q2);
    friend inline const Quaternion operator*(float factor, Quaternion q);
    friend inline const Quaternion operator*(Quaternion q, float factor);
    friend inline const Quaternion operator*(Quaternion q1, const Quaternion &q2);
    friend inline const Quaternion operator/(Quaternion q, float divisor);

    float w; /**< The real scalar component */
    float x; /**< The imaginary vector X axis component */
    float y; /**< The imaginary vector Y axis component */
    float z; /**< The imaginary vector Z axis component */
};

/**
 * @brief   Equality operator.
 * @details Tests for equality between two quaternions by comparing each of
 *          their corresponding components.
 * @note    A quaternion will represent the same rotation after it has been
 *          negated. However, the way the equality operator is implemented
 *          will cause a comparison between a quaternion and its negated self
 *          to always return false. This is because this function only tests
 *          if each component is exactly equal.
 *
 * @param[in] q1 The left side quaternion operand.
 * @param[in] q2 The right side quaternion operand.
 * @retval true  If the two quaternions are identical.
 * @retval false Otherwise.
 * @return       The result of the equality test.
 */
inline bool operator==(const Quaternion &q1, const Quaternion &q2)
{
    return (q1.w == q2.w) && (q1.x == q2.x) && (q1.y == q2.y) && (q1.z == q2.z);
}

/**
 * @brief   Inequality operator.
 * @details Tests for inequality between two quaternions by comparing each of
 *          their corresponding components.
 * @see     operator==(Quaternion, Quaternion)
 *
 * @param[in] q1 The left side quaternion operand.
 * @param[in] q2 The right side quaternion operand.
 * @retval true  If the two quaternions are not identical.
 * @retval false Otherwise.
 * @return       The result of the inequality test.
 */
inline bool operator!=(const Quaternion &q1, const Quaternion &q2)
{
    return !operator==(q1, q2);
}

/**
 * @brief   Addition operator.
 * @details Performs addition between two quaternions.
 * @see     Quaternion::operator+=(Quaternion)
 *
 * @param[in] q1 The left side quaternion operand.
 * @param[in] q2 The right side quaternion operand.
 * @return       The result of addition.
 */
inline const Quaternion operator+(Quaternion q1, const Quaternion &q2)
{
    q1 += q2;
    return q1;
}

/**
 * @brief   Negation operator.
 * @details Negates the quaternion by negating each of its components.
 * @f[
 *   -q = \begin{bmatrix}
 *   -q_0 & -q_1 & -q_2 & -q_3
 *   \end{bmatrix}
 * @f]
 *
 * @param[in] q The quaternion to negate.
 * @return      The negated quaternion.
 */
inline const Quaternion operator-(const Quaternion &q)
{
    return Quaternion(-q.w, -q.x, -q.y, -q.z);
}

/**
 * @brief   Subtraction operator.
 * @details Performs subtraction between two quaternions.
 * @see     Quaternion::operator-=(Quaternion)
 *
 * @param[in] q1 The left side quaternion.
 * @param[in] q2 The right side quaternion.
 * @return       The result of subtraction.
 */
inline const Quaternion operator-(Quaternion q1, const Quaternion &q2)
{
    q1 -= q2;
    return q1;
}

/**
 * @brief   Scalar multiplication operator.
 * @details Performs scalar multiplication between a quaternion and a scalar.
 * @see     Quaternion::operator*=(float)
 *
 * @param[in] factor The left side scalar.
 * @param[in] q      The right side quaternion.
 * @return           The result of multiplication.
 */
inline const Quaternion operator*(float factor, Quaternion q)
{
    q *= factor;
    return q;
}

/**
 * @brief   Scalar multiplication operator.
 * @details Performs scalar multiplication between a quaternion and a scalar.
 * @see     Quaternion::operator*=(float)
 *
 * @param[in] q      The left side quaternion.
 * @param[in] factor The right side scalar.
 * @return           The result of multiplication.
 */
inline const Quaternion operator*(Quaternion q, float factor)
{
    q *= factor;
    return q;
}

/**
 * @brief   Cross product multiplication operator.
 * @details Performs cross product multiplication between two quaternions.
 * @see     Quaternion::operator*=(Quaternion)
 *
 * @param[in] q1 The left side quaternion.
 * @param[in] q2 The right side quaternion.
 * @return       The result of multiplication.
 */
inline const Quaternion operator*(Quaternion q1, const Quaternion &q2)
{
    q1 *= q2;
    return q1;
}

/**
 * @brief   Scalar division operator.
 * @details Performs scalar division between a quaternion and a scalar.
 * @see     Quaternion::operator/=(float)
 *
 * @param[in] q       The left side quaternion.
 * @param[in] divisor The right side divisor.
 * @return            The result of division.
 */
inline const Quaternion operator/(Quaternion q, float divisor)
{
    q /= divisor;
    return q;
}

#endif // QUATERNION_H

