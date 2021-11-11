#ifndef SEQ_H
#define SEQ_H

#include <string>

#include "datatypes.h"

// Read input from file to get waypoints
void seq_create_waypoints(const std::string& filename);

// Get latest waypoint
Vec3D seq_get_waypoint();

// Remove latest waypoint, if reached
void seq_remove_waypoint();

#endif
