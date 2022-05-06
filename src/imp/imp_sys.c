#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "sys.h"
#include "print.h"
//#include "../../prep/prep.h"

long z__sys_getRamUsage(void)
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

void z__panic(char const *str_msg)
{
    z__fprint(stderr, "%s", str_msg);
}

void z__die(char const *str_msg, int code)
{
    z__fprint(stdout, "FORCE EXIT %s\n", str_msg);
    exit(code);
}
