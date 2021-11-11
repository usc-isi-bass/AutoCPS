#include "pos_ctrl.h"

#include "autocode.h"
#include "stub.h"

#include "ivp.h"
#include "kalman.h"
#include "sensor.h"
#include "seq.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// Whether to use curved waypoint navigation
bool pos_use_s_curve = false;

// Set whether to use curved waypoint navigation
void pos_set_curved_waypoints(bool use_curved_waypoints) {
  pos_use_s_curve = use_curved_waypoints;
}

// Get the next velocity heading to take
Vec3D pos_get_next_location(Vec3D current_location) {
  Vec3D target_location = seq_get_waypoint();
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
