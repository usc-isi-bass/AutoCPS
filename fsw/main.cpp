#include <iostream>

#include "clock.h"
#include "datatypes.h"
#include "seq.h"
#include "servo_ctrl.h"
#include "stub.h"

using namespace std;

int main(int argc, char **argv) {
  // Get waypoints from an input file
  seq_create_waypoints("input.txt");

  // Execution loop
  while(true) {
    clock_increment_timer();

    PosOutputData curr_pos = pos_get_current_location();

    std::cout << "Time: " << clock_get_current_time() << std::endl;
    std::cout << "Location: {" << curr_pos.position.x << ", " <<
                 curr_pos.position.y << ", " << curr_pos.position.z << "}" <<
                 std::endl;
    std::cout << std::endl;

    servo_move(pos_get_next_location());
  }

  return 0;
}
