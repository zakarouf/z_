#ifndef ZAKAROUF_Z_IMP__PRINT_H
#define ZAKAROUF_Z_IMP__PRINT_H

#include <stdarg.h>
#include <stdio.h>

#include "../types.h"

#define Z___IMP__PRINT_DEFAULT_SEPERATOR " "
#define Z___IMP__PRINT_CONFIG_COLOR_ENABLE

#if defined (Z___IMP__PRINT_CONFIG_COLOR_ENABLE)

#define Z___IMP__PRINT_COLOR_INT  "\x1b[38;5;4m"

#define Z___IMP__PRINT_COLOR_STRING "\x1b[38;5;2m"

#define Z___IMP__PRINT_COLOR_FLOAT "\x1b[38;5;3m"

#define Z___IMP__PRINT_COLOR_VEC "\x1b[38;5;7m" 

#define Z___IMP__PRINT_COLOR_POINTER "\x1b[38;5;5m"

#define Z___IMP__PRINT_COLOR_OBJECT "\x1b[38;5;6m"

#define Z___IMP__PRINT_COLOR_SPECIAL "\x1b[38;5;1m"

#define Z___IMP__PRINT_COLOR__RESET "\x1b[0m"

#else

#define Z___IMP__PRINT_COLOR_INT      

#define Z___IMP__PRINT_COLOR_STRING

#define Z___IMP__PRINT_COLOR_FLOAT

#define Z___IMP__PRINT_COLOR_VEC

#define Z___IMP__PRINT_COLOR_POINTER

#define Z___IMP__PRINT_COLOR_OBJECT

#define Z___IMP__PRINT_COLOR_SPECIAL

#define Z___IMP__PRINT_COLOR__RESET

#endif


