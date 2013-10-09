#include "quaternion.h"

Quaternion::Quaternion(void)
  : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
  : X(x), Y(y), Z(z), W(w)
{
}

Quaternion::Quaternion(float axis[3], float angle)
  : X(axis[0]), Y(axis[1]), Z(axis[2]), W(angle)
{
  //TODO euler angle convert?
}

Quaternion::Quaternion(const Quaternion& other)
  : X(other.X), Y(other.Y), Z(other.Z), W(other.W)
{
}

Quaternion::~Quaternion()
{
}

bool Quaternion::operator==(const Quaternion& other) const
{
  return ((X == other.X) &&
          (Y == other.Y) &&
          (Z == other.Z) &&
          (W == other.W));
}

bool Quaternion::operator!=(const Quaternion& other) const
{
  return !((*this) == other);
}

inline Quaternion& Quaternion::operator=(const Quaternion& other)
{
  X = other.X;
  Y = other.Y;
  Z = other.Z;
  W = other.W;
  
  return (*this);
}

Quaternion Quaternion::operator+(const Quaternion& other) const
{
  return Quaternion(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
}

Quaternion Quaternion::operator-(const Quaternion& other) const
{
  return Quaternion(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
}

Quaternion Quaternion::operator*(const float scalar) const
{
  return Quaternion(X * scalar, Y * scalar, Z * scalar, W * scalar);
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
  return Quaternion(
    (W * other.X) + (X * other.W) + (Y * other.Z) - (Z * other.Y),
    (W * other.Y) - (X * other.Z) + (Y * other.W) + (Z * other.X),
    (W * other.Z) + (X * other.Y) - (Y * other.X) + (Z * other.W),
    (W * other.W) - (X * other.X) - (Y * other.Y) - (Z * other.Z));
}

Quaternion Quaternion::operator/(const float scalar) const
{
  return Quaternion(X / scalar, Y / scalar, Z / scalar, W / scalar);
}

Quaternion Quaternion::operator/(Quaternion& other)
{
  return ((*this) * (other.inverse()));
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
  return (*this = (*this) + other);
}

Quaternion& Quaternion::operator-=(const Quaternion& other)
{
  return (*this = (*this) - other);
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
  return (*this = other * (*this));
}

Quaternion& Quaternion::operator/=(Quaternion& other)
{
  return ((*this) = (*this) * (other.inverse()));
}

Quaternion Quaternion::conjugate(void)
{
  return Quaternion(-X, -Y, -Z, W);
}

Quaternion Quaternion::createFromAxisAngle(float x, float y, float z, float angle)
{
  //TODO how do we really want to handle this?
  return Quaternion(x, y, z, angle);
}

Quaternion Quaternion::createFromAxisAngle(float axis[3], float angle)
{
  //TODO how do we really want to handle this?
  return Quaternion(axis, angle);
}

Quaternion Quaternion::createFromYawPitchRoll(float yaw, float pitch, float roll)
{
  //TODO
  (void)yaw;
  (void)pitch;
  (void)roll;
  
  return Quaternion();
}

float Quaternion::dot(const Quaternion& quaternion1, const Quaternion& quaternion2)
{
  return ((quaternion1.X * quaternion2.X) +
          (quaternion1.Y * quaternion2.Y) +
          (quaternion1.Z * quaternion2.Z) +
          (quaternion1.W * quaternion2.W));
}

Quaternion Quaternion::identity(void) const
{
  return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::inverse(void)
{
  return (this->conjugate() / this->normSquared());
}

Quaternion Quaternion::lerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount)
{
  //TODO
  (void)quaternion1;
  (void)quaternion2;
  (void)amount;
  
  return Quaternion();
}

Quaternion Quaternion::negate(void)
{
  return Quaternion(-X, -Y, -Z, -W);
}

float Quaternion::norm(void) const
{
  return sqrt(this->normSquared());
}

Quaternion Quaternion::normalize(void)
{
  float n = this->norm();
  
  return Quaternion(X / n, Y / n, Z / n, W / n);
}

float Quaternion::normSquared(void) const
{
  return ((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

Quaternion Quaternion::scale(const float factor)
{
  return Quaternion(X * factor, Y * factor, Z * factor, W * factor);
}

Quaternion Quaternion::slerp(Quaternion& quaternion1, Quaternion& quaternion2, float amount)
{
  //TODO
  (void)quaternion1;
  (void)quaternion2;
  (void)amount;
  
  return Quaternion();
}
