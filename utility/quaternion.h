#ifndef _QUATERNION_H
#define _QUATERNION_H

#include <math.h>
#include "vector.h"

/**
 * @brief Quaternion. A structure composed of three imaginary vectorial
 *        components and one real component. The vector represents the axis
 *        while the scalar represents the angle of rotation on that axis.
 *
 * @note There are two common ways to store the structure of a quaternion. They
 *       are {w, x, y, z} and {x, y, z, w} where w is the real component and
 *       {x, y, z} is the imaginary vector component. The layout {x, y, z, w}
 *       was choosen for this particular class because it makes it easier to
 *       work with the vectorial components as an array.
 * @note All angles are treated as radians.
 */
class Quaternion
{
public:
  /**
   * @brief Default constructor.
   */
  Quaternion()
    : _data{0.0f, 0.0f, 0.0f, 0.0f}
  {
  }
  
  /**
   * @brief Copy constructor.
   *
   * @param other The quaternion to copy from.
   */
  Quaternion(const Quaternion& other)
    : _data{other.x(), other.y(), other.z(), other.w()}
  {
  }
  
  /**
   * @brief Component initalization constructor.
   *
   * @param v The imaginary vectorial component.
   * @param s The scalar real component.
   */
  Quaternion(const Vector3& v, const float s)
    : _data{v.x(), v.y(), v.z(), s}
  {
  }
  
  /**
   * @brief Array initialization constructor.
   *
   * @param array The array to store as quaternion components. Should be in the
   *        order of {x, y, z, w}.
   */
  Quaternion(const float* array)
  {
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
    : _data{x, y, z, w}
  {
  }
  
  /**
   * @brief Destructor.
   */
  ~Quaternion()
  {
  }
  
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
  void vector(Vector3& v) {
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
    return Quaternion(vector(), scalar());
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
   * @return The cross product of the quaternions.
   */
  Quaternion operator*(const Quaternion& rhs) const {
    return Quaternion(); // TODO
  }
  
  /**
   * @brief Scalar multiplication.
   *
   * @param rhs The right hand side scalar value to multiply by.
   * @return The product of the quaternion times the scalar.
   */
  Quaternion operator*(const float rhs) const {
    return Quaternion(vector() * rhs, scalar() * rhs);
  }
  
  /**
   * @brief Division.
   *
   * @param rhs The right hand side quaternion to divide by.
   * @return The quotient of the quaternions.
   */
  Quaternion operator/(const Quaternion& rhs) const {
    return Quaternion(); // TODO double check that: (*this) * rhs.inverse();
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
  
  // TODO The rest of the comparative operator overloading.
  
  
  
  
#if 0
  // Reference only; this will go away soon.

  bool operator==(const Quaternion& other) const;
  bool operator!=(const Quaternion& other) const;
  inline Quaternion& operator=(const Quaternion& other);
  Quaternion operator+(const Quaternion& other) const;
  Quaternion operator-(const Quaternion& other) const;
  Quaternion operator*(const float scalar) const;
  Quaternion operator*(const Quaternion& other) const;
  Quaternion operator/(const float scalar) const;
  Quaternion operator/(Quaternion& other);
  Quaternion& operator+=(const Quaternion& other);
  Quaternion& operator-=(const Quaternion& other);
  Quaternion& operator*=(const Quaternion& other);
  Quaternion& operator/=(Quaternion& other);
  
  Quaternion conjugate(void);
  
  static Quaternion createFromAxisAngle(float x, float y, float z, float angle);
  static Quaternion createFromAxisAngle(float axis[3], float angle);
  
  static Quaternion createFromYawPitchRoll(float yaw, float pitch, float roll);
  
  static float dot(const Quaternion& quaternion1, const Quaternion& quaternion2);
  
  Quaternion identity(void) const;
  
  Quaternion inverse(void);
  
  static Quaternion lerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount);
  
  Quaternion negate(void);
  
  float norm(void) const;
  
  Quaternion normalize(void);
  
  float normSquared(void) const;
  
  Quaternion scale(const float factor);
  
  static Quaternion slerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount);
#endif
  
protected:
  float _data[4];
};

#endif
