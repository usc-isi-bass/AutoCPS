#include "servo_ctrl.h"

#include "autocode.h"

void servo_move(PosOutputData input_waypoint) {
  servo_autocode_servo_move(input_waypoint);
}