void z__imp_print__PRIV__print_func__i8_ptr(FILE *fp , z__i8 *ptr, z__u32 len)
{

    fputs(Z___IMP__PRINT_COLOR_INT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%hhi ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__i16_ptr(FILE *fp , z__i16 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_INT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%hi ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__i32_ptr(FILE *fp , z__i32 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_INT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%i ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__i64_ptr(FILE *fp , z__i64 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_INT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%lli ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__u8_ptr(FILE *fp , z__u8 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_INT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%hhu ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__u16_ptr(FILE *fp , z__u16 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_INT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%hu ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__u32_ptr(FILE *fp , z__u32 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_INT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%u ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__u64_ptr(FILE *fp , z__u64 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_INT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%lld ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__f32_ptr(FILE *fp , z__f32 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_FLOAT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%f ", *ptr);
        ptr++;
    }
}

void z__imp_print__PRIV__print_func__f64_ptr(FILE *fp , z__f64 *ptr, z__u32 len)
{
    fputs(Z___IMP__PRINT_COLOR_FLOAT, fp);
    for (int i = 0; i < len; ++i)
    {
        fprintf(fp, "%f ", *ptr);
        ptr++;
    }
}

z__fnptr(const z__imp_print__PRIV_print_func_arr[10], void) = { 
    z__imp_print__PRIV__print_func__i8_ptr, z__imp_print__PRIV__print_func__u8_ptr,
    z__imp_print__PRIV__print_func__i16_ptr, z__imp_print__PRIV__print_func__u16_ptr,
    z__imp_print__PRIV__print_func__i32_ptr, z__imp_print__PRIV__print_func__u32_ptr,
    z__imp_print__PRIV__print_func__i64_ptr, z__imp_print__PRIV__print_func__u64_ptr,

    z__imp_print__PRIV__print_func__f32_ptr, z__imp_print__PRIV__print_func__f64_ptr
};

#define z__fprint_Dynt(fp, dy)\
    {\
        fprintf(fp, Z___IMP__PRINT_COLOR_OBJECT "<Dynt>("Z___IMP__PRINT_COLOR_STRING"#%s"Z___IMP__PRINT_COLOR_OBJECT"){"\
                Z___IMP__PRINT_COLOR__RESET  "ID:"      Z___IMP__PRINT_COLOR_INT "%hhu"\
                Z___IMP__PRINT_COLOR__RESET " size:"    Z___IMP__PRINT_COLOR_INT "%lu"\
                Z___IMP__PRINT_COLOR__RESET " len:"     Z___IMP__PRINT_COLOR_INT "%u|%u"\
                Z___IMP__PRINT_COLOR__RESET " *p:"      Z___IMP__PRINT_COLOR_POINTER"%p"\
             Z___IMP__PRINT_COLOR_OBJECT "}",\
            dy.comment ,dy.typeID, dy.size, dy.lenUsed, dy.len, dy.data);\
    }

void z__imp_print__PRIV__print_func(FILE *fp, z__u32 count, char types_data[], ...)
{
    va_list args;
    va_start(args, types_data);

    for (int i = 0; i < count; ++i) {
        char type = types_data[i];
        if (type > 0
            && type < 7){
            fprintf(fp, Z___IMP__PRINT_COLOR_INT "%lld", va_arg(args, z__i64));
        } else if (type > 6
                    && type < 9) {
            fprintf(fp, Z___IMP__PRINT_COLOR_FLOAT "%f", va_arg(args, z__f64));
        } else if (type > 8
                    && type < 19) {

            z__voidArr tmparr = va_arg(args, z__voidArr);
            fputs("[ ", fp);
            z__imp_print__PRIV_print_func_arr[type-9](fp, tmparr.data, tmparr.lenUsed);
            fputs( Z___IMP__PRINT_COLOR__RESET "]", fp);

        } else if (type == 20) {
            fprintf(fp, Z___IMP__PRINT_COLOR_STRING "%s", va_arg(args, z__String).data);
        } else if (type == 25) {
            fprintf(fp, Z___IMP__PRINT_COLOR_STRING "%s", va_arg(args, char*));

        } else if (type == 31 ) {
            z__Vector2 t = va_arg(args, z__Vector2);
            fprintf(fp, "(" Z___IMP__PRINT_COLOR_FLOAT "%f, %f" Z___IMP__PRINT_COLOR__RESET")", t.x, t.y);

        } else if (type == 32 ) {
            z__Vector3 t = va_arg(args, z__Vector3);
            fprintf(fp, "("Z___IMP__PRINT_COLOR_FLOAT"%f, %f, %f"Z___IMP__PRINT_COLOR__RESET")", t.x, t.y, t.z);

        } else if (type == 33 ) {
            z__Vector4 t = va_arg(args, z__Vector4);
            fprintf(fp, "("Z___IMP__PRINT_COLOR_FLOAT"%f, %f, %f, %f"Z___IMP__PRINT_COLOR__RESET")", t.x, t.y, t.z, t.w);

        } else if (type == 34 ) {
            z__Vint2 t = va_arg(args, z__Vint2);
            fprintf(fp, "(" Z___IMP__PRINT_COLOR_INT " %i, %i " Z___IMP__PRINT_COLOR__RESET ")", t.x, t.y);

        } else if (type == 35 ) {
            z__Vint3 t = va_arg(args, z__Vint3);
            fprintf(fp, "(" Z___IMP__PRINT_COLOR_INT "%i, %i, %i" Z___IMP__PRINT_COLOR__RESET ")", t.x, t.y, t.z);

        } else if (type == 36 ) {
            z__Vint4 t = va_arg(args, z__Vint4);
            fprintf(fp, "(" Z___IMP__PRINT_COLOR_INT "%i, %i, %i, %i" Z___IMP__PRINT_COLOR__RESET ")", t.x, t.y, t.z, t.w);
        } 

        else if (type == 23) {
            fprintf(fp, Z___IMP__PRINT_COLOR_POINTER "%p", va_arg(args, z__ptr));
        } else if (type == 24) {
            z__Dynt tmpd = va_arg(args, z__Dynt);
            z__fprint_Dynt(fp, tmpd);
        }
        else {
            fputs(Z___IMP__PRINT_COLOR_SPECIAL "<Unknown>", fp);
        }

        fputs(Z___IMP__PRINT_COLOR__RESET Z___IMP__PRINT_DEFAULT_SEPERATOR "", fp);
    }
    va_end(args);
}


#define z__imp_print__PRIV__ptr_eval_type(t)\
    {\
        *z__imp_print__PRIV__ptr_eval_type__var__ptr = z__typeID(t);\
        ++z__imp_print__PRIV__ptr_eval_type__var__ptr;\
    };

#define z__imp_print__PRIV__wrappt(...) zpp__map(z__imp_print__PRIV__ptr_eval_type, __VA_ARGS__)

#define z__imp_print__PRIV__gen_print(fp, ...)\
    {                                                                       \
        char *ptr = malloc(sizeof(zpp__Args_Count(__VA_ARGS__)));           \
        char *z__imp_print__PRIV__ptr_eval_type__var__ptr = ptr;            \
        z__imp_print__PRIV__wrappt(__VA_ARGS__)                             \
                                                                            \
        z__imp_print__PRIV__print_func(                                     \
            fp, zpp__Args_Count(__VA_ARGS__), ptr, __VA_ARGS__);            \
        z__FREE(ptr);                                                       \
    }

#define z__print(...) z__imp_print__PRIV__gen_print(stdout, __VA_ARGS__)
#define z__fprint(fp, ...) z__imp_print__PRIV__gen_print(fp, __VA_ARGS__)

#endif