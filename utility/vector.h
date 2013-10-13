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

/**
 * @brief Vector, three dimensional.
 */
class Vector3 {
 public:
  /**
   * @brief Default constructor.
   */
  Vector3()
    : _data {0.0f, 0.0f, 0.0f} {}

  /**
   * @brief Copy constructor.
   *
   * @param other The vector to copy from.
   */
  Vector3(const Vector3& other)
    : _data {other.x(), other.y(), other.z()} {}

  /**
   * @brief Array initialization constructor.
   *
   * @param array The array to store as vector components.
   */
  explicit Vector3(const float* array) {
    for (int i = 0; i < 3; i++) {
      _data[i] = array[i];
    }
  }

  /**
   * @brief Initialization constructor.
   *
   * @param x The x-value component.
   * @param y The y-value component.
   * @param z The z-value component.
   */
  Vector3(const float x, const float y, const float z)
    : _data {x, y, z} {}

  /**
   * @brief Destructor.
   */
  ~Vector3() {}

  /**
   * @brief Return the vector x-component.
   *
   * @return The vector x-component.
   */
  float x() const { return _data[0]; }

  /**
   * @brief Return the vector y-component.
   *
   * @return The vector y-component.
   */
  float y() const { return _data[1]; }

  /**
   * @brief Return the vector z-component.
   *
   * @return The vector z-component.
   */
  float z() const { return _data[2]; }

  /**
   * @brief Subscript.
   *
   * @param i The index of the vector component to access.
   * @return The value of the vector component stored at the index.
   */
  inline float operator[](const int i) const {
    return _data[i];
  }

  /**
   * @brief Assignment.
   *
   * @param rhs The right hand side vector to assign.
   * @return The assigned vector.
   */
  inline Vector3 operator=(const Vector3& rhs) const {
    return Vector3(rhs.x(), rhs.y(), rhs.z());
  }

  /**
   * @brief Unary negation.
   *
   * @return The negated vector.
   */
  inline Vector3 operator-() const {
    return Vector3(-x(), -y(), -z());
  }

