#include "datatypes.h"

#include "autocode.h"
#include "params.h"

#include <cmath>

using namespace std;

Vec3D Vec3D::operator+(Vec3D a) {
  Vec3D ret;

  ret.x = this->x + a.x;
  ret.y = this->y + a.y;
  ret.z = this->z + a.z;

  return ret;
}

Vec3D Vec3D::operator-(Vec3D& a) {
  Vec3D ret;

  ret.x = this->x - a.x;
  ret.y = this->y - a.y;
  ret.z = this->z - a.z;

  return ret;
}

// Dot multiplication
double Vec3D::operator*(Vec3D& a) {
  return this->x * a.x + this->y * a.y + this->z * a.z;
}

Vec3D Vec3D::operator/(double a) {
  Vec3D ret;

  ret.x = this->x / a;
  ret.y = this->y / a;
  ret.z = this->z / a;

  return ret;
}

// Scalar multiplication
Vec3D Vec3D::operator*(double a) {
  Vec3D ret;

  ret.x = this->x * a;
  ret.y = this->y * a;
  ret.z = this->z * a;

  return ret;
}

Quaternion Quaternion::operator*(Quaternion a) {
  Quaternion ret, b;

#ifdef JPL_QUATERNION
  a = a.conj();
  b = b.conj();
#else
  b = this;
#endif

  ret.w = b.w * a.w - b.x * a.x - b.y * a.y - b.z * a.z;
  ret.x = b.w * a.w + b.x * a.x + b.y * a.y - b.z * a.z;
  ret.y = b.w * a.w - b.x * a.x + b.y * a.y + b.z * a.z;
  ret.z = b.w * a.w + b.x * a.x - b.y * a.y + b.z * a.z;

  return ret;
}

Quaternion Quaternion::conj() {
  Quaternion ret;

  ret.w = this->w;
  ret.x = this->x * -1;
  ret.y = this->y * -1;
  ret.z = this->z * -1;

  return ret;
}

// Default reference frame has standard unit vectors
ReferenceFrame::ReferenceFrame() {
  this->i.x = 1;
  this->i.y = 0;
  this->i.z = 0;

  this->j.x = 0;
  this->j.y = 1;
  this->j.z = 0;

  this->k.x = 0;
  this->k.y = 0;
  this->k.z = 1;
}

// Transpose a 6x6 matrix
StateMatrix StateMatrix::transpose() {
  StateMatrix ret;

  for (int i = 0; i < 6; i++)
    for (int it = 0; it < 6; it++)
      ret.v[i][it] = this->v[it][i];

  return ret;
}

// Matrix addition
StateMatrix StateMatrix::operator+(StateMatrix rhs) {
  StateMatrix ret;

  for (int i = 0; i < 6; i++)
    for (int it = 0; it < 6; it++)
      ret.v[i][it] = this->v[i][it] + rhs.v[i][it];

  return ret;
}

// Matrix subtraction
StateMatrix StateMatrix::operator-(StateMatrix rhs) {
  StateMatrix ret;

  for (int i = 0; i < 6; i++)
    for (int it = 0; it < 6; it++)
      ret.v[i][it] = this->v[i][it] - rhs.v[i][it];

  return ret;
}

// Matrix dot multiplication
StateMatrix StateMatrix::operator*(StateMatrix rhs) {
  StateMatrix ret;

  for (int i = 0; i < 6; i++)
    for (int it = 0; it < 6; it++) {
      ret.v[i][it] = 0;
      for (int iter = 0; iter < 6; iter++)
        ret.v[i][it] += this->v[i][iter] * rhs.v[iter][it];
    }

  return ret;
}

// Matrix scalar multiplication
StateMatrix StateMatrix::operator*(double rhs) {
  StateMatrix ret;

  for (int i = 0; i < 6; i++)
    for (int it = 0; it < 6; it++)
      ret.v[i][it] = this->v[it][i] * rhs;

  return ret;
}

Quaternion vec2quat(Vec3D input) {
  Quaternion ret;
  double cy, sy, cp, sp, cr, sr;

  cy = cos(input.z * 0.5);
  sy = sin(input.z * 0.5);
  cp = cos(input.y * 0.5);
  sp = sin(input.y * 0.5);
  cr = cos(input.x * 0.5);
  sr = sin(input.x * 0.5);

  ret.w = cr * cp * cy + sr * sp * sy;
  ret.x = sr * cp * cy - cr * sp * sy;
  ret.y = cr * sp * cy + sr * cp * sy;
  ret.z = cr * cp * sy - sr * sp * cy;

#ifndef JPL_QUATERNION
  ret = ret.conj();
#endif

  return ret;
}

Vec3D quat2vec(Quaternion input) {
  Vec3D ret;
  double sinr_cosp, cosr_cosp, sinp, siny_cosp, cosy_cosp;

#ifndef JPL_QUATERNION
  input = input.conj();
#endif

  sinr_cosp = 2 * (input.w * input.x + input.y * input.z);
  cosr_cosp = 1 - 2 * (input.x * input.x + input.y * input.y);
  ret.x = atan2(sinr_cosp, cosr_cosp);

  sinp = 2 * (input.w * input.y - input.z * input.x);
  if (abs(sinp) >= 1)
    ret.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
  else
    ret.y = asin(sinp);

  siny_cosp = 2 * (input.w * input.z + input.x * input.y);
  cosy_cosp = 1 - 2 * (input.y * input.y + input.z * input.z);
  ret.z = atan2(siny_cosp, cosy_cosp);

  return ret;
}

Vec3D normalize(Vec3D input) {
  Vec3D ret;
  double mag;

  // Calculate magnitude of vector
  mag = sqrt(pow(input.x, 2) + pow(input.y, 2) + pow(input.z, 2));

  // Divide all by magnitude
  ret.x = input.x / mag;
  ret.y = input.y / mag;
  ret.z = input.z / mag;

  return ret;
}

Quaternion normalize(Quaternion input) {
  Quaternion ret;
  double mag;

  // Calculate magnitude of vector
  mag = sqrt(pow(input.w, 2) + pow(input.x, 2) + pow(input.y, 2) +
             pow(input.z, 2));

  // Divide all by magnitude
  ret.w = input.w / mag;
  ret.x = input.x / mag;
  ret.y = input.y / mag;
  ret.z = input.z / mag;

  return ret;
}
