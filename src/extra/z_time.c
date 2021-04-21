#include <sys/time.h>

#ifdef WIN32
    #include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
    #include <time.h>   // for nanosleep
#else
    #include <unistd.h> // for usleep
#endif


void z__time_msleep(int milliseconds)
{ // cross-platform sleep function
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
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
    struct tm *timeinfo;
    time(&tCurrentTime);
    timeinfo = localtime(&tCurrentTime);
    *h = timeinfo->tm_hour;
    *m = timeinfo->tm_min;
    *s = timeinfo->tm_sec;

    return 0;
}
