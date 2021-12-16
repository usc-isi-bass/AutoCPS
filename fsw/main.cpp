#include <iostream>

#include "clock.h"
#include "datatypes.h"
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

  // Execution loop
  while(true) {
    clock_increment_timer();

    PosOutputData curr_pos = pos_get_current_location();

    cout << "Time: " << clock_get_current_time() << endl;
    cout << "Location: {" << curr_pos.position.x << ", " <<
                 curr_pos.position.y << ", " << curr_pos.position.z << "}" <<
                 endl;
    cout << endl;

    servo_move(pos_get_next_location());
  }

  return 0;
}
