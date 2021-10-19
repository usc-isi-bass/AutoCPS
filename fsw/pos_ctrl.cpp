#include "pos_ctrl.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// Waypoint queue
std::queue<Vec3D> waypoints;

void create_waypoints(const std::string& filename) {
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
    waypoints.push(input_waypoint);
  }
}

Vec3D get_waypoint() {
  return waypoints.front();
}
