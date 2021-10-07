#ifndef IMU_H
#define IMU_H

// IMU module 

#include "datatypes.h"
#include <deque>
#include <memory>

// Final output of IMU
struct IMUOutputData {
  Quarternion linear_velocity;
  Quarternion linear_accel;
  Quarternion angular_velocity;
  Quarternion angular_accel;
  Vec3D location;
  Quarternion orientation;
};

// IMU internal datatype
struct IMUInputData {
  // Simulated GPS
  Vec3D gps_satellite_a, gps_satellite_b, gps_satellite_c;
  double gps_distance_a, gps_distance_b, gps_distance_c;
  // Simulated IMU accelerations
  Vec3D rotational, linear;
  // Location of input data
  Vec3D sensor_location;
};

// Main loop of IMU unit, continuously runs when called by startup script
void imu_main_loop(std::shared_ptr<AXIStream> input_st,
                   std::shared_ptr<AXIStream> output_st);

#endif /*IMU_H*/
