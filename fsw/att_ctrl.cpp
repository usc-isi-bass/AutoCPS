#include "att_ctrl.h"

#include "params.h"

#include <cmath>

Quaternion att_calculate_lean_angle(AttInputData input_position, PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position - input_position.position;

  // Make sure none of the waypoints are above the maximum climb rate
  if (direction_euler.x >= PROP_MAX_ANGLE) direction_euler.x = PROP_MAX_ANGLE;
  if (direction_euler.y >= PROP_MAX_ANGLE) direction_euler.y = PROP_MAX_ANGLE;
  if (direction_euler.z >= PROP_MAX_ANGLE) direction_euler.z = PROP_MAX_ANGLE;

  return vec2quat(direction_euler);
}

Quaternion att_calculate_rotation_rate(AttInputData input_position, PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position - input_position.position;

  // Get the maximum angular velocity of helicopter
  double direction_magnitude = sqrt(pow(direction_euler.x, 2) +
                                    pow(direction_euler.y, 2) +
                                    pow(direction_euler.z, 2));

  // Switch to max magnitude if needed
  if (direction_magnitude > ATT_MAX_ROTATION_RATE) {
    direction_euler = normalize(direction_euler);
    direction_euler.x *= ATT_MAX_ROTATION_RATE;
    direction_euler.y *= ATT_MAX_ROTATION_RATE;
    direction_euler.z *= ATT_MAX_ROTATION_RATE;
  }

  return vec2quat(direction_euler);
}

double att_calculate_climb_rate(AttInputData input_position, PosOutputData input_waypoint) {
  Vec3D direction = quat2vec(att_calculate_rotation_rate(input_position,
                                                         input_waypoint));

  // Check if we even need to climb
  if (direction.z == ATT_MAX_ROTATION_RATE) {

  }


}

// Plane-only, calculate roll needed to get to waypoint
double att_calculate_roll(AttInputData input_position, PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position - input_position.position;
  

}

// Plane-only, calculate pitch needed to get to waypoint
double att_calculate_pitch(AttInputData input_position, PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position - input_position.position;
  
}

// Plane-only, calculate yaw needed to get to waypoint
double att_calculate_yaw(AttInputData input_position, PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position - input_position.position;
  
}

double att_calculate_throttle(AttInputData input_position, PosOutputData input_waypoint) {
  Vec3D direction_euler = input_waypoint.position - input_position.position;
  
}
