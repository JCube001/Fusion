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

#include "quaternion.h"

namespace fusion {

/**
 * @brief Addition.
 *
 * @param lhs The left hand side quaternion.
 * @param rhs The right hand side quaternion to add.
 * @return The sum of the quaternions.
 */
inline Quaternion operator+(Quaternion lhs, const Quaternion& rhs) {
  lhs += rhs;
  return lhs;
}

/**
 * @brief Subtraction.
 *
 * @param lhs The left hand side quaternion.
 * @param rhs The right hand side quaternion to subtract by.
 * @return The difference of the quaternions.
 */
inline Quaternion operator-(Quaternion lhs, const Quaternion& rhs) {
  lhs -= rhs;
  return lhs;
}

/**
 * @brief Unary negation.
 *
 * @param rhs The quaternion to negate.
 * @return The negated quaternion.
 *
 * @note A negated quaternion represents the same orientation.
 */
inline Quaternion operator-(const Quaternion& rhs) {
  return Quaternion(-rhs.scalar(), -rhs.vector());
}

/**
 * @brief Scalar multiplication.
 *
 * @param lhs The left hand side scalar.
 * @param rhs The right hand side quaternion to multiply by.
 * @return The product of the quaternion times the scalar.
 */
inline Quaternion operator*(float lhs, Quaternion rhs) {
  rhs *= lhs;
  return rhs;
}

/**
 * @brief Scalar multiplication.
 *
 * @param lhs The left hand side quaternion.
 * @param rhs The right hand side scalar to multiply by.
 * @return The product of the quaternion times the scalar.
 */
inline Quaternion operator*(Quaternion lhs, float rhs) {
  lhs *= rhs;
  return lhs;
}

/**
 * @brief Cross product multiplication.
 *
 * @param lhs The left hand side quaternion.
 * @param rhs The right hand side quaternion to multiply by.
 * @return The cross product of the quaternions.
 */
inline Quaternion operator*(Quaternion lhs, const Quaternion& rhs) {
  lhs *= rhs;
  return lhs;
}

/**
 * @brief Scalar division.
 *
 * @param lhs The left hand side quaternion.
 * @param rhs The right hand side scalar value to divide by.
 * @return The quotient of the quaternion divided by the scalar.
 */
inline Quaternion operator/(Quaternion lhs, float rhs) {
  lhs /= rhs;
  return lhs;
}

/**
 * @brief Division.
 *
 * @param lhs The left hand side quaternion.
 * @param rhs The right hand side quaternion to divide by.
 * @return The quotient of the quaternions.
 */
inline Quaternion operator/(Quaternion lhs, const Quaternion& rhs) {
  lhs /= rhs;
  return lhs;
}

/**
 * @brief Equal to.
 *
 * @param lhs The left hand side quaternion.
 * @param rhs The right hand side quaternion.
 * @return True if both quaternions are equal, otherwise false.
 */
inline bool operator==(const Quaternion& lhs, const Quaternion& rhs) {
  return ((lhs.scalar() == rhs.scalar()) && (lhs.vector() == rhs.vector()));
}

/**
 * @brief Not equal to.
 *
 * @param lhs The left hand side quaternion.
 * @param rhs The right hand side quaternion.
 * @return True if both quaternions are not equal, otherwise false.
 */
inline bool operator!=(const Quaternion& lhs, const Quaternion& rhs) {
  return !operator==(lhs, rhs);
}

}  // namespace fusion
