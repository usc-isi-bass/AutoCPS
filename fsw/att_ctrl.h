#ifndef ATT_CTRL_H
#define ATT_CTRL_H

#include "datatypes.h"
#include "pos_ctrl.h"

struct AttInputData {
  Vec3D position;
  Vec3D acceleration;
  Quaternion rotation;
};

Quaternion att_calculate_lean_angle(PosOutputData input_waypoint);
double att_calculate_climb_rate(PosOutputData input_waypoint);

double att_calculate_roll(PosOutputData input_waypoint);
double att_calculate_pitch(PosOutputData input_waypoint);
double att_calculate_yaw(PosOutputData input_waypoint);
double att_calculate_throttle(PosOutputData input_waypoint);

#endif
