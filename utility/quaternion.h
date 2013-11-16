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
#include "math_extra.h"
#include "vector.h"

namespace fusion {

// Prototypes
class Quaternion;
inline Quaternion operator+(Quaternion lhs, const Quaternion& rhs);
inline Quaternion operator-(Quaternion lhs, const Quaternion& rhs);
inline Quaternion operator-(const Quaternion& rhs);
inline Quaternion operator*(float lhs, Quaternion rhs);
inline Quaternion operator*(Quaternion lhs, float rhs);
inline Quaternion operator*(Quaternion lhs, const Quaternion& rhs);
inline Quaternion operator/(Quaternion lhs, float rhs);
inline Quaternion operator/(Quaternion lhs, const Quaternion& rhs);
inline bool operator==(const Quaternion& lhs, const Quaternion& rhs);
inline bool operator!=(const Quaternion& lhs, const Quaternion& rhs);
void swap(Quaternion& q0, Quaternion& q1);

/**
 * @brief Quaternion. A structure composed of three imaginary vectorial
 *        components and one real component. The vector represents the axis
 *        while the scalar represents the angle of rotation about that axis.
 *
 * @note There are two common ways to store the structure of a quaternion. They
 *       are [w, x, y, z] and [x, y, z, w] where w is the real component and
 *       [x, y, z] is the imaginary vector component. The layout [w, x, y, z]
 *       was chosen for this particular class because this is the format used
 *       most to describe quaternions mathematically.
 * @note All angles are treated as radians.
 */
class Quaternion {
 public:
  /**
   * @brief Default constructor.
   */
  Quaternion() {
    data_[0] = 1.0f;
    data_[1] = 0.0f;
    data_[2] = 0.0f;
    data_[3] = 0.0f;
  }

  /**
   * @brief Copy constructor.
   *
   * @param other The quaternion to copy from.
   */
  Quaternion(const Quaternion& other) {
    data_[0] = other.w();
    data_[1] = other.x();
    data_[2] = other.y();
    data_[3] = other.z();
  }

  /**
   * @brief Component initialization constructor.
   *
   * @param s The scalar real component.
   * @param p The imaginary vectorial component.
   */
  Quaternion(float s, const Vector3& p) {
    data_[0] = s;
    data_[1] = p.x();
    data_[2] = p.y();
    data_[3] = p.z();
  }

  /**
   * @brief Array initialization constructor.
   *
   * @param array The array to store as quaternion components. Should be in
   *        the order of [w, x, y, z].
   */
  explicit Quaternion(const float* array) {
    for (int i = 0; i < 4; i++) {
      data_[i] = array[i];
    }
  }

  /**
   * @brief Initialization constructor.
   *
   * @param w The real component.
   * @param x The x-value of the imaginary vector component.
   * @param y The y-value of the imaginary vector component.
   * @param z The z-value of the imaginary vector component.
   */
  Quaternion(float w, float x, float y, float z) {
    data_[0] = w;
    data_[1] = x;
    data_[2] = y;
    data_[3] = z;
  }

  /**
   * @brief Destructor.
   */
  ~Quaternion() {}

  /**
   * @brief Return the quaternion w-component.
   *
   * @return The quaternion w-component.
   */
  float w() const { return scalar(); }

  /**
   * @brief Return the quaternion x-component.
   *
   * @return The quaternion x-component.
   */
  float x() const { return data_[1]; }

  /**
   * @brief Return the quaternion y-component.
   *
   * @return The quaternion y-component.
   */
  float y() const { return data_[2]; }

  /**
   * @brief Return the quaternion z-component.
   *
   * @return The quaternion z-component.
   */
  float z() const { return data_[3]; }

  /**
   * @brief Return the quaternion scalar component.
   *
   * @return The quaternion scalar component.
   */
  float scalar() const { return data_[0]; }

  /**
   * @brief Return the quaternion vector component.
   *
   * @return The quaternion vector component.
   */
  Vector3 vector() const { return Vector3(data_ + 1); }

  /**
   * @brief Set the quaternion scalar component.
   */
  void setScalar(float s) { data_[0] = s; }

  /**
   * @brief Set the quaternion vector component.
   */
  void setVector(const Vector3& p) {
    for (int i = 1; i < 4; i++) {
      data_[i] = p[i - 1];
    }
  }

  /**
   * @brief Assignment.
   *
   * @param rhs The right hand side quaternion to assign.
   * @return The assigned quaternion.
   */
  Quaternion& operator=(Quaternion rhs) {
    swap(*this, rhs);
    return *this;
  }

  /**
   * @brief Subscript accessor.
   *
   * @param i The index of the quaternion component to access.
   * @return The value of the quaternion component stored at the index.
   */
  const float& operator[](int i) const {
    return data_[i];
  }

