#ifndef AUTOCODE_H
#define AUTOCODE_H

#include <cmath>
#include "params.h"

inline double pos_autocode_logistic_function(double x) {
  return 1 / (1 + exp(0 - x));
}

inline double pos_autocode_logistic_function_(double x) {
  return 1 / (1 + exp(0 - x));
}

inline double pos_autocode_logistic_function_derivative(double x) {
  return exp(x) / pow(exp(x) + 1, 2);
}

#endif
