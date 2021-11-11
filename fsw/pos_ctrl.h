#ifndef POS_CTRL_H
#define POS_CTRL_H

#include "datatypes.h"

// Choose whether to use curved waypoints
void pos_set_curved_waypoints(bool use_curved_waypoints);

// Calculate next waypoint to give to attitude control
Vec3D seq_get_next_location();

#endif
