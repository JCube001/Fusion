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

#include "vector.h"

namespace fusion {

Vector3 Vector3::lerp(const Vector3& p0, const Vector3& p1, const float t) {
  return p0*(1.0f - t) + p1*t;
}

Vector3 Vector3::nlerp(const Vector3& p0, const Vector3& p1, const float t) {
  return Vector3::lerp(p0, p1, t).normalized();
}

Vector3 Vector3::slerp(const Vector3& p0, const Vector3& p1, const float t) {
  // Vectors must be normalized to work with angle calculations.
  Vector3 pp0 = p0.normalized();
  Vector3 pp1 = p1.normalized();

  // Calculate omega (the angle between p0 and p1).
  const float o = acos(Vector3::dot(pp0, pp1));

  // A number approaching zero.
  const float lim = 1.0e-5f;

  // Check if omega is approaching zero before performing the Slerp.
  if (!(-lim <= o && o <= lim)) {
    const float so = sin(o);
    return (sin((1.0f - t)*o) / so)*pp0 + (sin(t*o) / so)*pp1;
  }

  // The angle is too small, use Lerp.
  return Vector3::lerp(pp0, pp1, t);
}

/**
 * @brief Swap the states between two vectors.
 *
 * @param p0 The first vector.
 * @param p1 The vector to swap with.
 */
void swap(Vector3& p0, Vector3& p1) {
  Vector3 temp;

  // Set temp equal to the state of p0.
  temp.data_[0] = p0.data_[0];
  temp.data_[1] = p0.data_[1];
  temp.data_[2] = p0.data_[2];

  // Set p0 equal to the state of p1.
  p0.data_[0] = p1.data_[0];
  p0.data_[1] = p1.data_[1];
  p0.data_[2] = p1.data_[2];

  // Set p1 equal to the state of temp.
  p1.data_[0] = temp.data_[0];
  p1.data_[1] = temp.data_[1];
  p1.data_[2] = temp.data_[2];
}

}  // namespace fusion
