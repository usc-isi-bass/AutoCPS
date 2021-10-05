#include <iostream>
#include <memory>
#include <thread>

#include "imu.h"

int main(int argc, char const *argv[])
{
  std::shared_ptr<AXIStream> imu_input_st(new AXIStream());
  std::shared_ptr<AXIStream> imu_to_actuator_st(new AXIStream());

  // Start IMU module
  std::thread imu_loop(imu_main_loop,
                       std::ref(imu_input_st),
                       std::ref(imu_to_actuator_st));

  // Should never return until stopped
  imu_loop.join();

  return 0;
}