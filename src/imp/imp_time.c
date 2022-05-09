#include <sys/time.h>

#ifdef WIN32
    #include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
    #include <time.h>   // for nanosleep
#else
    #include <unistd.h> // for usleep
#endif

#include "time.h"

#include "../types/string.h"

void z__time_msleep(int milliseconds)
{ // cross-platform sleep function
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts = {0};
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        if (milliseconds >= 1000) { 
          sleep(milliseconds / 1000);
        }
        usleep((milliseconds % 1000) * 1000);
    #endif
}

int z__time_getLocalTime(int *h, int *m, int *s)
{
    time_t tCurrentTime;
    struct tm timeinfo;
    time(&tCurrentTime);
    localtime_r(&tCurrentTime, &timeinfo);
    *h = timeinfo.tm_hour;
    *m = timeinfo.tm_min;
    *s = timeinfo.tm_sec;

    return 0;
}

z__u64 z__time(void)
{
    return time(NULL);
}

z__u64 z__time_process(void)
{
    return clock();
}

z__u64 z__time_tps(void)
{
    return CLOCKS_PER_SEC;
}

void z__time_getLocalTime_str(z__String *str)
{
    if(str->len == 0) z__String_new(28);
    if(str->len < 27) z__String_expand(str, 27);
    time_t tCurrentTime;
    time(&tCurrentTime);
    ctime_r(&tCurrentTime, str->data);
    str->data[24] = ' ';
}
