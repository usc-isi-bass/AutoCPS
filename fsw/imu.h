#ifndef IMU_H
#define IMU_H

#include "datatypes.h"

// Output struct for an IMU
struct ImuData {
  Vec3D gps_position;
  Vec3D accelerometer;
  Quaternion gyroscope;
};

#endif
