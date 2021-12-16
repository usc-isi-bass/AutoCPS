#include "seq.h"

#include "autocode.h"

#include <fstream>
#include <queue>
#include <sstream>

using namespace std;

// Waypoint queue
std::queue<SeqWaypoint> seq_waypoints;

// Push a new set of waypoints in from a file
// This can simulate an autopilot or controller input
void seq_create_waypoints(const string filename) {
  ifstream input_file(filename);
  std::string line;
  SeqWaypoint input_waypoint;

  // Loop through and add all waypoints into input
  while (input_file.good()) {
    getline(input_file, line);
    stringstream input_stream(line);

    // Get x, y, z
    input_stream >> input_waypoint.position.x;
    input_stream >> input_waypoint.position.y;
    input_stream >> input_waypoint.position.z;

    input_stream >> input_waypoint.clock;

    // Add waypoint to the queue
    seq_waypoints.push(input_waypoint);
  }

  // Fit the sequence of waypoints to an s-curve
  seq_autocode_fit_s_curve(seq_waypoints);
}

// Get the last waypoint
SeqWaypoint seq_get_waypoint() {
  return seq_waypoints.front();
}

// Pop the last waypoint since we reached it already
void seq_remove_waypoint() {
  seq_waypoints.pop();
}

bool seq_has_waypoints() {
  return !seq_waypoints.empty();
}
