#ifndef KALMAN_H
#define KALMAN_H

#include "datatypes.h"
#include "imu.h"

struct KalmanFilter {
  double x;
};

// Pass IMU data through Kalman filter
ImuData kalman_normalize_input(ImuData &input);

#endif
