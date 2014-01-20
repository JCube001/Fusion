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

#include "quaternion.h"

namespace fusion {

Quaternion Quaternion::convertFromAxisAngle(const float angle,
                                            const Vector3& axis) {
  const float half_angle = angle*0.5f;
  return Quaternion(cos(half_angle), axis*sin(half_angle));
}

Quaternion Quaternion::convertFromEulerAngles(const float roll,
                                              const float pitch,
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

float* Quaternion::convertToAxisAngle(const Quaternion& q) {
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

float* Quaternion::convertToEulerAngles(const Quaternion& q) {
  static float e[3];

  e[0] = atan2(2.0f*(q.w()*q.x() + q.y()*q.z()),
               1.0f - 2.0f*(q.x()*q.x() + q.y()*q.y()));
  e[1] = asin(2.0f*(q.w()*q.y() - q.z()*q.x()));
  e[2] = atan2(2.0f*(q.w()*q.z() + q.x()*q.y()),
               1.0f - 2.0f*(q.y()*q.y() + q.z()*q.z()));

  return e;
}

Quaternion Quaternion::lerp(const Quaternion& q0, const Quaternion& q1,
                            const float t) {
  return q0*(1.0f - t) + q1*t;
}

Quaternion Quaternion::nlerp(const Quaternion& q0, const Quaternion& q1,
                             const float t) {
  return Quaternion::lerp(q0, q1, t).normalized();
}

Quaternion Quaternion::slerp(const Quaternion& q0, const Quaternion& q1,
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

Quaternion Quaternion::squad(const Quaternion& q0, const Quaternion& q1,
                             const Quaternion& q2, const Quaternion& q3,
                             const float t) {
  return Quaternion::slerp(Quaternion::slerp(q0, q1, t),
                           Quaternion::slerp(q2, q3, t), 2.0f*t*(1.0f - t));
}

/**
 * @brief Swap the states between two quaternions.
 *
 * @param q0 The first quaternion.
 * @param q1 The quaternion to swap with.
 */
void swap(Quaternion& q0, Quaternion& q1) {
#ifdef ARDUINO
  Quaternion temp;

  // Set temp equal to the state of q0.
  temp.data_[0] = q0.data_[0];
  temp.data_[1] = q0.data_[1];
  temp.data_[2] = q0.data_[2];
  temp.data_[3] = q0.data_[3];

  // Set q0 equal to the state of q1.
  q0.data_[0] = q1.data_[0];
  q0.data_[1] = q1.data_[1];
  q0.data_[2] = q1.data_[2];
  q0.data_[3] = q1.data_[3];

  // Set q1 equal to the state of temp.
  q1.data_[0] = temp.data_[0];
  q1.data_[1] = temp.data_[1];
  q1.data_[2] = temp.data_[2];
  q1.data_[3] = temp.data_[3];

#else

  using std::swap;

  swap(q0.data_[0], q1.data_[0]);
  swap(q0.data_[1], q1.data_[1]);
  swap(q0.data_[2], q1.data_[2]);
  swap(q0.data_[3], q1.data_[3]);
#endif
}

}  // namespace fusion
