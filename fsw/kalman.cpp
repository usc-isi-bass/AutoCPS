#include "kalman.h"

#include "params.h"

KalmanFilter local_filter;

double delta_t = 1.0f / CLOCK_TICKS_PER_SEC / 60;

StateMatrix trans_matrix, identity_matrix, noise_matrix, uncertainty_matrix, last_cov_matrix;

void kalman_init() {
  // Build state transition matrix
  for (int i = 0; i < 6; i++) trans_matrix.v[i][i] = 1;
  trans_matrix.v[0][3] = delta_t;
  trans_matrix.v[1][4] = delta_t;
  trans_matrix.v[2][5] = delta_t;

  // Build identity matrix
  for (int i = 0; i < 6; i++)
    identity_matrix.v[i][i] = 1;

  // Build process noise matrix
  // TODO: generate somehow?

  // First covariance matrix is 100% accurate
  for (int i = 0; i < 6; i++)
    for (int it = 0; it < 6; it++)
      last_cov_matrix.v[i][it] = 1;
}

ImuData kalman_normalize_input(ImuData &input) {
  ImuData estimate;

#if KALMAN_ENABLE == 1
  StateMatrix covariance_pred, kalman_gain, measurement_matrix, temp;
  Vec3D estimate_velocity;

  // State extrapolation
  estimate.gps_position = local_filter.prev_position +
                          local_filter.prev_velocity * delta_t +
                          local_filter.prev_accel * 0.5 * pow(delta_t, 2);
  estimate.velocity = local_filter.prev_velocity * delta_t + local_filter.prev_position;
  estimate.accelerometer = local_filter.prev_accel;

  // Extrapolate covariance
  covariance_pred = trans_matrix * last_cov_matrix * trans_matrix.transpose() + noise_matrix;

  // Calculate Kalman gain
  temp = last_cov_matrix + noise_matrix;
  kalman_gain = last_cov_matrix * temp.transpose();

  // Update estimate with input measurement
  temp.v[0][0] = input.gps_position.x;
  temp.v[1][1] = input.gps_position.y;
  temp.v[2][2] = input.gps_position.z;
  temp.v[3][3] = input.accelerometer.x;
  temp.v[4][4] = input.accelerometer.y;
  temp.v[5][5] = input.accelerometer.z;
  local_filter.prev_state_matrix = local_filter.prev_state_matrix +
    kalman_gain * (temp - local_filter.prev_state_matrix);

  // Update state for next iteration
  local_filter.prev_position = input.gps_position;
  local_filter.prev_velocity.x = local_filter.prev_state_matrix.v[0][0];
  local_filter.prev_velocity.y = local_filter.prev_state_matrix.v[1][1];
  local_filter.prev_velocity.z = local_filter.prev_state_matrix.v[2][2];
  local_filter.prev_accel.x = local_filter.prev_state_matrix.v[3][3];
  local_filter.prev_accel.y = local_filter.prev_state_matrix.v[4][4];
  local_filter.prev_accel.z = local_filter.prev_state_matrix.v[5][5];

  // Update covariance matrix
  temp = (identity_matrix - kalman_gain);
  last_cov_matrix = temp * last_cov_matrix * temp.transpose() +
    kalman_gain * uncertainty_matrix * kalman_gain.transpose();
#else
  estimate = input;
#endif

  return estimate;
}