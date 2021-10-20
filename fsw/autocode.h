#ifndef AUTOCODE_H
#define AUTOCODE_H

#include <cmath>
#include "params.h"

inline double pos_autocode_logistic_function(double x) {
  return 1.0f / (1.0f + exp(0.0f - x));
}

inline double pos_autocode_logistic_function_inverse(double x) {
  return 0.0f - log(1.0f / x - 1.0f);
}

inline double pos_autocode_logistic_function_derivative(double x) {
  return exp(x) / pow(exp(x) + 1.0f, 2);
}

#endif
