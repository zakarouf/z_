#ifndef ZAKAROUF_Z_IMP__SYS_H
#define ZAKAROUF_Z_IMP__SYS_H

#include "string.h"

/**
 * Get Ram Usage by the current program (in bytes)
 */
long z__sys_getRamUsage(void);

/**
 * Panic And Exit
 */
void z__panic(int code, char const *str_msg_fmt, ...);

/**
 * Get current working directory
 */
z__String z__sys_getcwd(void);

/**
 * Get current working Folder
 */
z__String z__sys_getcwf(void);

#endif
