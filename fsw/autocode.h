#ifndef AUTOCODE_H
#define AUTOCODE_H

#include "datatypes.h"
#include "pos_ctrl.h"
#include "seq.h"

#include <queue>

void seq_autocode_fit_s_curve(std::queue<SeqWaypoint> target);

Vec3D pos_autocode_s_curve_derivative(Vec3D curr, SeqWaypoint target);

double pos_autocode_get_max_speed();

Vec3D att_autocode_calculate_lean_angle(PosOutputData input_waypoint);

#endif