  /**
   * @brief Addition.
   *
   * @param rhs The right hand side vector to add.
   * @return The sum of the vectors.
   */
  Vector3 operator+(const Vector3& rhs) const {
    return Vector3(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
  }

  /**
   * @brief Subtraction.
   *
   * @param rhs The right hand side vector to subtract by.
   * @return The difference of the vectors.
   */
  Vector3 operator-(const Vector3& rhs) const {
    return Vector3(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
  }

  /**
   * @brief Cross product multiplication.
   *
   * @param rhs The right hand side vector to multiply by.
   * @return The cross product of the vectors.
   */
  Vector3 operator*(const Vector3& rhs) const {
    return Vector3(y()*rhs.z() - z()*rhs.y(),
                   z()*rhs.x() - x()*rhs.z(),
                   x()*rhs.y() - y()*rhs.x());
  }

  /**
   * @brief Scalar multiplication.
   *
   * @param rhs The right hand side scalar value to multiply by.
   * @return The product of the vector times the scalar.
   */
  Vector3 operator*(const float rhs) const {
    return Vector3(x()*rhs, y()*rhs, z()*rhs);
  }

  /**
   * @brief Scalar division.
   *
   * @param rhs The right hand side scalar value to divide by.
   * @return The quotient of the vector divided by the scalar.
   */
  Vector3 operator/(const float rhs) const {
    return Vector3(x() / rhs, y() / rhs, z() / rhs);
  }

  /**
   * @brief Equal to.
   *
   * @param rhs The right hand side vector.
   * @return True if both vectors are equal, otherwise false.
   */
  inline bool operator==(const Vector3& rhs) const {
    return ((x() == rhs.x()) &&
            (y() == rhs.y()) &&
            (z() == rhs.z()));
  }

  /**
   * @brief Not equal to.
   *
   * @param rhs The right hand side vector.
   * @return True if both vectors are not equal, otherwise false.
   */
  inline bool operator!=(const Vector3& rhs) const {
    return !((*this) == rhs);
  }

  /**
   * @brief Less than.
   *
   * @param rhs The right hand side vector.
   * @return True if the left hand side norm is less than the right hand side
   *         norm, otherwise false.
   */
  inline bool operator<(const Vector3& rhs) const {
    return (norm() < rhs.norm());
  }

  /**
   * @brief Greater than.
   *
   * @param rhs The right hand side vector.
   * @return True if the left hand side norm is greater than the right hand side
   *         norm, otherwise false.
   */
  inline bool operator>(const Vector3& rhs) const {
    return (rhs < (*this));
  }

  /**
   * @brief Less than or equal to.
   *
   * @param rhs The right hand side vector.
   * @return True if the left hand side norm is less than or equal to the right
   *         hand side norm, otherwise false. 
   */
  inline bool operator<=(const Vector3& rhs) const {
    return !((*this) > rhs);
  }

  /**
   * @brief Greater than or equal to.
   *
   * @param rhs The right hand side vector.
   * @return True if the left hand side norm is greater than or equal to the
   *         right hand side norm, otherwise false. 
   */
  inline bool operator>=(const Vector3& rhs) const {
    return !((*this) < rhs);
  }

  /**
   * @brief Dot product multiplication.
   *
   * @param a The left hand side vector.
   * @param b The right hand side vector.
   * @return The scalar product of two vectors.
   */
  static float dot(const Vector3& a, const Vector3& b) {
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
  }

  /**
   * @brief Performs a linear interpolation between two vectors.
   *
   * @param a The start vector.
   * @param b The end vector.
   * @param amount A value between 0 and 1 indicating the weight of the end
   *        vector.
   * @return The linear interpolation between two vectors.
   */
  static Vector3 lerp(const Vector3& a, const Vector3& b, const float amount) {
    return a + (b - a)*amount;
  }

  /**
   * @brief Scalar triple product multiplication.
   *
   * @param a The vector to obtain the dot product from.
   * @param b The vector to cross multiply with c.
   * @param c The vector to cross multiply with b.
   * @return The scalar product of the three vectors.
   */
  static float tripleProduct(const Vector3& a, const Vector3& b,
                             const Vector3& c) {
    return Vector3::dot(a, b*c);
  }

  /**
   * @brief Performs a normalized linear interpolation between two vectors.
   *
   * @param a The start vector.
   * @param b The end vector.
   * @param amount A value between 0 and 1 indicating the weight of the end
   *        vector.
   * @return The normalized linear interpolation between two vectors.
   */
  static Vector3 nlerp(const Vector3& a, const Vector3& b, const float amount) {
    return Vector3::lerp(a, b, amount).normalize();
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
   * @brief Returns a normalized (unit) vector.
   *
   * @return The normalized vector.
   */
  Vector3 normalize() const {
    return (*this) / norm();
  }

  /**
   * @brief Performs a spherical linear interpolation between two vectors.
   *
   * @param a The start vector.
   * @param b The end vector.
   * @param amount A value between 0 and 1 indicating the weight of the end
   *        vector.
   * @return The spherical linear interpolation between two vectors.
   */
  static Vector3 slerp(const Vector3& a, const Vector3& b, const float amount) {
    // The dot product is also the cosine of the angle between two vectors.
    float c = Vector3::dot(a, b);

    // Clamp it to be in the range of arc cosine.
    c = fmax(-1.0f, fmin(1.0f, c));

    // Return the angle between the start and end.
    // Then multiply that by the amount to get the angle between start and the
    // final result.
    float theta = acos(c)*amount;
    Vector3 relative = b - a*c;
    relative = relative.normalize();

    // The result.
    return (a*cos(theta)) + (relative*sin(theta));
  }

 protected:
  float _data[3];
};

#endif  // UTILITY_VECTOR_H_