  /**
   * @brief Subscript mutator.
   *
   * @param i The index of the quaternion component to mutate.
   * @return The value of the quaternion component stored at the index.
   */
  float& operator[](int i) {
    return data_[i];
  }

  /**
   * @brief Compound addition.
   *
   * @param rhs The right hand side quaternion to add.
   * @return The sum of the quaternions.
   */
  Quaternion& operator+=(const Quaternion& rhs) {
    setScalar(scalar() + rhs.scalar());
    setVector(vector() + rhs.vector());
    return *this;
  }

  /**
   * @brief Compound subtraction.
   *
   * @param rhs The right hand side quaternion to subtract by.
   * @return The difference of the quaternions.
   */
  Quaternion& operator-=(const Quaternion& rhs) {
    setScalar(scalar() - rhs.scalar());
    setVector(vector() - rhs.vector());
    return *this;
  }

  /**
   * @brief Compound scalar multiplication.
   *
   * @param rhs The right hand side scalar value to multiply by.
   * @return The product of the quaternion times the scalar.
   */
  Quaternion& operator*=(const float rhs) {
    setScalar(scalar()*rhs);
    setVector(vector()*rhs);
    return *this;
  }

  /**
   * @brief Compound cross product multiplication.
   *
   * @param rhs The right hand side quaternion to multiply by.
   * @return The cross product of the quaternions defined as
   *         q0q1 = [s0s1 - v0.v1, s0v1 + s1v0 + v0v1].
   */
  Quaternion& operator*=(const Quaternion& rhs) {
    Quaternion lhs = *this;
    setScalar(lhs.scalar()*rhs.scalar() -
              Vector3::dot(lhs.vector(), rhs.vector()));
    setVector(lhs.scalar()*rhs.vector() + rhs.scalar()*lhs.vector() +
              lhs.vector()*rhs.vector());
    return *this;
  }

  /**
   * @brief Compound scalar division.
   *
   * @param rhs The right hand side scalar value to divide by.
   * @return The quotient of the quaternion divided by the scalar.
   */
  Quaternion& operator/=(const float rhs) {
    setScalar(scalar() / rhs);
    setVector(vector() / rhs);
    return *this;
  }

  /**
   * @brief Compound division.
   *
   * @param rhs The right hand side quaternion to divide by.
   * @return The quotient of the quaternions defined as q0 / q1 = q0q1^-1.
   */
  Quaternion& operator/=(const Quaternion& rhs) {
    *this *= rhs.inverse();
    return *this;
  }

  // Related non-member functions.
  friend inline Quaternion operator+(Quaternion lhs, const Quaternion& rhs);
  friend inline Quaternion operator-(Quaternion lhs, const Quaternion& rhs);
  friend inline Quaternion operator-(const Quaternion& rhs);
  friend inline Quaternion operator*(float lhs, Quaternion rhs);
  friend inline Quaternion operator*(Quaternion lhs, float rhs);
  friend inline Quaternion operator*(Quaternion lhs, const Quaternion& rhs);
  friend inline Quaternion operator/(Quaternion lhs, float rhs);
  friend inline Quaternion operator/(Quaternion lhs, const Quaternion& rhs);
  friend inline bool operator==(const Quaternion& lhs, const Quaternion& rhs);
  friend inline bool operator!=(const Quaternion& lhs, const Quaternion& rhs);
  friend void swap(Quaternion& q0, Quaternion& q1);

  /**
   * @brief Conjugate the quaternion.
   */
  void conjugate() {
    setVector(-vector());
  }

  /**
   * @brief Returns the quaternion conjugate.
   *
   * @return The conjugate of the quaternion defined as q* = [s, -v].
   */
  Quaternion conjugated() const {
    return Quaternion(scalar(), -vector());
  }

  /**
   * @brief Returns a unit quaternion converted from an axis-angle.
   *
   * @param angle The angle the axis is rotated at in radians.
   * @param axis The vector representation of the axis.
   * @return The unit quaternion representation of the axis-angle.
   *
   * @note All angles are in radians.
   */
  static Quaternion convertFromAxisAngle(const float angle,
                                         const Vector3& axis) {
    const float half_angle = angle*0.5f;
    return Quaternion(cos(half_angle), axis*sin(half_angle));
  }

