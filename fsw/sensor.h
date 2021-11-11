#ifndef SENSOR_H
#define SENSOR_H

#include "datatypes.h"

// Basic datatype for a sensor
struct Sensor {
  Vec3D sensor_position;
  Quaternion sensor_orientation;

  Vec3D sensor_output_position;
  Quaternion sensor_output_rotation;
};

#endif
