#include "stub.h"

#include <cmath>
#include <limits>
#include "ivp.h"
#include "params.h"

Vec3D current_position;
Quaternion current_rotation;

ImuData stub_imu_get_measurement(ImuUnit &unit) {
  ImuData ret;
  ReferenceFrame sensor_fr, system_fr = ivp_get_system_frame();

  Vec3D imu_location = current_position + unit.position;

  ret.gps_position = ivp_pos_convert_frame(imu_location, sensor_fr, system_fr);

  Quaternion imu_rotation = current_rotation * unit.rotation;

  ret.gyroscope = ivp_rot_convert_frame(imu_rotation, sensor_fr, system_fr);

  return ret;
}
