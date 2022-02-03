#include <iostream>

#include "att_ctrl.h"
#include "clock.h"
#include "datatypes.h"
#include "kalman.h"
#include "seq.h"
#include "servo_ctrl.h"
#include "stub.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: fsw <input file>" << endl;
    return -1;
  }

  // Get waypoints from an input file
  seq_create_waypoints(argv[1]);

  // Initialize stuff as needed
  kalman_init();

  // Execution loop
  while(true) {
    clock_increment_timer();

    PosOutputData curr_pos = pos_get_current_location();

    cout << "Time: " << clock_get_current_time() << endl;
    cout << "Location: {" << curr_pos.position.x << ", " <<
                 curr_pos.position.y << ", " << curr_pos.position.z << "}" <<
                 endl;

    PosOutputData next_pos = pos_get_next_location();

    cout << "Heading: {" << att_calculate_roll(next_pos) << ", " << att_calculate_pitch(next_pos)
         << ", " << att_calculate_yaw(next_pos) << "}" << endl;
    cout << "Throttle: " << att_calculate_throttle(next_pos) << endl;

    servo_move(next_pos);

    cout << endl;
  }

  return 0;
}
