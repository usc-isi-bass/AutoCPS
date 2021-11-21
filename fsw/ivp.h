#ifndef IVP_H
#define IVP_H

#include "datatypes.h"
#include "sensor.h"

// Transform a coordinate in one reference frame into another
Vec3D ivp_pos_convert_frame(Vec3D coordinate,
                            ReferenceFrame sensor_frame,
                            ReferenceFrame system_frame);

// Transform a rotation in one reference frame into another
Quaternion ivp_rot_convert_frame(Vec3D coordinate,
                                 ReferenceFrame sensor_frame,
                                 ReferenceFrame system_frame);


Vec3D ivp_get_sensor_position(Sensor *sensor);

Quaternion ivp_get_sensor_rotation(Sensor *sensor);

ReferenceFrame ivp_get_system_frame();
void ivp_set_system_frame(ReferenceFrame &ref);

#endif
