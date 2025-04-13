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

/**
 * Print message & Exit.
 */
int z__exit(int code, char const *fmt, ...);

#ifdef Z__IMPLEMENTATION
#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#include "print.h"

#if defined(_WIN32) || defined (_WIN64) || defined (WINDOWS) || defined (_MSC_VER)
    #include <windows.h>
    #include <direct.h>
    #define getcwd _getcwd
#else 
    #include <unistd.h>
#endif

long z__sys_getRamUsage(void)
{

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    return usage.ru_maxrss;
}


void z__panic(int code, char const *str_msg_fmt, ...)
{
    va_list arg;
    va_start(arg, str_msg_fmt);
    z__fprint_cl256f(stderr, 1, "panic: ");
    vfprintf(stderr, str_msg_fmt, arg);
    va_end(arg);
    exit(code);
}


int z__exit(int code, char const *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    vfprintf(stderr, fmt, arg);
    va_end(arg);
    exit(code);
}
#endif //Z__IMPLEMENTATION

#endif
