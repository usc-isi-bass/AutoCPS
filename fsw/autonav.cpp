#include "autonav.h"
#include "seq.h"

SeqWaypoint autonav_get_waypoint() {
#if AUTONAV_ENABLE == 1
  // Dummy calculation
  SeqWaypoint ret = seq_get_waypoint();
  ret.position.x += 0.01f;
  return ret;
#else
  return seq_get_waypoint();
#endif
}
