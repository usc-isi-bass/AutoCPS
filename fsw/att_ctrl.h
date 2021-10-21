#ifndef ATT_CTRL_H
#define ATT_CTRL_H

#include "datatypes.h"

Quaternion att_calculate_lean_angle(Vec3D input_position, Vec3D input_waypoint);
Quaternion att_calculate_rotation_rate(Vec3D input_position, Vec3D input_waypoint);
double att_calculate_climb_rate(Vec3D input_position, Vec3D input_waypoint);

double att_calculate_roll(Vec3D input_position, Vec3D input_waypoint);
double att_calculate_pitch(Vec3D input_position, Vec3D input_waypoint);
double att_calculate_yaw(Vec3D input_position, Vec3D input_waypoint);
double att_calculate_throttle(Vec3D input_position, Vec3D input_waypoint);

#endif
