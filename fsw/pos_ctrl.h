#ifndef POS_CTRL_H
#define POS_CTRL_H

#include "datatypes.h"
#include "imu.h"
#include "sensor.h"

struct PosOutputData {
  Vec3D position;
  Quaternion rotation;
};

// Choose whether to use curved waypoints
void pos_set_curved_waypoints(bool use_curved_waypoints);

// Calculate next waypoint to give to attitude control
PosOutputData pos_get_next_location();

// Add IMU or sensor to poll as needed
void pos_add_sensor(SensorUnit *sensor);
void pos_add_imu(ImuUnit *imu);

// Calculate current location based on data from kalman and imu
PosOutputData pos_get_current_location();

#endif
