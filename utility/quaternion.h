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

#ifndef UTILITY_QUATERNION_H_
#define UTILITY_QUATERNION_H_

#include <math.h>
#include "utility/vector.h"

/**
 * @brief Quaternion. A structure composed of three imaginary vectorial
 *        components and one real component. The vector represents the axis
 *        while the scalar represents the angle of rotation on that axis.
 *
 * @note There are two common ways to store the structure of a quaternion. They
 *       are [w, x, y, z] and [x, y, z, w] where w is the real component and
 *       [x, y, z] is the imaginary vector component. The layout [x, y, z, w]
 *       was choosen for this particular class because it makes it easier to
 *       work with the vectorial components as an array.
 * @note All angles are treated as radians.
 */
class Quaternion {
 public:
  /**
   * @brief Default constructor.
   */
  Quaternion() : _data {0.0f, 0.0f, 0.0f, 0.0f} {}

  /**
   * @brief Copy constructor.
   *
   * @param other The quaternion to copy from.
   */
  Quaternion(const Quaternion& other)
    : _data {other.x(), other.y(), other.z(), other.w()} {}

  /**
   * @brief Component initialization constructor.
   *
   * @param v The imaginary vectorial component.
   * @param s The scalar real component.
   */
  Quaternion(const Vector3& v, const float s)
    : _data {v.x(), v.y(), v.z(), s} {}

  /**
   * @brief Array initialization constructor.
   *
   * @param array The array to store as quaternion components. Should be in
   *        the order of [x, y, z, w].
   */
  explicit Quaternion(const float* array) {
    for (int i = 0; i < 4; i++) {
      _data[i] = array[i];
    }
  }

  /**
   * @brief Initialization constructor.
   *
   * @param x The x-value of the imaginary vector component.
   * @param y The y-value of the imaginary vector component.
   * @param z The z-value of the imaginary vector component.
   * @param w The real component.
   */
  Quaternion(const float x, const float y, const float z, const float w)
    : _data {x, y, z, w} {}

  /**
   * @brief Destructor.
   */
  ~Quaternion() {}

  /**
   * @brief Return the quaternion x-component.
   *
   * @return The quaternion x-component.
   */
  float x() const { return _data[0]; }

  /**
   * @brief Return the quaternion y-component.
   *
   * @return The quaternion y-component.
   */
  float y() const { return _data[1]; }

  /**
   * @brief Return the quaternion z-component.
   *
   * @return The quaternion z-component.
   */
  float z() const { return _data[2]; }

  /**
   * @brief Return the quaternion w-component.
   *
   * @return The quaternion w-component.
   */
  float w() const { return scalar(); }

  /**
   * @brief Return the quaternion scalar component.
   *
   * @return The quaternion scalar component.
   */
  float scalar() const { return _data[3]; }

  /**
   * @brief Set the quaternion scalar component.
   */
  void scalar(const float s) { _data[3] = s; }

  /**
   * @brief Return the quaternion vector component.
   *
   * @return The quaternion vector component.
   */
  Vector3 vector() const { return Vector3(_data); }

  /**
   * @brief Set the quaternion vector component.
   */
  void vector(const Vector3& v) {
    for (int i = 0; i < 3; i++) {
      _data[i] = v[i];
    }
  }

  /**
   * @brief Subscript.
   *
   * @param i The index of the quaternion component to access.
   * @return The value of the quaternion component stored at the index.
   */
  inline float operator[](const int i) const {
    return _data[i];
  }

  /**
   * @brief Assignment.
   *
   * @param rhs The right hand side quaternion to assign.
   * @return The assigned quaternion.
   */
  inline Quaternion operator=(const Quaternion& rhs) const {
    return Quaternion(rhs.vector(), rhs.scalar());
  }

  /**
   * @brief Unary negation.
   *
   * @return The negated quaternion.
   */
  inline Quaternion operator-() const {
    return Quaternion(-vector(), -scalar());
  }

  /**
   * @brief Addition.
   *
   * @param rhs The right hand side quaternion to add.
   * @return The sum of the quaternions.
   */
  Quaternion operator+(const Quaternion& rhs) const {
    return Quaternion(vector() + rhs.vector(), scalar() + rhs.scalar());
  }

  /**
   * @brief Subtraction.
   *
   * @param rhs The right hand side quaternion to subtract by.
   * @return The difference of the quaternions.
   */
  Quaternion operator-(const Quaternion& rhs) const {
    return Quaternion(vector() - rhs.vector(), scalar() - rhs.scalar());
  }

  /**
   * @brief Cross product multiplication.
   *
   * @param rhs The right hand side quaternion to multiply by.
   * @return The cross product of the quaternions defined as
   *         q1q2 = [v2s1 + v1s2 + v1v2, s1s2 - v1.v2].
   */
  Quaternion operator*(const Quaternion& rhs) const {
    return Quaternion(rhs.vector()*scalar() + vector()*rhs.scalar() +
                      vector()*rhs.vector(),
                      scalar()*rhs.scalar() - Vector3::dot(vector(),
                      rhs.vector()));
  }

