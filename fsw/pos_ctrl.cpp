#include "pos_ctrl.h"

#include "autocode.h"
#include "params.h"
#include "stub.h"

#include "autonav.h"
#include "clock.h"
#include "ivp.h"
#include "kalman.h"
#include "sensor.h"
#include "seq.h"

using namespace std;

// Whether to use curved waypoint navigation
bool pos_use_s_curve = false;

// Set whether to use curved waypoint navigation
void pos_set_curved_waypoints(bool use_curved_waypoints) {
  pos_use_s_curve = use_curved_waypoints;
}

// Get the next velocity heading to take
PosOutputData pos_get_next_location(Vec3D current_location) {
  SeqWaypoint target_location = autonav_get_waypoint();
  PosOutputData ret;

  if (pos_use_s_curve) {
    // Set new waypoint based on derivative
    double max_change_in_time_slice = pos_autocode_get_max_speed() * CLOCK_TICKS_PER_SEC;
    ret.target_position = pos_autocode_s_curve_derivative(current_location, target_location) * max_change_in_time_slice;

    return ret;
  } else {
    // For straight-line navigation, just send in next waypoint
    return ret;
  }
}
