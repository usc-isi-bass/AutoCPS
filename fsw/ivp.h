#ifndef IVP_H
#define IVP_H

#include "datatypes.h"
#include "imu.h"
#include "sensor.h"

// 3D transformation matrix
struct TransformationMatrix {
  double t11, t12, t13, t21, t22, t23, t31, t32, t33;
};

// Transform a coordinate in one reference frame into another
Vec3D ivp_pos_convert_frame(Vec3D coordinate,
                            ReferenceFrame &sensor_frame,
                            ReferenceFrame &system_frame);

// Transform a rotation in one reference frame into another
Quaternion ivp_rot_convert_frame(Quaternion coordinate,
                                 ReferenceFrame &sensor_frame,
                                 ReferenceFrame &system_frame);

TransformationMatrix ivp_build_transform_matrix(ReferenceFrame &frame_1,
                                                ReferenceFrame &frame_2);

Vec3D ivp_get_sensor_position(SensorUnit *sensor);
Quaternion ivp_get_sensor_rotation(SensorUnit *sensor);

Vec3D ivp_get_imu_position(ImuUnit *sensor);
Quaternion ivp_get_imu_heading(ImuUnit *sensor);

ReferenceFrame ivp_get_system_frame();
void ivp_set_system_frame(ReferenceFrame &ref);

#endif
