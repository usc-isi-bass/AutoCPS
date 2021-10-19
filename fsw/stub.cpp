#include "stub.h"

#include <cmath>
#include <limits>
#include "params.h"

using namespace std;

// Get the minimum of an array
inline double stub_min(const double* arr, const size_t size) {
  double local_min = numeric_limits<double>::max();

  for (int i = 0; i < size; i++)
    local_min = (arr[i] < local_min) ? arr[i] : local_min;

  return local_min;
}

double stub_estimate_max_speed() {
  if (fsw_system == ROVER) {
    return stub_min(motor_max_speeds, NUM_MOTORS);
  } else if (fsw_system == PLANE) {

  } else if (fsw_system == ROCKET) {

  } else if (fsw_system == HELICOPTER) {

  } else {
    return -1;
  }
}
