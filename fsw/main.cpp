#include <iostream>

#include "datatypes.h"
#include "pos_ctrl.h"
#include "stub.h"

using namespace std;

int main(int argc, char **argv) {
  create_waypoints("input.txt");
  cout << get_waypoint().z << endl;

  return 0;
}
