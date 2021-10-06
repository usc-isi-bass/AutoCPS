#ifndef FSW_STUB_H
#define FSW_STUB_H

#include "imu.h"

// Stubbed function to generate data for the IMU
IMUInputData imu_stub_data_recieve_sensors();

// Stubbed function to send data to the IMU
void imu_stub_data_send(IMUInputData input_data, std::shared_ptr<AXIStream> input_stream);

#endif /*FSW_STUB_H*/
