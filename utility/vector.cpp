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

#include "vector.h"

namespace fusion {

/**
 * @brief Addition.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector to add.
 * @return The sum of the vectors.
 */
inline Vector3 operator+(Vector3 lhs, const Vector3& rhs) {
  lhs += rhs;
  return lhs;
}

/**
 * @brief Subtraction.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector to subtract by.
 * @return The difference of the vectors.
 */
inline Vector3 operator-(Vector3 lhs, const Vector3& rhs) {
  lhs -= rhs;
  return lhs;
}

/**
 * @brief Unary negation.
 *
 * @return The negated vector.
 */
inline Vector3 operator-(const Vector3& rhs) {
  return Vector3(-rhs.x(), -rhs.y(), -rhs.z());
}

/**
 * @brief Scalar multiplication.
 *
 * @param lhs The left hand side scalar to multiply by.
 * @param rhs The right hand side vector.
 * @return The product of the vector times the scalar.
 */
inline Vector3 operator*(float lhs, Vector3 rhs) {
  rhs *= lhs;
  return rhs;
}

/**
 * @brief Scalar multiplication.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side scalar to multiply by.
 * @return The product of the vector times the scalar.
 */
inline Vector3 operator*(Vector3 lhs, float rhs) {
  lhs *= rhs;
  return lhs;
}

/**
 * @brief Cross product multiplication.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector to multiply by.
 * @return The cross product of the vectors.
 */
inline Vector3 operator*(Vector3 lhs, const Vector3& rhs) {
  lhs *= rhs;
  return lhs;
}

/**
 * @brief Scalar division.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side scalar value to divide by.
 * @return The quotient of the vector divided by the scalar.
 */
inline Vector3 operator/(Vector3 lhs, float rhs) {
  lhs /= rhs;
  return lhs;
}

/**
 * @brief Equal to.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector.
 * @return True if both vectors are equal, otherwise false.
 */
inline bool operator==(const Vector3& lhs, const Vector3& rhs) {
  return ((lhs.x() == rhs.x()) &&
          (lhs.y() == rhs.y()) &&
          (lhs.z() == rhs.z()));
}

/**
 * @brief Not equal to.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector.
 * @return True if both vectors are not equal, otherwise false.
 */
inline bool operator!=(const Vector3& lhs, const Vector3& rhs) {
  return !operator==(lhs, rhs);
}

/**
 * @brief Less than.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector.
 * @return True if the left hand side norm is less than the right hand side
 *         norm, otherwise false.
 */
inline bool operator<(const Vector3& lhs, const Vector3& rhs) {
  return (lhs.norm() < rhs.norm());
}

/**
 * @brief Greater than.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector.
 * @return True if the left hand side norm is greater than the right hand side
 *         norm, otherwise false.
 */
inline bool operator>(const Vector3& lhs, const Vector3& rhs) {
  return operator<(rhs, lhs);
}

/**
 * @brief Less than or equal to.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector.
 * @return True if the left hand side norm is less than or equal to the right
 *         hand side norm, otherwise false. 
 */
inline bool operator<=(const Vector3& lhs, const Vector3& rhs) {
  return !operator>(lhs, rhs);
}

/**
 * @brief Greater than or equal to.
 *
 * @param lhs The left hand side vector.
 * @param rhs The right hand side vector.
 * @return True if the left hand side norm is greater than or equal to the
 *         right hand side norm, otherwise false. 
 */
inline bool operator>=(const Vector3& lhs, const Vector3& rhs) {
  return !operator<(lhs, rhs);
}

}  // namespace fusion
