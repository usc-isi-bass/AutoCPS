#include "imu.h"

AXIStream *input_st, *output_st;

inline void imu_loop_recv() {
  
}

// Main loop of IMU unit, continuously runs when called by startup script
void imu_loop(AXIStream *input, AXIStream *output) {
  input_st = input;
  output_st = output;

  // Run loop forever
  while (true) {
    // Recieve data from the IMU
    imu_loop_recv();
    // Calculate 

  }
}
