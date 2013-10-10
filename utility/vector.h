#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>

class Vector3 {
public:
  /**
   * @brief Default constructor.
   */
  Vector3()
    : _data{0.0f, 0.0f, 0.0f}
  {
  }
  
  /**
   * @brief Copy constructor.
   * @param other The vector to copy from.
   */
  Vector3(const Vector3& other)
    : _data{other.x(), other.y(), other.z()}
  {
  }
  
  /**
   * @brief Initialization constructor.
   * @param x The x-value component.
   * @param y The y-value component.
   * @param z The z-value component.
   */
  Vector3(const float x, const float y, const float z)
    : _data{x, y, z}
  {
  }
  
  /**
   * @brief Array initialization constructor.
   * @param data The array to store as vector components.
   */
  Vector3(const float* data)
  {
    for (int i = 0; i < 3; i++) {
	  _data[i] = data[i];
	}
  }
  
  /**
   * @brief Destructor.
   */
  ~Vector3()
  {
  }
  
  /* Access functions */
  float x() const { return _data[0]; }
  float y() const { return _data[1]; }
  float z() const { return _data[2]; }
  
  /**
   * @brief Assignment.
   * @param rhs The right hand side vector to assign.
   * @return The resulting vector.
   */
  Vector3 operator=(const Vector3& rhs) const {
    return Vector3(rhs.x(), rhs.y(), rhs.z());
  }
  
  /**
   * @brief Unary negation.
   * @return The resulting vector.
   */
  Vector3 operator-() const {
    return Vector3(-x(), -y(), -z());
  }
  
  /**
   * @brief Addition.
   * @param rhs The right hand side vector to add.
   * @return The resulting vector.
   */
  Vector3 operator+(const Vector3& rhs) const {
    return Vector3(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
  }
  
  /**
   * @brief Subtraction.
   * @param rhs The right hand side vector to subtract by.
   * @return The resulting vector.
   */
  Vector3 operator-(const Vector3& rhs) const {
    return Vector3(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
  }
  
  /**
   * @brief Cross product multiplication.
   * @param rhs The right hand side vector to multiply by.
   * @return The resulting vector.
   */
  Vector3 operator*(const Vector3& rhs) const {
    return Vector3(y()*rhs.z() - z()*rhs.y(),
	               z()*rhs.x() - x()*rhs.z(),
				   x()*rhs.y() - y()*rhs.x());
  }
  
  /**
   * @brief Scalar multiplication.
   * @param s The scalar value to multiply by.
   * @return The resulting vector.
   */
  Vector3 operator*(const float s) const {
    return Vector3(s*x(), s*y(), s*z());
  }
  
  /**
   * @brief Dot product multiplication.
   * @param a The left hand side vector.
   * @param b The right hand side vector.
   * @return The scalar product of two vectors.
   */
  static float dot(Vector3& a, Vector3& b) const {
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
  }
  
  /**
   * @brief Returns the norm (magnitude) of the vector.
   * @return The scalar norm of the vector.
   */
  float norm() const {
    return sqrt(x()*x() + y()*y() + z()*z());
  }
  
protected:
  float _data[3];
};

#endif