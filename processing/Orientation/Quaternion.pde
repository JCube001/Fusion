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

class Quaternion {
  float[] data;
  
  Quaternion() {
    data = new float[] {1.0f, 0.0f, 0.0f, 0.0f};
  }
  
  Quaternion(float w, float x, float y, float z) {
    data = new float[] {w, x, y, z};
  }
  
  float w() {
    return data[0];
  }
  
  float x() {
    return data[1];
  }
  
  float y() {
    return data[2];
  }
  
  float z() {
    return data[3];
  }
  
  void set(float w, float x, float y, float z) {
    data = new float[] {w, x, y, z};
  }
  
  void conjugate() {
    this.set(this.w(), -this.x(), -this.y(), -this.z());
  }
  
  Quaternion conjugated() {
    return new Quaternion(this.w(), -this.x(), -this.y(), -this.z());
  }
  
  float norm() {
    return sqrt(
      this.w()*this.w() +
      this.x()*this.x() +
      this.y()*this.y() +
      this.z()*this.z());
  }
  
  void normalize() {
    float n = this.norm();
    this.set(
      this.w() / n,
      this.x() / n,
      this.y() / n,
      this.z() / n);
  }
  
  Quaternion normalized() {
    float n = this.norm();
    return new Quaternion(
      this.w() / n,
      this.x() / n,
      this.y() / n,
      this.z() / n);
  }
}

Quaternion convertFromAxisAngle(final float angle,
                                final float x,
                                final float y,
                                final float z) {
  final float half_angle = angle * 0.5f;
  final float sin_half_angle = sin(half_angle);
  
  return new Quaternion(
    cos(half_angle),
    x * sin_half_angle,
    y * sin_half_angle,
    z * sin_half_angle);
}

float[] convertToAxisAngle(final Quaternion q) {
  final float p_norm = sqrt(
    q.x() * q.x() +
    q.y() * q.y() +
    q.z() * q.z());
  final float theta = 2.0f * atan2(p_norm, q.w());
  
  float[] aa = new float[4];
  
  if (theta != 0.0f) {
    aa = new float[] {
      theta,
      q.x() / p_norm,
      q.y() / p_norm,
      q.z() / p_norm};
  } else {
    aa = new float[] {theta, 0.0f, 0.0f, 0.0f};
  }
  
  return aa;
}

Quaternion convertFromEulerAngles(final float[] e) {
  final float half_e_0 = e[0] * 0.5f;
  final float half_e_1 = e[1] * 0.5f;
  final float half_e_2 = e[2] * 0.5f;
  
  final float cr = cos(half_e_0);
  final float cp = cos(half_e_1);
  final float cy = cos(half_e_2);
  final float sr = sin(half_e_0);
  final float sp = sin(half_e_1);
  final float sy = sin(half_e_2);
  
  Quaternion q = new Quaternion(
    cr*cp*cy + sr*sp*sy,
    sr*cp*cy - cr*sp*sy,
    cr*sp*cy + sr*cp*sy,
    cr*cp*sy - sr*sp*cy);
  
  return q;
}

float[] convertToEulerAngles(final Quaternion q) {
  float[] e = new float[3];
  
  e[0] = atan2(2.0f*(q.w()*q.x() + q.y()*q.z()),
               1.0f - 2.0f*(q.x()*q.x() + q.y()*q.y()));
  e[1] = asin(2.0f*(q.w()*q.y() - q.z()*q.x()));
  e[2] = atan2(2.0f*(q.w()*q.z() + q.x()*q.y()),
               1.0f - 2.0f*(q.y()*q.y() + q.z()*q.z()));
  
  return e;
}

Quaternion identity() {
  return new Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}
