#ifndef KALMAN_H
#define KALMAN_H

#include "datatypes.h"
#include "imu.h"

struct KalmanFilter {
  Vec3D prev_position;
  Vec3D prev_velocity;
  Vec3D prev_accel;
  StateMatrix prev_state_matrix;
};

// Initialize stuff
void kalman_init();

// Pass IMU data through Kalman filter
ImuData kalman_normalize_input(ImuData &input);

#endif
