#include <iostream>

#include "datatypes.h"
#include "seq.h"
#include "stub.h"

using namespace std;

int main(int argc, char **argv) {
  // Get waypoints from an input file
  seq_create_waypoints("input.txt");

  return 0;
}
