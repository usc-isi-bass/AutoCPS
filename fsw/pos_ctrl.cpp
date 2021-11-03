#include "pos_ctrl.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include "autocode.h"
#include "stub.h"

using namespace std;

// Waypoint queue
std::queue<Vec3D> pos_waypoints;

// Whether to use curved waypoint navigation
bool pos_use_s_curve = false;

// Push a new set of waypoints in from a file
// This can simulate an autopilot or contorller input
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

// Set whether to use curved waypoint navigation
void pos_set_curved_waypoints(bool use_curved_waypoints) {
  pos_use_s_curve = use_curved_waypoints;
}

// Get the last waypoint
Vec3D pos_get_waypoint() {
  return pos_waypoints.front();
}

// Pop the last waypoint since we reached it already
void pos_remove_waypoint() {
  pos_waypoints.pop();
}

// Get the next velocity heading to take
Vec3D pos_get_next_location(Vec3D current_location) {
  Vec3D target_location = pos_get_waypoint();
  Vec3D ret;

  if (pos_use_s_curve) {
    // Set new waypoint based on derivative
    double max_speed = pos_autocode_get_max_speed();
    ret.x = pos_autocode_s_curve_derivative(current_location.x) * max_speed;
    ret.y = pos_autocode_s_curve_derivative(current_location.y) * max_speed;
    ret.z = pos_autocode_s_curve_derivative(current_location.z) * max_speed;
    return ret;
  } else {
    // For straight-line navigation, just send in next waypoint
    return target_location;
  }
}
