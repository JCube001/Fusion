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

#ifndef UTILITY_VECTOR_H_
#define UTILITY_VECTOR_H_

#include <math.h>
#include "math_extra.h"

namespace fusion {

/**
 * @brief Vector. Three dimensional vector.
 */
class Vector3 {
 public:
  /**
   * @brief Default constructor.
   */
  Vector3() {
    data_[0] = 0.0f;
    data_[1] = 0.0f;
    data_[2] = 0.0f;
  }

  /**
   * @brief Copy constructor.
   *
   * @param other The vector to copy from.
   */
  Vector3(const Vector3& other) {
    data_[0] = other.x();
    data_[1] = other.y();
    data_[2] = other.z();
  }

  /**
   * @brief Array initialization constructor.
   *
   * @param array The array to store as vector components.
   */
  explicit Vector3(const float* array) {
    for (int i = 0; i < 3; i++) {
      data_[i] = array[i];
    }
  }

  /**
   * @brief Initialization constructor.
   *
   * @param x The x-value component.
   * @param y The y-value component.
   * @param z The z-value component.
   */
  Vector3(float x, float y, float z) {
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
  }

  /**
   * @brief Destructor.
   */
  ~Vector3() {}

  /**
   * @brief Mutate all components.
   *
   * @param x The new vector x-component.
   * @param y The new vector y-component.
   * @param z The new vector z-component.
   */
  void set(float x, float y, float z) {
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
  }

  /**
   * @brief Return the vector x-component.
   *
   * @return The vector x-component.
   */
  float x() const { return data_[0]; }

  /**
   * @brief Return the vector y-component.
   *
   * @return The vector y-component.
   */
  float y() const { return data_[1]; }

  /**
   * @brief Return the vector z-component.
   *
   * @return The vector z-component.
   */
  float z() const { return data_[2]; }

  /**
   * @brief Assignment.
   *
   * @param rhs The right hand side vector to assign.
   * @return The assigned vector.
   */
  Vector3& operator=(Vector3 rhs) {
    swap(*this, rhs);
    return *this;
  }

  /**
   * @brief Subscript accessor.
   *
   * @param i The index of the vector component to access.
   * @return The value of the vector component stored at the index.
   */
  const float operator[](int i) const {
    return data_[i];
  }

  /**
   * @brief Subscript mutator.
   *
   * @param i The index of the vector component to mutate.
   * @return The value of the vector component stored at the index.
   */
  float operator[](int i) {
    return data_[i];
  }

  /**
   * @brief Compound addition.
   *
   * @param rhs The right hand side vector to add.
   * @return The sum of the vectors.
   */
  Vector3& operator+=(const Vector3& rhs) {
    this->data_[0] += rhs.x();
    this->data_[1] += rhs.y();
    this->data_[2] += rhs.z();
    return *this;
  }

  /**
   * @brief Compound subtraction.
   *
   * @param rhs The right hand side vector to subtract by.
   * @return The difference of the vectors.
   */
  Vector3& operator-=(const Vector3& rhs) {
    this->data_[0] -= rhs.x();
    this->data_[1] -= rhs.y();
    this->data_[2] -= rhs.z();
    return *this;
  }

  /**
   * @brief Compound scalar multiplication.
   *
   * @param rhs The right hand side scalar value to multiply by.
   * @return The product of the vector times the scalar.
   */
  Vector3& operator*=(const float rhs) {
    this->data_[0] *= rhs;
    this->data_[1] *= rhs;
    this->data_[2] *= rhs;
    return *this;
  }

  /**
   * @brief Compound cross product multiplication.
   *
   * @param rhs The right hand side vector to multiply by.
   * @return The cross product of the vectors.
   */
  Vector3& operator*=(const Vector3& rhs) {
    this->data_[0] = y()*rhs.z() - z()*rhs.y();
    this->data_[1] = z()*rhs.x() - x()*rhs.z();
    this->data_[2] = x()*rhs.y() - y()*rhs.x();
    return *this;
  }

  /**
   * @brief Compound scalar division.
   *
   * @param rhs The right hand side scalar value to divide by.
   * @return The quotient of the vector divided by the scalar.
   */
  Vector3& operator/=(const float rhs) {
    this->data_[0] /= rhs;
    this->data_[1] /= rhs;
    this->data_[2] /= rhs;
    return *this;
  }

  // Related non-member functions.
  friend Vector3 operator+(Vector3 lhs, const Vector3& rhs);
  friend Vector3 operator-(Vector3 lhs, const Vector3& rhs);
  friend Vector3 operator-(const Vector3& rhs);
  friend Vector3 operator*(float lhs, Vector3 rhs);
  friend Vector3 operator*(Vector3 lhs, float rhs);
  friend Vector3 operator*(Vector3 lhs, const Vector3& rhs);
  friend Vector3 operator/(Vector3 lhs, float rhs);
  friend bool operator==(const Vector3& lhs, const Vector3& rhs);
  friend bool operator!=(const Vector3& lhs, const Vector3& rhs);
  friend bool operator<(const Vector3& lhs, const Vector3& rhs);
  friend bool operator>(const Vector3& lhs, const Vector3& rhs);
  friend bool operator<=(const Vector3& lhs, const Vector3& rhs);
  friend bool operator>=(const Vector3& lhs, const Vector3& rhs);

