#include "att_ctrl.h"

#include "autocode.h"
#include "params.h"

#include <cmath>

Quaternion att_calculate_lean_angle(PosOutputData input_waypoint) {
  return vec2quat(att_autocode_calculate_lean_angle(input_waypoint));
}

double att_calculate_climb_rate(PosOutputData input_waypoint) {
  double climb_rate = input_waypoint.position.z;
  return (climb_rate >= ATT_MAX_CLIMB_RATE) ? ATT_MAX_CLIMB_RATE : climb_rate;
}

// Plane-only, calculate roll needed to get to waypoint
double att_calculate_roll(PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position;
  
  if (direction_euler.x >= ATT_MAX_ROLL_ANGLE)
    return ATT_MAX_ROLL_ANGLE;
  else
    return direction_euler.x;
}

// Plane-only, calculate pitch needed to get to waypoint
double att_calculate_pitch(PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position;
  
  if (direction_euler.y >= ATT_MAX_PITCH_ANGLE)
    return ATT_MAX_PITCH_ANGLE;
  else
    return direction_euler.y;
}

// Plane-only, calculate yaw needed to get to waypoint
double att_calculate_yaw(PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position;
  
  if (direction_euler.z >= ATT_MAX_YAW_ANGLE)
    return ATT_MAX_YAW_ANGLE;
  else
    return direction_euler.z;
}

double att_calculate_speed(PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position;
  double ret;
  
  // Reach max speed if able
  ret = sqrt(pow(direction_euler.x, 2) + pow(direction_euler.y, 2) +
             pow(direction_euler.z, 2));
  if (ret > MAX_SPEED) ret = MAX_SPEED;

  // If not calculate minimum speed needed
  if (ret < STALL_SPEED) ret = STALL_SPEED;

  return ret;
}
