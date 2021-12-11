#ifndef ATT_CTRL_H
#define ATT_CTRL_H

#include "datatypes.h"
#include "pos_ctrl.h"

struct AttInputData {
  Vec3D position;
  Vec3D acceleration;
};

Quaternion att_calculate_lean_angle(AttInputData input_position, PosOutputData input_waypoint);
Quaternion att_calculate_rotation_rate(AttInputData input_position, PosOutputData input_waypoint);
double att_calculate_climb_rate(AttInputData input_position, PosOutputData input_waypoint);

double att_calculate_roll(AttInputData input_position, PosOutputData input_waypoint);
double att_calculate_pitch(AttInputData input_position, PosOutputData input_waypoint);
double att_calculate_yaw(AttInputData input_position, PosOutputData input_waypoint);
double att_calculate_throttle(AttInputData input_position, PosOutputData input_waypoint);

#endif
