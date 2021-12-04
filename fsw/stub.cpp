#include "stub.h"

#include <cmath>
#include <limits>
#include "ivp.h"
#include "params.h"

Vec3D current_position, past_position, past_velocity;

ImuData stub_imu_get_measurement(ImuUnit &unit) {
  ImuData ret;
  ReferenceFrame sensor_fr, system_fr;
  Vec3D current_velocity;

  system_fr = ivp_get_system_frame();

  // Calculate new GPS location
  Vec3D imu_location = current_position + unit.position;
  ret.gps_position = ivp_pos_convert_frame(imu_location, sensor_fr, system_fr);

  // Calculate new velocity as change in position over the last time frame

  ret.accelerometer = current_velocity - past_velocity;

  // Update position
  past_position = current_position;

  return ret;
}