  /**
   * @brief Returns a unit quaternion converted from Euler angles.
   *
   * @param roll The angle representing roll in radians.
   * @param pitch The angle representing pitch in radians.
   * @param yaw The angle representing yaw in radians.
   * @return The unit quaternion representation of the Euler rotations.
   *
   * @note Specifically these are Tait-Bryan angles.
   * @note All angles are in radians.
   */
  static Quaternion convertFromEulerAngles(const float roll, const float pitch,
                                           const float yaw) {
    const float half_roll = roll*0.5f;
    const float half_pitch = pitch*0.5f;
    const float half_yaw = yaw*0.5f;
    const float sr = sin(half_roll);
    const float sp = sin(half_pitch);
    const float sy = sin(half_yaw);
    const float cr = cos(half_roll);
    const float cp = cos(half_pitch);
    const float cy = cos(half_yaw);

    return Quaternion(cr*cp*cy + sr*sp*sy, sr*cp*cy - cr*sp*sy,
                      cr*sp*cy + sr*cp*sy, cr*cp*sy - sr*sp*cy);
  }

  /**
   * @brief Returns an axis-angle representation of a unit quaternion.
   *
   * @param q The unit quaternion to convert from.
   * @return The pointer to the axis-angle represented by the unit quaternion
   *         as an array of size four. The values in the array are ordered
   *         [angle, x, y, z].
   *
   * @note All angles are in radians.
   */
  static float* convertToAxisAngle(const Quaternion& q) {
    const float pn = q.vector().norm();
    const float theta = 2.0f*atan2(pn, q.w());
    static float a[4];

    // Store the angle.
    a[0] = theta;

    // If the angle is zero, then that means the vector component must have a
    // norm of zero. The result will therefore be a zero quaternion.
    if (theta != 0.0f) {
      a[1] = q.x() / pn;
      a[2] = q.y() / pn;
      a[3] = q.z() / pn;
    } else {
      a[1] = 0.0f;
      a[2] = 0.0f;
      a[3] = 0.0f;
    }

    return a;
  }

  /**
   * @brief Returns an array containing Euler angles converted from a
   *        unit quaternion.
   *
   * @param q The unit quaternion to convert from.
   * @return The pointer to the Euler angles represented by the unit quaternion
   *         as an array of size three. The values in the array are ordered
   *         [roll, pitch, yaw].
   *
   * @note Specifically these are Tait-Bryan angles.
   * @note All angles are in radians.
   * @note This function is inefficient and should not be used on an embedded
   *       device. Euler angles should actually be avoided entirely.
   *       The only time this conversion from quaternion to Euler angles should
   *       take place is when displaying a rotation as human readable angle
   *       values.
   */
  static float* convertToEulerAngles(const Quaternion& q) {
    static float e[3];

    e[0] = atan2(2.0f*(q.w()*q.x() + q.y()*q.z()),
                 1.0f - 2.0f*(q.x()*q.x() + q.y()*q.y()));
    e[1] = asin(2.0f*(q.w()*q.y() - q.z()*q.x()));
    e[2] = atan2(2.0f*(q.w()*q.z() + q.x()*q.y()),
                 1.0f - 2.0f*(q.y()*q.y() + q.z()*q.z()));

    return e;
  }

  /**
   * @brief Dot product multiplication.
   *
   * @param q0 The left hand side quaternion.
   * @param q1 The right hand side quaternion.
   * @return The scalar product of two quaternions.
   */
  static float dot(const Quaternion& q0, const Quaternion& q1) {
    return q0.scalar()*q1.scalar() + Vector3::dot(q0.vector(), q1.vector());
  }

  /**
   * @brief Normalizes the quaternion.
   *
   * @note Makes use of the inverse square root to be able to avoid division
   *       operations entirely.
   */
  void fastNormalize() {
    *this *= invSqrt(w()*w() + x()*x() + y()*y() + z()*z());
  }

  /**
   * @brief Returns the normalized (unit) quaternion.
   *
   * @return The normalized quaternion.
   *
   * @note Makes use of the inverse square root to be able to avoid division
   *       operations entirely.
   */
  Quaternion fastNormalized() const {
    return *this * invSqrt(w()*w() + x()*x() + y()*y() + z()*z());
  }

  /**
   * @brief Returns the quaternion identity.
   *
   * @return The identity of the quaternion defined as q = [1, 0, 0, 0].
   * @note The identity represents no rotation.
   */
  static Quaternion identity() {
    return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
  }

  /**
   * @brief Returns the quaternion inverse.
   *
   * @return The inverse of the quaternion defined as q^-1 = q* / ||q||^2.
   *
   * @note Multiple definitions were encountered during research. After much
   *       testing, this one seems to be the most correct.
   */
  Quaternion inverse() const {
    const float n = norm();

    // Gracefully handle a zero quaternion by returning the identity.
    // Only return the conjugate in the case where the magnitude is one.
    if (n == 0.0f) {
      return Quaternion::identity();
    } else if (n == 1.0f) {
      return conjugated();
    }

    return conjugated() / (n*n);
  }

  /**
   * @brief Inverts the quaternion.
   */
  void invert() {
    const float n = norm();

    if (n == 0.0f) {
      *this = Quaternion::identity();
    } else if (n == 1.0f) {
      *this = conjugated();
    }

    *this = conjugated() / (n*n);
  }

