#include "att_ctrl.h"
#include "params.h"

Quaternion att_calculate_lean_angle(Vec3D input_position, Vec3D input_waypoint) {
  Vec3D direction_euler = input_waypoint - input_position;

  

  return vec2quat(direction_euler);
}

Quaternion att_calculate_rotation_rate(Vec3D input_position, Vec3D input_waypoint) {

}

double att_calculate_climb_rate(Vec3D input_position, Vec3D input_waypoint) {
  
}

double att_calculate_roll(Vec3D input_position, Vec3D input_waypoint) {
  
}

double att_calculate_pitch(Vec3D input_position, Vec3D input_waypoint) {
  
}

double att_calculate_yaw(Vec3D input_position, Vec3D input_waypoint) {
  
}

double att_calculate_throttle(Vec3D input_position, Vec3D input_waypoint) {
  
}
