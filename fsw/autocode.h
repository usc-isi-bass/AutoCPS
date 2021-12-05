#ifndef AUTOCODE_H
#define AUTOCODE_H

#include "params.h"
#include <cmath>

// Constants for use with the S-curve functions
double pos_autocode_s_curve_constant_1 = 3.25f;
double pos_autocode_s_curve_constant_2 = 2.5f;
double pos_autocode_s_curve_constant_3 = 1.0f;

// Optional define
#define ALTERNATIVE_VEC2QUAT

inline double pos_autocode_generate_s_curve(Vec2D x, Vec2D y) {
  // TODO: examine curve fitting methods
  return x.x;
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

inline double autocode_clock_timer_ticks_to_epoch(long timer_ticks) {
  return (double) timer_ticks * 100;
}

#endif
