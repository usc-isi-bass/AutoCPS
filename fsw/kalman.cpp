#include "kalman.h"

#include "params.h"

KalmanFilter local_filter;

ImuData kalman_normalize_input(ImuData &input) {
  ImuData estimate;

  double delta_t = 1.0f / CLOCK_TICKS_PER_SEC / 60;

  // Prediction
  estimate.gps_position = local_filter.prev_position +
                          local_filter.prev_velocity * delta_t +
                          local_filter.prev_accel * 0.5 * pow(delta_t, 2);
  estimate.accelerometer = local_filter.prev_accel;

  // Correction
  local_filter.prev_position = input.gps_position;
  local_filter.prev_velocity = (input.gps_position - local_filter.prev_position) * delta_t;
  local_filter.prev_accel = input.accelerometer;

  return estimate;
}