/*
 * Common datatype definitions
 */

#ifndef DATATYPES_H
#define DATATYPES_H

// Standard 3D vector
struct Vec3D {
  double x, y, z;
  Vec3D operator+(Vec3D a);
  Vec3D operator-(Vec3D& a);
  double operator*(Vec3D& a);
  Vec3D operator*(double a);
  Vec3D operator/(double a);
};

// Standard quarternion
struct Quaternion {
  double w, x, y, z;
  Quaternion operator*(Quaternion a);
  Quaternion operator*(Quaternion& a);
  Quaternion conj();
};

// Definition of an inertial reference frame by the 3 unit vectors
struct ReferenceFrame {
  Vec3D i, j, k;
  ReferenceFrame();
};

// 6x6 matrix for 3-dimensional attitude
struct StateMatrix {
  double v[6][6];
  StateMatrix operator+(StateMatrix rhs);
  StateMatrix operator-(StateMatrix rhs);
  StateMatrix operator*(StateMatrix rhs);
  StateMatrix operator*(double rhs);
  StateMatrix transpose();
};

// Quaternion/Euler rotation conversions
Quaternion vec2quat(Vec3D input);
Vec3D quat2vec(Quaternion input);

// Normalize vectors/quaternions
Vec3D normalize(Vec3D input);
Quaternion normalize(Quaternion input);

#endif
