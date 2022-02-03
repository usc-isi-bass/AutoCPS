#include "ivp.h"

#include "datatypes.h"
#include "params.h"
#include "kalman.h"

ReferenceFrame system_frame;

// Build a transformation matrix from two reference frames
TransformationMatrix ivp_build_transform_matrix(ReferenceFrame &frame_1,
                                                ReferenceFrame &frame_2) {
  TransformationMatrix ret;
  Vec3D fr1, fr2;

  ret.t11 = frame_1.i * frame_2.i;
  ret.t12 = frame_1.i * frame_2.j;
  ret.t13 = frame_1.i * frame_2.k;

  ret.t21 = frame_1.j * frame_2.i;
  ret.t22 = frame_1.j * frame_2.j;
  ret.t23 = frame_1.j * frame_2.k;

  ret.t31 = frame_1.k * frame_2.i;
  ret.t32 = frame_1.k * frame_2.j;
  ret.t33 = frame_1.k * frame_2.k;

  return ret;
}

// Get the translational transformation needed to go between these two frames 
Vec3D ivp_pos_convert_frame(Vec3D coordinate,
                            ReferenceFrame &sensor_frame,
                            ReferenceFrame &system_frame) {
  Vec3D ret;
  TransformationMatrix transform = ivp_build_transform_matrix(sensor_frame, system_frame);

  // Just multiply by transformation matrix to get new position
  ret.x = coordinate.x * (transform.t11 + transform.t12 + transform.t13);
  ret.y = coordinate.y * (transform.t21 + transform.t22 + transform.t23);
  ret.z = coordinate.z * (transform.t31 + transform.t32 + transform.t33);

  return ret;
}

// Get the translational transformation needed to go between these two frames 
Quaternion ivp_rot_convert_frame(Quaternion coordinate,
                            ReferenceFrame &sensor_frame,
                            ReferenceFrame &system_frame) {
  Vec3D ret = quat2vec(coordinate);
  TransformationMatrix transform = ivp_build_transform_matrix(sensor_frame, system_frame);

  // Just multiply by transformation matrix to get new position
  ret.x = coordinate.x * (transform.t11 + transform.t12 + transform.t13);
  ret.y = coordinate.y * (transform.t21 + transform.t22 + transform.t23);
  ret.z = coordinate.z * (transform.t31 + transform.t32 + transform.t33);

  return vec2quat(normalize(ret));
}

Vec3D ivp_get_sensor_position(SensorUnit *sensor) {
#if SENSOR_ENABLE == 1
  SensorData sensor_data = sensor_get_data(sensor);

  return ivp_pos_convert_frame(sensor_data.output_position,
                               sensor->sensor_frame,
                               system_frame);
#else
  // Return empty
  Vec3D ret;
  return ret;
#endif
}

Quaternion ivp_get_sensor_rotation(SensorUnit *sensor) {
#if SENSOR_ENABLE == 1
  SensorData sensor_data;
  Quaternion sensor_rotation;

  sensor_data = sensor_get_data(sensor);

  return ivp_rot_convert_frame(sensor_rotation,
                               sensor->sensor_frame,
                               system_frame);
#else
  // Return empty
  Quaternion ret;
  return ret;
#endif
}

Vec3D ivp_get_imu_position(ImuUnit *sensor) {
#if IMU_ENABLE == 1
  ImuData imu_data = imu_get_measurement(sensor);

  return ivp_pos_convert_frame(imu_data.gps_position,
                               sensor->imu_frame,
                               system_frame);
#else
  // Return empty
  Vec3D ret;
  return ret;
#endif
}

Quaternion ivp_get_imu_heading(ImuData *sensor) {
#if IMU_ENABLE == 1
  ImuData sensor_data = imu_get_measurement(sensor);

  return vec2quat(ivp_pos_convert_frame(sensor_data.output_rotation,
                                        sensor->sensor_frame,
                                        system_frame));
#else
  // Return empty
  Quaternion ret;
  return ret;
#endif
}

ReferenceFrame ivp_get_system_frame() {
  return system_frame;
}

void ivp_set_system_frame(ReferenceFrame &ref) {
  system_frame = ref;
}
