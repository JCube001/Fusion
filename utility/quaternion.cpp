#include "quaternion.h"

Quaternion::Quaternion(void)
  : W(0.0F), X(0.0F), Y(0.0F), Z(0.0F)
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
  : W(w), X(x), Y(y), Z(z)
{
}

Quaternion::Quaternion(const Quaternion& other)
  : W(other.W), X(other.X), Y(other.Y), Z(other.Z)
{
}

Quaternion::~Quaternion()
{
}

bool Quaternion::operator==(const Quaternion& other) const
{
  return ((W == other.W) &&
          (X == other.X) &&
          (Y == other.Y) &&
          (Z == other.Z));
}

bool Quaternion::operator!=(const Quaternion& other) const
{
  return !(*this == other);
}

inline Quaternion& Quaternion::operator=(const Quaternion& other)
{
  W = other.W;
  X = other.X;
  Y = other.Y;
  Z = other.Z;
  return *this;
}

Quaternion Quaternion::operator+(const Quaternion& other) const
{
  return Quaternion(W + other.W, X + other.X, Y + other.Y, Z + other.Z);
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
  return (*this = other + (*this));
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
  Quaternion ret;
  
  ret.W = (W * other.W) - (X * other.X) - (Y * other.Y) - (Z * other.Z);
  ret.X = (W * other.X) + (X * other.W) + (Y * other.Z) - (Z * other.Y);
  ret.Y = (W * other.Y) - (X * other.Z) + (Y * other.W) + (Z * other.X);
  ret.Z = (W * other.Z) + (X * other.Y) - (Y * other.X) + (Z * other.W);
  
  return ret;
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
  return (*this = other * (*this));
}

void Quaternion::normalize(void) {
  float magnitude = sqrt((W * W) + (X * X) + (Y * Y) + (Z * Z));
  
  W /= magnitude;
  X /= magnitude;
  Y /= magnitude;
  Z /= magnitude;
}

void Quaternion::makeInverse(void)
{
  X = -X;
  Y = -Y;
  Z = -Z;
}

void Quaternion::makeIdentity(void)
{
  W = 1.0F;
  X = 0.0F;
  Y = 0.0F;
  Z = 0.0F;
}