  /**
   * @brief Scalar multiplication.
   *
   * @param rhs The right hand side scalar value to multiply by.
   * @return The product of the quaternion times the scalar.
   */
  Quaternion operator*(const float rhs) const {
    return Quaternion(vector()*rhs, scalar()*rhs);
  }

  /**
   * @brief Division.
   *
   * @param rhs The right hand side quaternion to divide by.
   * @return The quotient of the quaternions defined as q1 / q2 = q1q2^-1.
   */
  Quaternion operator/(const Quaternion& rhs) const {
    return (*this) * rhs.inverse();
  }

  /**
   * @brief Scalar division.
   *
   * @param rhs The right hand side scalar value to divide by.
   * @return The quotient of the quaternion divided by the scalar.
   */
  Quaternion operator/(const float rhs) const {
    return Quaternion(vector() / rhs, scalar() / rhs);
  }

  /**
   * @brief Equal to.
   *
   * @param rhs The right hand side quaternion.
   * @return True if both quaternions are equal, otherwise false.
   */
  inline bool operator==(const Quaternion& rhs) const {
    return ((vector() == rhs.vector()) && (scalar() == rhs.scalar()));
  }

  /**
   * @brief Not equal to.
   *
   * @param rhs The right hand side quaternion.
   * @return True if both quaternions are not equal, otherwise false.
   */
  inline bool operator!=(const Quaternion& rhs) const {
    return !((*this) == rhs);
  }

  /**
   * @brief Returns the quaternion conjugate.
   *
   * @return The conjugate of the quaternion defined as q* = [-v, s].
   */
  Quaternion conjugate() const {
    return Quaternion(-vector(), scalar());
  }

  /**
   * @brief Dot product multiplication.
   *
   * @param a The left hand side quaternion.
   * @param b The right hand side quaternion.
   * @return The scalar product of two quaternions defined as
   *         q1.q2 = [v1.v2 + s1s2].
   */
  static float dot(const Quaternion& a, const Quaternion& b) {
    return Vector3::dot(a.vector(), b.vector()) + a.scalar()*b.scalar();
  }

  /**
   * @brief Returns the quaternion identity.
   *
   * @return The identity of the quaternion defined as q = [0, 0, 0, 1].
   */
  static Quaternion identity() {
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
  }

  /**
   * @brief Returns the quaternion inverse.
   *
   * @return The inverse of the quaternion defined as q^-1 = q* / ||q||^2.
   */
  Quaternion inverse() const {
    float n = norm();
    return conjugate() / (n*n);
  }

  /**
   * @brief Performs a linear interpolation between two quaternions.
   *
   * @param a The start quaternion.
   * @param b The end quaternion.
   * @param amount A value between 0 and 1 indicating the weight of the end
   *        quaternion.
   * @return The linear interpolation between two quaternions.
   */
  static Quaternion lerp(const Quaternion& a, const Quaternion& b,
                         const float amount) {
    return a + (b - a)*amount;
  }

  /**
   * @brief Performs a normalized linear interpolation between two
   *        quaternions.
   *
   * @param a The start quaternion.
   * @param b The end quaternion.
   * @param amount A value between 0 and 1 indicating the weight of the end
   *        quaternion.
   * @return The normalized linear interpolation between two quaternions.
   */
  static Quaternion nlerp(const Quaternion& a, const Quaternion& b,
                          const float amount) {
    return Quaternion::lerp(a, b, amount).normalize();
  }

  /**
   * @brief Returns the norm (magnitude) of the quaternion.
   *
   * @return The norm of the quaternion defined as ||q|| = sqrt(v^2 + s^2).
   */
  float norm() const {
    return sqrt(x()*x() + y()*y() + z()*z() + w()*w());
  }

  /**
   * @brief Returns the normalized quaternion.
   *
   * @return The normalized quaternion defined as q' = q / ||q||.
   */
  Quaternion normalize() const {
    return (*this) / norm();
  }

  /**
   * @brief Performs a rotation of the vector using this quaternion.
   *
   * @param v The vector to rotate.
   * @return The rotated three dimensional vector.
   */
  Vector3 rotateVector(const Vector3& v) const {
    return ((*this) * Quaternion(v, 0) * (*this).conjugate()).vector();
  }

  /**
   * @brief Performs a spherical linear interpolation between two quaternions.
   *
   * @param a The start quaternion.
   * @param b The end quaternion.
   * @param amount A value between 0 and 1 indicating the weight of the end
   *        vector.
   * @return The spherical linear interpolation between two quaternions.
   */
  static Quaternion slerp(const Quaternion& a, const Quaternion& b,
                          const float amount) {
    // TODO(JCube001): Implement.
    (void)a;
    (void)b;
    (void)amount;

    return Quaternion();
  }

 protected:
  float _data[4];
};

#endif  // UTILITY_QUATERNION_H_
