#include "stub.h"

#include "autocode.h"
#include "ivp.h"
#include "params.h"

#include <cmath>
#include <limits>

Vec3D current_position, past_position, past_v;
Vec3D current_rotation, past_rotation;

ImuData stub_imu_get_measurement(ImuUnit *unit) {
  ImuData ret;
  ReferenceFrame sensor_fr, system_fr;
  Vec3D imu_location;
  double delta_t = 1.0f / CLOCK_TICKS_PER_SEC / 60;

  system_fr = ivp_get_system_frame();

  // Calculate new GPS location
  imu_location = current_position + unit->position;
  ret.gps_position = ivp_pos_convert_frame(imu_location, sensor_fr, system_fr);

  // Calculate current velocity
  ret.velocity = (current_position - imu_location) / delta_t;

  // Calculate new velocity as change in position over the last time frame
  ret.accelerometer = (ret.velocity - past_v) / delta_t;

  // Update position
  past_position = current_position;
  past_v = ret.velocity;

  return ret;
}

SensorData stub_sensor_get_measurement(SensorUnit *unit) {
  SensorData ret;
  ReferenceFrame sensor_fr, system_fr;
  Vec3D current_velocity;

  system_fr = ivp_get_system_frame();

  // Calculate new GPS location
  Vec3D gps_location = current_position + unit->position;
  ret.output_position = ivp_pos_convert_frame(gps_location, sensor_fr, system_fr);

  // Get output rotation based on current velocity
  ret.output_rotation = vec2quat(current_rotation);

  // Update position
  past_position = current_position;
  past_v = current_velocity;

  return ret;
}

void stub_servo_move(PosOutputData input_waypoint) {
  servo_autocode_servo_move(input_waypoint);
}
