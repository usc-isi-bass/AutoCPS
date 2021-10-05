// FSW stub that lets simulator interface with software 

#include "imu.h"

// Stubbed function to send data to IMU
IMUInputData imu_data_recieve_sensors() {
  IMUInputData data;
  Vec3D zero;

  // Set every field to zero
  zero.x = 0;
  zero.y = 0;
  zero.z = 0;
  data.rotational = zero;
  data.linear = zero;
  data.gps_satellite_a = zero;
  data.gps_satellite_b = zero;
  data.gps_satellite_c = zero;
  data.gps_distance_a = 0;
  data.gps_distance_b = 0;
  data.gps_distance_c = 0;

  return data;
}
