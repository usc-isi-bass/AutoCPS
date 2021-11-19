#include "ivp.h"

#include "datatypes.h"
#include "kalman.h"

ReferenceFrame center_frame;

// Get the translational transformation needed to go between these two frames 
Vec3D sensor_pos_to_system_pos(Vec3D coordinate, ReferenceFrame sensor_frame,
                               ReferenceFrame system_frame) {
  Vec3D ret;
  Vec3D transform;
  
  transform.x = sensor_frame.origin.x - system_frame.origin.x;
  transform.y = sensor_frame.origin.y - system_frame.origin.z;
  transform.z = sensor_frame.origin.z - system_frame.origin.z;

  ret.x = coordinate.x - transform.x;
  ret.y = coordinate.y - transform.y;
  ret.z = coordinate.z - transform.z;

  return ret;
}

// Get the rotation transformation needed to go between these two frames 
Quaternion sensor_rot_to_system_rot(Quaternion coordinate,
                                    ReferenceFrame sensor_frame,
                                    ReferenceFrame system_frame) {
  Quaternion new_rot;

    

  return new_rot;
}

Vec3D ivp_get_sensor_position(Sensor *sensor) {
  SensorData sensor_data;

  sensor_data = sensor_get_data(sensor);

  return sensor_pos_to_system_pos(sensor_data.output_position,
                                  sensor->sensor_frame,
                                  center_frame);
}

Quaternion ivp_get_sensor_rotation(Sensor *sensor) {
  SensorData sensor_data;
  Quaternion sensor_rotation;

  sensor_data = sensor_get_data(sensor);

  return sensor_rot_to_system_rot(sensor_rotation,
                                  sensor->sensor_frame,
                                  center_frame);
}
