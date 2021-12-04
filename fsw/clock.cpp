#include "clock.h"

void clock_increment_timer() {
  clock_timer_ticks++;
}

long clock_get_current_time() {
  return clock_timer_ticks;
}
