#include "clock.h"

#include "autocode.h"

void clock_increment_timer() {
  clock_timer_ticks++;
}

long clock_get_current_time() {
  return clock_timer_ticks;
}

void clock_get_current_time(long time) {
  clock_timer_ticks = time;
}

double clock_timer_ticks_to_epoch() {
  return autocode_clock_timer_ticks_to_epoch(clock_timer_ticks);
}
