#include "autonav.h"
#include "seq.h"

SeqWaypoint autonav_get_waypoint() {
  return seq_get_waypoint();
}
