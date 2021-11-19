#ifndef IVP_H
#define IVP_H

#include "datatypes.h"
#include "sensor.h"

// Transform a coordinate in one reference frame into another
Vec3D sensor_pos_to_system_pos(Vec3D coordinate, ReferenceFrame sensor_frame,
                               ReferenceFrame system_frame);

// Transform a rotation in one reference frame into another
Quaternion sensor_rot_to_system_rot(Vec3D coordinate,
                                    ReferenceFrame sensor_frame,
                                    ReferenceFrame system_frame);


Vec3D ivp_get_sensor_position(Sensor *sensor);

Quaternion ivp_get_sensor_rotation(Sensor *sensor);

#endif
