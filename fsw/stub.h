#ifndef STUB_H
#define STUB_H

#include "imu.h"

double stub_kalman_filter_equation_a();

ImuData stub_imu_get_measurement(ImuUnit unit);

#endif
