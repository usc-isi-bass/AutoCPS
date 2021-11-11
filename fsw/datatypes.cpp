#include "datatypes.h"

#include "SpiceCK.h"
#include "SpiceZpr.h"

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
  SpiceDouble rotation_matrix[3][3], quart[4];

  // Transform Euler angle into rotation matrix, and rotation matrix into
  // quaternion
  eul2m_c(ret.z, ret.y, ret.z, 2, 1, 0, rotation_matrix);
  m2q_c(rotation_matrix, quart);

  ret.w = quart[0];
  ret.x = quart[1];
  ret.y = quart[2];
  ret.z = quart[3];

  return ret;
}
