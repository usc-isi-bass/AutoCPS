#ifndef POS_CTRL_H
#define POS_CTRL_H

#include <queue>
#include <string>

#include "datatypes.h"

// Read input from file to get waypoints
void create_waypoints(const std::string& filename);

// Get latest waypoint
Vec3D get_waypoint();

#endif
