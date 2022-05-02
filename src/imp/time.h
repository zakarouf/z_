#ifndef ZAKAROUF_Z_IMP__TIME_H
#define ZAKAROUF_Z_IMP__TIME_H

/**
 * Sleep for `n` milliseconds
 */
void z__time_msleep(int milliseconds);

/**
 * Get Local Time
 */
int z__time_getLocalTime(int * _Nonnull h, int * _Nonnull m, int * _Nonnull s);


#endif