  /**
   * @brief Dot product multiplication.
   *
   * @param p0 The left hand side vector.
   * @param p1 The right hand side vector.
   * @return The scalar product of two vectors.
   */
  static float dot(const Vector3& p0, const Vector3& p1) {
    return p0.x()*p1.x() + p0.y()*p1.y() + p0.z()*p1.z();
  }

  /**
   * @brief Normalizes the vector.
   *
   * @note Makes use of the inverse square root to be able to avoid division
   *       operations entirely.
   */
  void fastNormalize() {
    *this *= invSqrt(x()*x() + y()*y() + z()*z());
  }

  /**
   * @brief Returns a normalized (unit) vector.
   *
   * @return The normalized vector.
   *
   * @note Makes use of the inverse square root to be able to avoid division
   *       operations entirely.
   */
  Vector3 fastNormalized() const {
    return *this * invSqrt(x()*x() + y()*y() + z()*z());
  }

  /**
   * @brief Performs a linear interpolation between two vectors.
   *
   * @param p0 The start vector.
   * @param p1 The end vector.
   * @param t A value between 0 and 1 indicating the weight of the end vector.
   * @return The linear interpolation between two vectors.
   */
  static Vector3 lerp(const Vector3& p0, const Vector3& p1, const float t) {
    return p0*(1.0f - t) + p1*t;
  }

  /**
   * @brief Scalar triple product multiplication.
   *
   * @param p0 The vector to obtain the dot product from.
   * @param p1 The vector to cross multiply with p2.
   * @param p2 The vector to cross multiply with p1.
   * @return The scalar triple product of the three vectors.
   */
  static float tripleProduct(const Vector3& p0, const Vector3& p1,
                             const Vector3& p2) {
    return Vector3::dot(p0, p1*p2);
  }

  /**
   * @brief Performs a normalized linear interpolation between two vectors.
   *
   * @param p0 The start vector.
   * @param p1 The end vector.
   * @param t A value between 0 and 1 indicating the weight of the end vector.
   * @return The normalized linear interpolation between two vectors.
   */
  static Vector3 nlerp(const Vector3& p0, const Vector3& p1, const float t) {
    return Vector3::lerp(p0, p1, t).normalized();
  }

  /**
   * @brief Returns the norm (magnitude) of the vector.
   *
   * @return The scalar norm of the vector.
   */
  float norm() const {
    return sqrt(x()*x() + y()*y() + z()*z());
  }

  /**
   * @brief Normalizes the vector.
   */
  void normalize() {
    *this /= norm();
  }

  /**
   * @brief Returns a normalized (unit) vector.
   *
   * @return The normalized vector.
   */
  Vector3 normalized() const {
    return *this / norm();
  }

  /**
   * @brief Performs a spherical linear interpolation between two vectors.
   *
   * @param p0 The start vector.
   * @param p1 The end vector.
   * @param t A value between 0 and 1 indicating the weight of the end vector.
   * @return The spherical linear interpolation between two vectors defined as
   *         Slerp(p0, p1; t) = (sin((1-t)o) / sin(o))(p0 hat) +
   *         (sin(to) / sin(o))(p1 hat) where o = acos(cos(o)) =
   *         acos((p0 hat).(p1 hat)).
   */
  static Vector3 slerp(const Vector3& p0, const Vector3& p1, const float t) {
    // Vectors must be normalized to work with angle calculations.
    Vector3 pp0 = p0.normalized();
    Vector3 pp1 = p1.normalized();

    // Calculate omega (the angle between p0 and p1).
    const float o = acos(Vector3::dot(pp0, pp1));

    // A number approaching zero.
    const float lim = 1.0e-5f;

    // Check if omega is approaching zero before performing the Slerp.
    if (!(-lim <= o && o <= lim)) {
      const float so = sin(o);
      return (sin((1.0f - t)*o) / so)*pp0 + (sin(t*o) / so)*pp1;
    }

    // The angle is too small, use Lerp.
    return Vector3::lerp(pp0, pp1, t);
  }

  /**
   * @brief Swap the states between two vectors.
   *
   * @param p0 The first vector.
   * @param p1 The vector to swap with.
   */
  friend void swap(Vector3& p0, Vector3& p1) {
    Vector3 temp;

    // Set temp equal to the state of p0.
    temp.data_[0] = p0.data_[0];
    temp.data_[1] = p0.data_[1];
    temp.data_[2] = p0.data_[2];

    // Set p0 equal to the state of p1.
    p0.data_[0] = p1.data_[0];
    p0.data_[1] = p1.data_[1];
    p0.data_[2] = p1.data_[2];

    // Set p1 equal to the state of temp.
    p1.data_[0] = temp.data_[0];
    p1.data_[1] = temp.data_[1];
    p1.data_[2] = temp.data_[2];
  }

 protected:
  float data_[3];
};

}  // namespace fusion

#endif  // UTILITY_VECTOR_H_
