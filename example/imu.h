#ifndef IMU_H
#define IMU_H

// IMU module 

#include "datatypes.h"

// Final output of IMU
struct IMUOutput {
  Quarternion linear_accel;
  Quarternion angular_accel;
  Quarternion orientation;
};

// Recieve data from a sensor and
void data_recieve_sensor(void );

// Main loop of IMU unit, continuously runs when called by startup script
void imu_loop();

#endif /*IMU_H*/