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
    /**
     * @brief   Default constructor.
     * @details Initializes the quaternion to the quaternion identity. The
     *          identity represents no rotation.
     */
    Quaternion();

    /**
     * @brief   Copy constructor.
     * @details Copies the components of a quaternion into the new quaternion.
     *
     * @param[in] q The quaternion to copy from.
     */
    Quaternion(const Quaternion &q);

    /**
     * @brief   Initialization constructor.
     * @details Creates a quaternion with the specified values @p w, @p x,
     *          @p y, and @p z.
     *
     * @param[in] w The real scalar component.
     * @param[in] x The imaginary vector X axis component.
     * @param[in] y The imaginary vector Y axis component.
     * @param[in] z The imaginary vector Z axis component.
     */
    Quaternion(const float w, const float x, const float y, const float z);

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
    Quaternion conjugate() const;

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
    void convertToAxisAngle(float &wx, float &wy, float &wz, float &angle) const;

    /**
     * @brief   Converts the quaternion to Euler angles.
     * @details Converts from a quaternion representation of rotation to the
     *          equivalent set of Euler angles representing three dimensions
     *          of rotation.
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
    void convertToEulerAngles(float &roll, float &pitch, float &yaw) const;

    /**
     * @brief   Dot product multiplication.
     * @details Performs dot product multiplication on quaternions. For cross
     *          product multiplication, use the C++ operator for
     *          multiplication.
     * @f[
     *   a \cdot b = {a_0}{b_0} + {a_1}{b_1} + {a_2}{b_2} +{a_3}{b_3}
     * @f]
     * @see     Quaternion::operator*=()
     *
     * @param[in] q The quaternion to multiply by.
     * @return      The scalar dot product of two quaternions.
     */
    float dot(const Quaternion &q) const;

    /**
     * @brief   Computes the inverse.
     * @details The quaternion inverse is defined as a quaternion conjugate
     *          divided by the norm of the quaternion squared.
     * @f[
     *   q^{-1} = \frac{q^{*}}{\|q\|^{2}}
     * @f]
     *
     * @return If the norm is equal to zero, then the quaternion identity is
     *         returned. Otherwise, a copy of the quaternion inverse is
     *         returned.
     */
    Quaternion inverse() const;

    /**
     * @brief   Computes the norm.
     * @details The quaternion norm is defined as the square root of all of
     *          the quaternion components first squared and then added
     *          together.
     * @f[
     *   \|q\| = \sqrt{q_{0}^{2} + q_{1}^2 + q_{2}^{2} + q_{3}^{2}}
     * @f]
     *
     * @return The scalar norm or magnitude.
     */
    float norm() const;

    /**
     * @brief   Normalizes the quaternion.
     * @details Computes and sets the quaternion to be normalized. This
     *          produces a versor (unit quaternion).
     */
    void normalize();

    /**
     * @brief   Computes the normalized quaternion.
     * @details Computes what the normalized quaternion is but does not
     *          modify the internal structure of the quaternion this is
     *          invoked against.
     * @f[
     *   \hat{q} = \frac{q}{\|q\|}
     * @f]
     *
     * @return A copy of the quaternion versor.
     */
    Quaternion normalized() const;

    /**
     * @brief   Assignment operator.
     * @details Assigns the quaternion to have the same values for its
     *          components as another.
     *
     * @param[in] q The quaternion to set equal to.
     * @return      The assigned quaternion.
     */
    Quaternion &operator=(const Quaternion &q);

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
    Quaternion &operator+=(const Quaternion &q);

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
    Quaternion &operator-=(const Quaternion &q);

    /**
     * @brief   Compound scalar multiplication operator.
     * @details Compound multiplication between a quaternion and a scalar.
     *          The resulting quaternion represents the same rotation as
     *          before it was scaled.
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
    Quaternion &operator*=(float factor);

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
    Quaternion &operator*=(const Quaternion &q);

    /**
     * @brief   Compound scalar division operator.
     * @details Compound division between a quaternion and a scalar. The
     *          resulting quaternion represents the same rotation as before it
     *          was scaled.
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
 * @return       True if the two quaternions are identical. Otherwise, false.
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
 * @return       True if the two quaternions are not identical. Otherwise,
 *               false.
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
 * @return    The result of addition.
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

