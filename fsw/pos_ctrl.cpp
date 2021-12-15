#include "pos_ctrl.h"

#include "autocode.h"
#include "params.h"
#include "stub.h"

#include "autonav.h"
#include "clock.h"
#include "ivp.h"
#include "kalman.h"
#include "seq.h"

using namespace std;

// Whether to use curved waypoint navigation
bool pos_use_s_curve = false;

// List of sensors to poll
SensorUnit* pos_sensor_list[20];
size_t pos_sensor_count = 0;

// List of IMUs to poll
ImuUnit* pos_imu_list[20];
size_t pos_imu_count = 0;

// Set whether to use curved waypoint navigation
void pos_set_curved_waypoints(bool use_curved_waypoints) {
  pos_use_s_curve = use_curved_waypoints;
}

// Get the next velocity heading to take
PosOutputData pos_get_next_location(PosOutputData current_location) {
  SeqWaypoint target_location = autonav_get_waypoint();
  PosOutputData ret;

  double max_change_in_time_slice = pos_autocode_get_max_speed() * CLOCK_TICKS_PER_SEC;
  if (pos_use_s_curve) {
    // Set new waypoint based on derivative
    ret.position = pos_autocode_s_curve_derivative(current_location.position, target_location) * max_change_in_time_slice;

    // Get target rotation based on new location from previous location
    ret.rotation = target_location.rotation * current_location.rotation.conj();
  } else {
    // For straight-line navigation, just send in next waypoint
    ret.position = (current_location.position - target_location.position) * max_change_in_time_slice;

    // Get target rotation based on new location from previous location
    ret.rotation = target_location.rotation * current_location.rotation.conj();
  }

  return ret;
}

// Add a sensor to poll when doing pos_get_data
void pos_add_sensor(SensorUnit *sensor) {
  pos_sensor_list[pos_sensor_count] = sensor;
  pos_sensor_count++;
}

// Add an IMU to poll when doing pos_get_data
void pos_add_imu(ImuUnit *imu) {
  pos_imu_list[pos_imu_count] = imu;
  pos_imu_count++;
}

PosOutputData pos_get_data() {
  PosOutputData ret;
  Vec3D estim_loc;

  // Average them out i guess?
  for (size_t i = 0; i < pos_sensor_count; i++) {
    ivp_get_sensor_position(pos_sensor_list[pos_sensor_count]);
  }

  for (size_t i = 0; i < pos_imu_count; i++) {

  }
}
