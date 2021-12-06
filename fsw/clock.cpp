#include "clock.h"

#include "params.h"

long clock_timer_ticks;

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
  return CLOCK_TICKS_PER_SEC * clock_timer_ticks;
}
