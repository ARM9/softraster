#include "precompiled.h"
#include "profile.h"

long time_delta(struct timespec *p_ts, struct timespec *p_te) {
  long delta = p_te->tv_nsec - p_ts->tv_nsec;
  delta += (p_te->tv_sec - p_ts->tv_sec) * 1000000000l;
  return delta;
}
