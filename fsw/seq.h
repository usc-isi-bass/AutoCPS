#ifndef SEQ_H
#define SEQ_H

#include <string>

#include "datatypes.h"

struct SeqWaypoint {
  Vec3D position;
  Quaternion rotation;
  double clock;
};

// Read input from file to get waypoints
void seq_create_waypoints(const std::string& filename);

// Get latest waypoint
SeqWaypoint seq_get_waypoint();

// Remove latest waypoint, if reached
void seq_remove_waypoint();

// Check if we still have waypoints remaining
bool seq_has_waypoints();

#endif
