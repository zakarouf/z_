#include "print.h"
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
