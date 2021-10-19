#ifndef POS_CTRL_H
#define POS_CTRL_H

#include <queue>
#include <string>

#include "datatypes.h"

// Read input from file to get waypoints
void pos_create_waypoints(const std::string& filename);

// Choose whether to use curved waypoints
void pos_set_curved_waypoints(bool use_curved_waypoints);

// Get latest waypoint
Vec3D pos_get_waypoint();

// Remove latest waypoint, if reached
void pos_remove_waypoint();

// Calculate next waypoint to give to attitude control
Vec3D pos_get_next_location();

#endif
