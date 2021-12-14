#include "sensor.h"

#include "stub.h"

SensorData sensor_get_data(SensorUnit *sensor) {
  return stub_sensor_get_measurement(sensor);
}
