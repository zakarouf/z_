#include <stdlib.h>

long z__sys_getRamUsage(void)
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}