  /**
   * @brief Performs a linear interpolation between two quaternions.
   *
   * @param q0 The start quaternion.
   * @param q1 The end quaternion.
   * @param t A value between 0 and 1 inclusive indicating the weight of the end
   *          quaternion.
   * @return The linear interpolation between two quaternions.
   */
  static Quaternion lerp(const Quaternion& q0, const Quaternion& q1,
                         const float t) {
    return q0*(1.0f - t) + q1*t;
  }

  /**
   * @brief Performs a normalized linear interpolation between two
   *        quaternions.
   *
   * @param q0 The start quaternion.
   * @param q1 The end quaternion.
   * @param t A value between 0 and 1 inclusive indicating the weight of the end
   *          quaternion.
   * @return The normalized linear interpolation between two quaternions.
   */
  static Quaternion nlerp(const Quaternion& q0, const Quaternion& q1,
                          const float t) {
    return Quaternion::lerp(q0, q1, t).normalized();
  }

  /**
   * @brief Returns the norm (magnitude) of the quaternion.
   *
   * @return The norm of the quaternion defined as ||q|| = sqrt(s^2 + v^2).
   */
  float norm() const {
    return sqrt(w()*w() + x()*x() + y()*y() + z()*z());
  }

  /**
   * @brief Normalizes the quaternion.
   */
  void normalize() {
    *this /= norm();
  }

  /**
   * @brief Returns the normalized (unit) quaternion.
   *
   * @return The normalized quaternion defined as q' = q / ||q||.
   */
  Quaternion normalized() const {
    return (*this) / norm();
  }

  /**
   * @brief Performs a rotation of the vector using the quaternion.
   *
   * @param p The vector to rotate.
   * @return The rotated three dimensional vector defined as p' = qpq^-1.
   */
  Vector3 rotateVector(const Vector3& p) const {
    return (*this * Quaternion(0.0f, p) * inverse()).vector();
  }

  /**
   * @brief Performs a spherical linear interpolation between two quaternions.
   *
   * @param q0 The start quaternion.
   * @param q1 The end quaternion.
   * @param t A value between 0 and 1 inclusive indicating the weight of the end
   *          quaternion.
   * @return The spherical linear interpolation between two quaternions defined
   *         as Slerp(q0, q1; t) = ((sin(1-t)*o) / sin(o))(q0 cap) +
   *         (sin(to) / sin(o))(q1 cap) where o = acos(cos(o)) =
   *         acos((q0 cap).(q1 cap)).
   */
  static Quaternion slerp(const Quaternion& q0, const Quaternion& q1,
                          const float t) {
    // Quaternions must be normalized to work with angle calculations.
    // Quaternion qq1 is kept mutable because it may need to be negated later.
    const Quaternion qq0 = q0.normalized();
    Quaternion qq1 = q1.normalized();

    // Calculate omega (the angle between q0 and q1)
    const float co = Quaternion::dot(qq0, qq1);
    const float o = acos(co);

    // Check if the dot product (cosine omega) resulted in a negative value.
    // If it did, then negate one end quaternion to prevent taking the long way
    // around during the interpolation.
    if (co < 0.0f) {
      qq1 = -qq1;
    }

    // A number approaching zero.
    const float lim = 1.0e-5f;

    // Check if omega is approaching zero before performing the Slerp.
    if (!(-lim <= o && o <= lim)) {
      const float so = sin(o);
      return qq0*(sin((1.0f - t)*o) / so) + qq1*(sin(t*o) / so);
    }

    // The angle is too small, use Lerp.
    return Quaternion::lerp(qq0, qq1, t);
  }

  /**
   * @brief Performs a spherical and quadrangle interpolation between four
   *        quaternions.
   *
   * @param q0 The start quaternion.
   * @param q1 The first control quaternion.
   * @param q2 The second control quaternion.
   * @param q3 The end quaternion.
   * @param t A value between 0 and 1 inclusive indicating the weight of the end
   *          quaternion.
   * @return The spherical and quadrangle interpolation between four quaternions
   *         defined as Squad(q0, q1, q2, q3; t) = Slerp(Slerp(q0, q1; t),
   *         Slerp(q2, q3; t), 2t(1 - t)).
   */
  static Quaternion squad(const Quaternion& q0, const Quaternion& q1,
                          const Quaternion& q2, const Quaternion& q3,
                          const float t) {
    return Quaternion::slerp(Quaternion::slerp(q0, q1, t),
                             Quaternion::slerp(q2, q3, t), 2.0f*t*(1.0f - t));
  }

 protected:
  float data_[4];
};

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

#endif  // UTILITY_QUATERNION_H_
