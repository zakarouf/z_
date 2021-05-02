#ifndef ZAKAROUF_Z__EXTRA_H
#define ZAKAROUF_Z__EXTRA_H

#include "../types/ztypes.h"

/* File */
z__i8Arr z__file__readFile(char const filename[]);
z__Dynt z__file__Dynt_readFile(char const filename[], z__size const subDiv, char const *comment, z__i32 const commentLen);
z__StringLines z__file_getfnames(char const path[]);

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
void z__log_basic(void * fileStream ,const char *format, ...);

#endif
