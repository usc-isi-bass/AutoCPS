#ifndef IMU_H
#define IMU_H

// IMU module 

#include "datatypes.h"
#include <deque>

// Final output of IMU
struct IMUData {
  Quarternion linear_accel;
  Quarternion angular_accel;
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

// Recieve a quarternion from AXI stream
Quarternion receive_axi_stream();

// Recieve data from a sensor and feed it into the calculations
IMUInputData data_recieve_sensors();

// Main loop of IMU unit, continuously runs when called by startup script
void imu_loop(AXIStream &input_st, AXIStream &output_st);

#endif /*IMU_H*/
