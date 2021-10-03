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

// IMU internal datatype
struct IMUInternalData {

};

// Recieve a quarternion from AXI stream
Quarternion receive_axi_stream() {

}

// Recieve data from a sensor and feed it into the calculations
void data_recieve_sensor();

// Main loop of IMU unit, continuously runs when called by startup script
void imu_loop();

#endif /*IMU_H*/