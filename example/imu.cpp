#include "imu.h"

std::shared_ptr<AXIStream> input_st, output_st;

// Recieve a quarternion from AXI stream
Quarternion imu_receive_axi_stream() {
  input_st->get();
}

// Recieve data from the IMU 
inline void imu_loop_recv() {
  
}

// Main loop of IMU unit, continuously runs when called by startup script
void imu_main_loop(std::shared_ptr<AXIStream> input, std::shared_ptr<AXIStream> output) {
  input_st = input;
  output_st = output;

  // Run loop forever
  while (true) {
    // Recieve data from the IMU
    imu_loop_recv();
    // Calculate 
    
  }
}
