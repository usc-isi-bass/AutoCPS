#ifndef AUTOCODE_H
#define AUTOCODE_H

#include <cmath>
#include "params.h"

// Constants for use with the S-curve functions
double pos_autocode_s_curve_constant_1 = 3.25f;
double pos_autocode_s_curve_constant_2 = 2.5f;
double pos_autocode_s_curve_constant_3 = 1.0f;

inline double pos_autocode_generate_s_curve(Vec2D x, Vec2D y) {
  // TODO: examine curve fitting methods
}

inline double pos_autocode_s_curve_derivative(double x) {
  return pos_autocode_s_curve_constant_1 * pos_autocode_s_curve_constant_2 * exp(
          -1.0 * pos_autocode_s_curve_constant_1 * (x - pos_autocode_s_curve_constant_3)) /
         pow(exp(-1.0 * pos_autocode_s_curve_constant_1 * (x - pos_autocode_s_curve_constant_3)) +
            1, 2);
}

inline double pos_autocode_get_max_speed() {
  return 125.0;
}

#endif
