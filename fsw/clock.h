#ifndef CLOCK_H
#define CLOCK_H

#include "datatypes.h"

long clock_timer_ticks;

void clock_increment_timer();

long clock_get_current_time();

#endif