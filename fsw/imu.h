#ifndef IMU_H
#define IMU_H

#include "datatypes.h"

// Output struct for an IMU
struct ImuData {
  Vec3D gps_position;
  Vec3D accelerometer;
};

// Location data for an IMU based on reference frame of system
struct ImuUnit {
  Vec3D position;
  ReferenceFrame imu_frame;
};

// Get IMU data for one such unit
ImuData imu_get_measurement(ImuUnit *unit);

#endif
