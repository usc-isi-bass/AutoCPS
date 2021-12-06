#ifndef AUTOCODE_H
#define AUTOCODE_H

#include "datatypes.h"
#include "params.h"
#include "seq.h"

#include <cmath>
#include <queue>

// Optional define
#define ALTERNATIVE_VEC2QUAT

// Constants for use with the S-curve functions
double pos_autocode_s_curve_constant_1;
double pos_autocode_s_curve_constant_2;
double pos_autocode_s_curve_constant_3;

inline void seq_autocode_fit_s_curve(std::queue<SeqWaypoint> target) {
  // TODO: examine curve fitting methods
  pos_autocode_s_curve_constant_1 = 3.25f;
  pos_autocode_s_curve_constant_2 = 2.5f;
  pos_autocode_s_curve_constant_3 = 1.0f;
}

inline Vec3D pos_autocode_s_curve_derivative(Vec3D curr, SeqWaypoint target) {
  Vec3D ret;

  // Do calculations
  ret.x = pos_autocode_s_curve_constant_1 * pos_autocode_s_curve_constant_2 * exp(
          -1.0 * pos_autocode_s_curve_constant_1 * (curr.x - pos_autocode_s_curve_constant_3)) /
         pow(exp(-1.0 * pos_autocode_s_curve_constant_1 * (curr.x - pos_autocode_s_curve_constant_3)) +
            1, 2);
  ret.y = pos_autocode_s_curve_constant_1 * pos_autocode_s_curve_constant_2 * exp(
          -1.0 * pos_autocode_s_curve_constant_1 * (curr.y - pos_autocode_s_curve_constant_3)) /
         pow(exp(-1.0 * pos_autocode_s_curve_constant_1 * (curr.y - pos_autocode_s_curve_constant_3)) +
            1, 2);
  ret.z = pos_autocode_s_curve_constant_1 * pos_autocode_s_curve_constant_2 * exp(
          -1.0 * pos_autocode_s_curve_constant_1 * (curr.z - pos_autocode_s_curve_constant_3)) /
         pow(exp(-1.0 * pos_autocode_s_curve_constant_1 * (curr.z - pos_autocode_s_curve_constant_3)) +
            1, 2);

  normalize(ret);

  return ret;
}

inline double pos_autocode_get_max_speed() {
  return 125.0;
}

#endif
