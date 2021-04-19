#ifndef ZAKAROUF_Z__H
#define ZAKAROUF_Z__H

#include "types/ztypes.h"

/* File */
z__i8Arr z__file__readFile(char filename[]);
z__Dynt z__file__Dynt_readFile(const char filename[],const z__size subDiv,const char *comment, const z__i32 commentLen);
z__StringLines z__file_getfnames(char path[]);

/* System */
long z__sys_getRamUsage(void);

/* Time */
void z__time_msleep(int milliseconds);
int z__time_getLocalTime(int *h, int *m, int *s);

/* Misc */
Z__INLINE int z__sswitch(int i)
{
    return i* -1;
}

/* Log */
void z__log_basic(void * fileStream ,const char * restrict format, ...);

#endif
