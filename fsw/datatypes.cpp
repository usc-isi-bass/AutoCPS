#include "datatypes.h"

#include <cmath>

Vec2D Vec2D::operator-(Vec2D& a) {
  Vec2D ret;

  ret.x = this->x - a.x;
  ret.y = this->y - a.y;

  return ret;
}

Vec3D Vec3D::operator+(Vec3D& a) {
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

Quaternion vec2quat(Vec3D input) {
  Quaternion ret;
  double c1, c2, c3, s1, s2, s3;

  c1 = cos(input.x / 2);
  c2 = cos(input.y / 2);
  c3 = cos(input.z / 2);
  s1 = sin(input.x / 2);
  s2 = sin(input.y / 2);
  s3 = sin(input.z / 2);

#ifdef ALTERNATIVE_VEC2QUAT
  ret.w = sqrt(1.0f + (c1 * c2) + (c1 * c3) - (c1 * s2 * s3) + (c2 * c3)) / 2;
  ret.x = ((c2 * s3) + (c1 * s3) + (s1 * s2 * c3)) / (4.0f * ret.w);
  ret.y = ((s1 * c2) + (s1 * c3) + (c1 * s2 * s3)) / (4.0f * ret.w);
  ret.z = (((-1.0f * s1)) * s3) + (c1 * s2 *c3) * s2) / (4.0f * ret.w);
#else
  ret.w = (c1 * c2 * c3) - (s1 * s2 * s3);
  ret.x = (s1 * s2 * c3) - (c1 * c2 * s3);
  ret.y = (s1 * c2 * c3) - (c1 * s2 * s3);
  ret.z = (c1 * s2 * c3) - (s1 * c2 * s3);
#endif

  return ret;
}

Vec3D quat2vec(Quaternion input) {
  Vec3D ret;
  double t0, t1, t2, t3, t4;

  t0 = +2.0f * (input.w * input.x + input.y * input.z);
  t1 = +1.0f - 2.0f * (input.x * input.x + input.y * input.y);
  ret.x = atan2(t0, t1);

  t2 = 2.0f * (input.w * input.y - input.z * input.x);
  t2 = (t2 > 1.0f) ? 1.0f : t2;
  t2 = (t2 < -1.0f) ? -1.0f : t2;
  ret.y = asin(t2);

  t3 = 2.0f * (input.w * input.z + input.x * input.y);
  t4 = 1.0f - 2.0f * (input.y * input.y + input.z * input.z);
  ret.z = atan2(t3, t4);

  return ret;
}
