#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "sys.h"
//#include "../../prep/prep.h"

long z__sys_getRamUsage(void)
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

void z__logfile_basic(void * fileStream ,const char * restrict format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(fileStream, format, args);
    va_end(args);

    fflush(fileStream);

}

void z__panic(char const *str_msg)
{
    z__logfile_basic(stdout, "%s", str_msg);
}

void z__die(char const *str_msg, int code)
{
    z__logfile_basic(stdout, "FORCE EXIT %s\n", str_msg);
    exit(code);
}
