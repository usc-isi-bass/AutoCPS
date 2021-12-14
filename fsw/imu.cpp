#include "imu.h"
#include "stub.h"

ImuData imu_get_measurement(ImuUnit *unit) {
  return stub_imu_get_measurement(unit);
}
