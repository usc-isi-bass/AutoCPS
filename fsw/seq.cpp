#include "seq.h"

#include <fstream>
#include <queue>
#include <sstream>

using namespace std;

// Waypoint queue
std::queue<Vec3D> seq_waypoints;

// Push a new set of waypoints in from a file
// This can simulate an autopilot or controller input
void seq_create_waypoints(const string& filename) {
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
    seq_waypoints.push(input_waypoint);
  }
}

// Get the last waypoint
Vec3D seq_get_waypoint() {
  return seq_waypoints.front();
}

// Pop the last waypoint since we reached it already
void seq_remove_waypoint() {
  seq_waypoints.pop();
}