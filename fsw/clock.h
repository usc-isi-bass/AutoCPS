#ifndef CLOCK_H
#define CLOCK_H

#include "datatypes.h"

void clock_increment_timer();

long clock_get_current_time();

void clock_get_current_time(long time);

double clock_timer_ticks_to_epoch();

#endif