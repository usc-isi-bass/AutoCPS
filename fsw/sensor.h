#ifndef SENSOR_H
#define SENSOR_H

#include "datatypes.h"

// Basic datatype for a sensor
struct SensorData {
  Vec3D output_position;
  Quaternion output_rotation;
};

// Basic datatype for a sensor
struct SensorUnit {
  ReferenceFrame sensor_frame;
  Vec3D position;
};

SensorData sensor_get_data(SensorUnit *sensor);

#endif
