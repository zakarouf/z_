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

#ifndef ZAKAROUF_Z_IMP__PRINT_H
#define ZAKAROUF_Z_IMP__PRINT_H

#include <stdio.h>
#include "ansifmt.h"
#include "string.h"
#include "prep/nm/string.h"

/**
 * Basic Print Function (Basically fprintf)
 * _vb: with __FILE__ __LINE__ __func__ detail
 * _cl256: Custom Foreground Color
 * _cl256_full: Custom Color
 * _clrgb: 24bit Color, Foreground only
 * _clrgb_full: 24bit Color
 */
int z__fprint(FILE *fp, const char * __restrict fmt, ...)
    __attribute__((format (printf, 2, 3)));

int z__print(const char * __restrict fmt, ...)
    __attribute__((format (printf, 1, 2)));

int z__print_String(z__String const str);

int z__fprint_str(FILE *fp, char const *str, z__size size);
int z__print_str(char const *str, z__size size);
int z__print_char(z__u32 ch);

/* impl */
#define z__fprint_cl256(fp, bg, fg, fmt, ...)\
    z__fprint(fp, z__ansi_fmt((cl256, %d, %d)) fmt z__ansi_fmt((plain)), bg, fg, ##__VA_ARGS__)

#define z__fprint_cl256f(fp, fg, fmt, ...)\
    z__fprint(fp, z__ansi_fmt((cl256_fg, %d)) fmt z__ansi_fmt((plain)), fg, ##__VA_ARGS__)

#define z__fprint_clrgb(fp, b_r, b_g, b_b, f_r, f_g, f_b, fmt, ...)\
    z__fprint(fp,\
        z__ansi_fmt((clrgb, b_r, b_g, b_b, f_r, f_g, f_b))\
            fmt\
        z__ansi_fmt((plain)), ##__VA_ARGS__ )

#define z__fprint_clrgbf(fp, f_r, f_g, f_b, fmt, ...)\
    z__fprint(fp,\
        z__ansi_fmt((clrgb_fg, f_r, f_g, f_b))\
            fmt\
        z__ansi_fmt((plain)), ##__VA_ARGS__ )


#define z__fprint_vb(fp, fmt, ...)\
    z__fprint(fp\
        , __FILE__ ":" zpp__to_string(__LINE__) " @ %s(): " fmt\
        , __func__, ##__VA_ARGS__ )

#define z__fprint_vb_cl256(fp, bg, fg, fmt, ...)\
    z__fprint_cl256(fp, bg, fg\
        , __FILE__ ":" zpp__to_string(__LINE__) " @ %s(): " fmt\
        , __func__, ##__VA_ARGS__ )

#define z__fprint_vb_cl256f(fp, fg, fmt, ...)\
    z__fprint_cl256f(fp, fg\
        , __FILE__ ":" zpp__to_string(__LINE__) " @ %s(): " fmt\
        , __func__, ##__VA_ARGS__ )


#define z__fprint_vb_clrgb(fp,  b_r, b_g, b_b, f_r, f_g, f_b, fmt, ...)\
    z__fprint_clrgb(fp,  b_r, b_g, b_b, f_r, f_g, f_b\
        , __FILE__ ":" zpp__to_string(__LINE__) " @ %s(): " fmt\
        , __func__, ##__VA_ARGS__ )

#define z__fprint_vb_clrgbf(fp, f_r, f_g, f_b, fmt, ...)\
    z__fprint_clrgbf(fp, f_r, f_g, f_b\
        , __FILE__ ":" zpp__to_string(__LINE__) " @ %s(): " fmt\
        , __func__, ##__VA_ARGS__ )


#ifdef Z__IMPLEMENTATION
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>

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

int z__print_String(z__String const str)
{
    return fwrite(str.data, str.lenUsed, 1, stdout);
}

int z__print_str(char const *str, z__size size)
{
    return fwrite(str, 1, size, stdout);
}

int z__fprint_str(FILE *fp, char const *str, z__size size)
{
    return fwrite(str, 1, size, fp);
}

int z__print_char(z__u32 ch)
{
    return fputc(ch, stdout);
}
#endif //Z__IMPLEMENTATION

#endif // ZAKAROUF_Z_IMP__PRINT_H

