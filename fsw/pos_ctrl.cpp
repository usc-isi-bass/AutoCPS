#include "pos_ctrl.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include "autocode.h"
#include "stub.h"

using namespace std;

// Waypoint queue
std::queue<Vec3D> pos_waypoints;

// Whether to use waypoints
bool pos_use_curved_waypoints = false;

void pos_create_waypoints(const std::string& filename) {
  ifstream input_file(filename);
  std::string line;
  Vec3D input_waypoint;

  // Loop through and add all waypoints into input
  while (input_file.good()) {
    getline(input_file, line);
    stringstream input_stream(line);

    // Get x, y, z
    input_stream >> input_waypoint.x;
    input_stream >> input_waypoint.y;
    input_stream >> input_waypoint.z;

    // Add waypoint to the queue
    pos_waypoints.push(input_waypoint);
  }
}

void pos_set_curved_waypoints(bool use_curved_waypoints) {
  pos_use_curved_waypoints = use_curved_waypoints;
}

Vec3D pos_get_waypoint() {
  return pos_waypoints.front();
}

void pos_remove_waypoint() {
  pos_waypoints.pop();
}

Vec3D pos_get_next_location() {
  Vec3D target_location = pos_get_waypoint();

  if (pos_use_curved_waypoints) {
    double max_speed = stub_estimate_max_speed();
    
  } else {
    // For straight-line navigation, just send in next waypoint
    return target_location;
  }
}
