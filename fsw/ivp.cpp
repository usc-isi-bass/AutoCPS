#include "ivp.h"
#include "kalman.h"
#include "sensor.h"


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
Quaternion sensor_rot_to_system_rot(Vec3D coordinate,
                                    ReferenceFrame sensor_frame,
                                    ReferenceFrame system_frame) {
  Quaternion ret;

  return ret;
}
