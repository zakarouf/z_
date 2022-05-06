#include "print.h"
#include <stdarg.h>

int z__fprint(FILE *fp, const char *restrict fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);

    int val = vfprintf(fp, fmt, arg);

    va_end(arg);
    return val;
}

int z__print(const char * restrict fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);

    int val = vprintf(fmt, arg);

    va_end(arg);
    return val;
}
