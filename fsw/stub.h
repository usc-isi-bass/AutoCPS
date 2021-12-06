#ifndef STUB_H
#define STUB_H

#include "imu.h"
#include "sensor.h"

double stub_kalman_filter_equation_a();

ImuData stub_imu_get_measurement(ImuUnit &unit);

SensorData stub_sensor_get_measurement(SensorUnit &unit);

#endif
