/*
 * Common datatype definitions
 */

#ifndef DATATYPES_H
#define DATATYPES_H

// Standard 2D vector
struct Vec2D {
  double x, y;
};

// Standard 3D vector
struct Vec3D {
  double x, y, z;
};

// Standard quarternion
struct Quat {
  double a, b, c, d;
};

#endif