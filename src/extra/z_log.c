#include <stdarg.h>
#include <stdio.h>
#include "zextra.h"

void z__log_basic(void * fileStream ,const char * restrict format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(fileStream, format, args);
    va_end(args);

    fflush(fileStream);

}
