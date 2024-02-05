#ifndef ZAKAROUF_Z_IMP__TIME_H
#define ZAKAROUF_Z_IMP__TIME_H

#include "std/primitives.h"
#include "string.h"

/**
 * Sleep for `n` milliseconds
 */
void z__time_msleep(int milliseconds);

/**
 * Get Local Time
 */
int z__time_getLocalTime(int * _Nonnull h, int * _Nonnull m, int * _Nonnull s);
void z__time_getLocalTime_str(z__String * _Nonnull str);

/**
 * Get time
 */
z__u64 z__time(void);
z__u64 z__time_process(void);
z__u64 z__time_tps(void);
z__f64 z__time_delta(z__u64 process_0, z__u64 process_1);
z__u64 z__time_mfps(z__u32 fps);

#endif
