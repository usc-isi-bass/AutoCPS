#include <stdexcept>
#include "datatypes.h"

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

void AXIStream::push_back() {

}

void AXIStream::pop_out() {

}

void AXIStream::size() {

}
