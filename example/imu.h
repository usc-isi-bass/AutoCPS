#ifndef IMU_H
#define IMU_H

// IMU module 

#include "datatypes.h"
#include <deque>
#include <memory>

// Final output of IMU
struct IMUData {
  Quarternion linear_accel;
  Quarternion angular_accel;
  Quarternion location;
  Quarternion orientation;
};

// IMU internal datatype
struct IMUInputData {
  // Simulated GPS
  Vec3D gps_satellite_a, gps_satellite_b, gps_satellite_c;
  double gps_distance_a, gps_distance_b, gps_distance_c;
  // Simulated inertial navigation system
  Vec3D rotational, linear;
};

// Main loop of IMU unit, continuously runs when called by startup script
void imu_main_loop(std::shared_ptr<AXIStream> input, std::shared_ptr<AXIStream> output);

#endif /*IMU_H*/
