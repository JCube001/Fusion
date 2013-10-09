/**
 * TODO doxygen comments before I forget everything I just wrote
 */

#ifndef _QUATERNION_H
#define _QUATERNION_H

#include <math.h>

class Quaternion {
public:
  float W;  // The rotation component
  float X;  // The x-value of the vector component
  float Y;  // The y-value of the vector component
  float Z;  // The z-value of the vector component
  
  Quaternion(void);
  Quaternion(float x, float y, float z, float w);
  Quaternion(float axis[3], float angle);
  Quaternion(const Quaternion& other);
  ~Quaternion();
  
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
};

#endif
