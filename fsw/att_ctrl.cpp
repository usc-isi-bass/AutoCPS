#include "att_ctrl.h"
#include "params.h"

Quaternion att_calculate_lean_angle(Vec3D input_position, Vec3D input_waypoint) {
  Vec3D direction_euler = input_waypoint - input_position;

  // Make sure none of the waypoints are above the maximum climb rate
  if (direction_euler.x >= PROP_MAX_ANGLE) direction_euler.x = PROP_MAX_ANGLE;
  if (direction_euler.y >= PROP_MAX_ANGLE) direction_euler.y = PROP_MAX_ANGLE;
  if (direction_euler.z >= PROP_MAX_ANGLE) direction_euler.z = PROP_MAX_ANGLE;

  return vec2quat(direction_euler);
}

Quaternion att_calculate_rotation_rate(Vec3D input_position, Vec3D input_waypoint) {
  Vec3D direction_euler = input_waypoint - input_position;

  // Get the maximum angular velocity of helicopter



  return vec2quat(direction_euler);
}

double att_calculate_climb_rate(Vec3D input_position, Vec3D input_waypoint) {
  Vec3D direction_euler = input_waypoint - input_position;

  // Get the maximum angular velocity of helicopter
}

// Plane-only, calculate roll needed to get to waypoint
double att_calculate_roll(Vec3D input_position, Vec3D input_waypoint) {
  Vec3D direction_euler = input_waypoint - input_position;
  
}

// Plane-only, calculate pitch needed to get to waypoint
double att_calculate_pitch(Vec3D input_position, Vec3D input_waypoint) {
  Vec3D direction_euler = input_waypoint - input_position;
  
}

// Plane-only, calculate yaw needed to get to waypoint
double att_calculate_yaw(Vec3D input_position, Vec3D input_waypoint) {
  Vec3D direction_euler = input_waypoint - input_position;
  
}

double att_calculate_throttle(Vec3D input_position, Vec3D input_waypoint) {
  
}
