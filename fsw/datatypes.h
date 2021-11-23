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
  Vec3D operator+(Vec3D& a);
  Vec3D operator-(Vec3D& a);
  double operator*(Vec3D& a);
};

// Standard quarternion
struct Quaternion {
  double w, x, y, z;
  Quaternion operator*(Quaternion& a);
};

// Definition of an inertial reference frame by the 3 unit vectors
struct ReferenceFrame {
  Vec3D i, j, k;
  ReferenceFrame();
};

Quaternion vec2quat(Vec3D input);

Vec3D quat2vec(Quaternion input);

Vec3D normalize_vec(Vec3D input);

#endif
