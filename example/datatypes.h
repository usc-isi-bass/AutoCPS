#ifndef DATATYPES_H
#define DATATYPES_H

#include <queue>
#include <string>

// Contains definitons and mutators for commonly used datatypes

// Standard 2D vector
struct Vec2D {
  double x;
  double y;
};

// Standard 3D vector
struct Vec3D {
  double x;
  double y;
  double z;
};

// Standard Quarternion
struct Quarternion {
  double a;
  double b;
  double c;
  double d;
};

// Simulated AXI-streaming interface using a deque to insert symbols
// Assuming we the data entered has up to 4 values in it
class AXIToken {
private:
  double a;
  double b;
  double c;
  double d;
  std::string type;
public:
  void input_vec2d(Vec2D v);
  void input_vec3d(Vec3D v);
  void input_quart(Quarternion q);
  
  Vec2D output_vec2d();
  Vec3D output_vec3d();
  Quarternion output_quart();
};

class AXIStream {
private:
  std::queue<AXIToken> buffer;
public:
  void push_back();
  void pop_out();
  void size();
};

#endif /*DATATYPES_H*/

