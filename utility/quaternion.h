#ifndef _QUATERNION_H
#define _QUATERNION_H

#include <math.h>

class Quaternion {
public:
  Quaternion(void);
  Quaternion(float w, float x, float y, float z);
  Quaternion(const Quaternion& other);
  ~Quaternion();
  
  bool operator==(const Quaternion& other) const;
  bool operator!=(const Quaternion& other) const;
  inline Quaternion& operator=(const Quaternion& other);
  Quaternion operator+(const Quaternion& other) const;
  Quaternion& operator+=(const Quaternion& other);
  Quaternion operator*(const Quaternion& other) const;
  Quaternion& operator*=(const Quaternion& other);
  
  void normalize(void);
  void makeInverse(void);
  void makeIdentity(void);
  
  float W;        // Real
  float X, Y, Z;  // Vectorial imaginary
};

#endif
