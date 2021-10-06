#include <cmath>
#include <stdexcept>

#include "datatypes.h"

void AXIToken::input_double(double v) {
  this->a = v;

  this->type = "double";
}

void AXIToken::input_vec2d(Vec2D v) {
  this->a = v.x;
  this->b = v.y;

  this->type = "Vec2D";
}

void AXIToken::input_vec3d(Vec3D v) {
  this->a = v.x;
  this->b = v.y;
  this->c = v.z;

  this->type = "Vec3D";
}

void AXIToken::input_quart(Quarternion q) {
  this->a = q.a;
  this->b = q.b;
  this->c = q.c;
  this->d = q.d;

  this->type = "Quarternion";
}

double AXIToken::output_double() {
  if (this->type != "double") {
    std::string err_msg = "AXIToken: Expected double but got " + this->type;
    throw std::invalid_argument(err_msg);
  }

  return this->a;
}

Vec2D AXIToken::output_vec2d() {
  if (this->type != "Vec2D") {
    std::string err_msg = "AXIToken: Expected Vec2D but got " + this->type;
    throw std::invalid_argument(err_msg);
  }

  Vec2D ret;
  ret.x = this->a;
  ret.y = this->b;
  return ret;
}

Vec3D AXIToken::output_vec3d() {
  if (this->type != "Vec3D") {
    std::string err_msg = "AXIToken: Expected Vec3D but got " + this->type;
    throw std::invalid_argument(err_msg);
  }

  Vec3D ret;
  ret.x = this->a;
  ret.y = this->b;
  ret.z = this->c;
  return ret;
}

Quarternion AXIToken::output_quart() {
  if (this->type != "Quarternion") {
    std::string err_msg = "AXIToken: Expected Quarternion but got " + this->type;
    throw std::invalid_argument(err_msg);
  }

  Quarternion ret;
  ret.a = this->a;
  ret.b = this->b;
  ret.c = this->c;
  ret.d = this->d;
  return ret;
}

void AXIStream::push(AXIToken t) {
  buffer.push(t);
}

AXIToken AXIStream::get() {
  AXIToken ret;
  ret.type = "empty";

  if (!buffer.empty()) {
    ret = buffer.front();
    buffer.pop();
  }

  return ret;
}

inline Quarternion convert_to_quarternion(Vec3D v) {
  Quarternion ret;

  double c1 = cos(v.z * 0.5);
  double c2 = cos(v.y * 0.5);
  double c3 = cos(v.x * 0.5);
  double s1 = sin(v.z * 0.5);
  double s2 = sin(v.y * 0.5);
  double s3 = sin(v.x * 0.5);

  ret.a = c1 * c2 * s3 - s1 * s2 * c3;
  ret.a = c1 * s2 * c3 + s1 * c2 * s3;
  ret.a = s1 * c2 * c3 - c1 * s2 * s3;
  ret.a = c1 * c2 * c3 + s1 * s2 * s3;

  return ret;
}
