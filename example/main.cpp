#include <iostream>
#include <memory>

#include "imu.h"
#include "fsw_stub.h"

int main(int argc, char const *argv[])
{
  // Simulated AXI streams
  std::shared_ptr<AXIStream> imu_input_st(new AXIStream());
  std::shared_ptr<AXIStream> imu_to_actuator_st(new AXIStream());

  // TODO: Initialization
  
  // Main control loop
  while(true) {
    // Generate positioning data and send data to IMU
    imu_stub_data_send(imu_stub_data_recieve_sensors(), imu_input_st);
    // Run one iteration of IMU module
    imu_main_loop(imu_input_st, imu_to_actuator_st);
    // Query autopilot

    // Run one iteration of actuator module

    // Run one iteration of control dynamics module

    // Modify control surfaces accordingly

  }

  return 0;
}