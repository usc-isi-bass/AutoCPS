/*
 * Common datatype definitions
 */

#ifndef DATATYPES_H
#define DATATYPES_H

// Standard 2D vector
struct Vec2D {
  double x, y;
  Vec2D operator-(Vec2D& a);
};

// Standard 3D vector
struct Vec3D {
  double x, y, z;
  Vec3D operator-(Vec3D& a);
};

// Standard quarternion
struct Quaternion {
  double w, x, y, z;
};

Quaternion vec2quat(Vec3D input);

#endif