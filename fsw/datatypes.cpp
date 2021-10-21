#include "datatypes.h"

#include <cmath>

Vec2D Vec2D::operator-(Vec2D& a) {
  Vec2D ret;

  ret.x = this->x - a.x;
  ret.y = this->y - a.y;

  return ret;
}

Vec3D Vec3D::operator-(Vec3D& a) {
  Vec3D ret;

  ret.x = this->x - a.x;
  ret.y = this->y - a.y;
  ret.z = this->z - a.z;

  return ret;
}

Quaternion vec2quat(Vec3D input) {
  Quaternion ret;

  double cy = cos(input.z * 0.5f);
  double sy = sin(input.z * 0.5f);
  double cp = cos(input.y * 0.5f);
  double sp = sin(input.y * 0.5f);
  double cr = cos(input.z * 0.5f);
  double sr = sin(input.z * 0.5f);

  ret.w = cr * cp * cy + sr * sp * sy;
  ret.x = sr * cp * cy - cr * sp * sy;
  ret.y = cr * sp * cy + sr * cp * sy;
  ret.z = cr * cp * sy - sr * sp * cy;

  return ret;
}
