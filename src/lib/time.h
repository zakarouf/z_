/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZAKAROUF_Z_IMP__TIME_H
#define ZAKAROUF_Z_IMP__TIME_H

#include "std/primitives.h"
#include "string.h"

/**
 * Sleep for `n` milliseconds
 */
void z__time_msleep(int milliseconds);

/**
 * Get Local Time
 */
int z__time_getLocalTime(int *h, int *m, int *s);
void z__time_getLocalTime_str(z__String *str);

/**
 * Get time
 */
z__u64 z__time(void);
z__u64 z__time_process(void);
z__u64 z__time_tps(void);
z__f64 z__time_delta(z__u64 process_0, z__u64 process_1);
z__u64 z__time_mfps(z__u32 fps);


#ifdef Z__IMPLEMENTATION
#include <time.h>
#ifdef WIN32
    #include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
    #include <time.h>   // for nanosleep
#else
    #include <unistd.h> // for usleep
#endif

#include "string.h"

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

z__u64 z__time_mfps(z__u32 fps)
{
    z__float x = 1.0f/fps;
    return (z__u64)(x * 1000);
}

z__u64 z__time_tps(void)
{
    return CLOCKS_PER_SEC;
}

z__f64 z__time_delta(z__u64 process_0, z__u64 process_1)
{
    return (z__f64)(process_1 - process_0) / CLOCKS_PER_SEC;
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
#endif //Z__IMPLEMENTATION
#endif
