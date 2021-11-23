#ifndef SENSOR_H
#define SENSOR_H

#include "datatypes.h"

// Basic datatype for a sensor
struct SensorData {
  Vec3D output_position;
  Quaternion output_rotation;
};

// Basic datatype for a sensor
struct Sensor {
  ReferenceFrame sensor_frame;
};

SensorData sensor_get_data(Sensor *sensor);

#endif
