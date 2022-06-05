#include "../types/arr.h"
#include "../types/dynt.h"
#include "../types/string.h"

#include "type.h"
#include "ansi.h"

#include "tgprint.h"

#include <stdarg.h>
#include <stdio.h>

#define COLOR_INT 4
#define COLOR_STRING 2
#define COLOR_FLOAT 3
#define COLOR_PTR 5
#define COLOR_DYNT 11

#define t(n) z__typeid_getminor_raw(z__type_id_lit(n))
static const char *fmt_int[] = {
  [t(u8)] = "%hhu ",
  [t(byte)] = "0x%02x ",
  [t(i16)] = "%hi ",
  [t(u16)] = "%hu ",
  [t(i32)] = "%i ",
  [t(u32)] = "%u ",
  [t(i64)] = "%lli ",
  [t(u64)] = "%llu ",
  [t(char)] = "%c ",
  [t(ptr)] = z__ansi_fmt((cl256_fg, COLOR_PTR)) "%p ",
};

static const z__size unit_sizes_int[] = {
  [t(u8)] = sizeof(z__u8),
  [t(byte)] = z__sizeof(z__byte),
  [t(i16)] = z__sizeof(z__i16),
  [t(u16)] = z__sizeof(z__u16),
  [t(i32)] = z__sizeof(z__i32),
  [t(u32)] = z__sizeof(z__u32),
  [t(i64)] = z__sizeof(z__i64),
  [t(u64)] = z__sizeof(z__u64),
  [t(char)] = z__sizeof(char),
  [t(ptr)] = z__sizeof(void *),
};  

static inline void _print_arr_int(FILE *fp, void *data, z__u32 length, z__u32 unit_size, char const *fmt)
{
    fputs("[ " z__ansi_fmt((cl256_fg, COLOR_INT)), fp);
    char *p = data;
    for (size_t i = 0; i < length; i++, p += unit_size) {
        fprintf(fp, fmt, *p);
    }
    fputs(z__ansi_fmt((plain))
        "] ", fp);
}

static inline void _print_arr_f32(FILE *fp, z__f32 *data, z__u32 length)
{
    fputs("[ " z__ansi_fmt((cl256_fg, COLOR_FLOAT)), fp);
    float *p = data;
    for (size_t i = 0; i < length; i++, p += 1) {
        fprintf(fp, "%f ", *p);
    }
    fputs(z__ansi_fmt((plain))
        "] ", fp);
}

int _z__tgfprint_raw(FILE *fp, z__u32 count, z__u16 tids[], z__size sizes[], ...)
{
    va_list arg;
    va_start(arg, sizes);

    z__typeid *tid = (void *)tids;
    for (size_t i = 0; i < count; i++, tid += 1) {
        switch (tid->major) {
          case _Z__PRIV__TYPE_M_ATOM_INT: {
            fputs(z__ansi_fmt((cl256_fg, COLOR_INT)), fp);
            fprintf(fp
              , fmt_int[z__typeid_getminor_raw(tid->raw)], va_arg(arg, z__i64)); 
            fputs(z__ansi_fmt((plain)), fp);
          } break;

          case _Z__PRIV__TYPE_M_ATOM_FLOAT: {
            fprintf(fp,
                    z__ansi_fmt((cl256_fg, COLOR_FLOAT))
                    "%f "
                    z__ansi_fmt((plain)), va_arg(arg, z__f64)); 
          } break;

          case _Z__PRIV__TYPE_M_PRIM_ARR: {
              _print_arr_int(fp
                , va_arg(arg, void*)
                , sizes[i]/unit_sizes_int[tid->minor]
                , unit_sizes_int[tid->minor], fmt_int[tid->minor]);
          } break;

          case _Z__PRIV__TYPE_M_PRIM_ARR_FLOAT: {
              _print_arr_f32(fp
                  , va_arg(arg, void *)
                  , sizes[i]/sizeof(z__f32));
          } break;
          
          case _Z__PRIV__TYPE_M_ARR: {
              z__voidArr arr = va_arg(arg, z__voidArr);
              _print_arr_int(fp
                  , arr.data
                  , arr.lenUsed
                  , unit_sizes_int[tid->minor], fmt_int[tid->minor]);
          } break;

          case _Z__PRIV__TYPE_M_ARR_FLOAT: {
              z__voidArr arr = va_arg(arg, z__voidArr);
              _print_arr_f32(fp
                  , arr.data
                  , arr.lenUsed);
          } break;
          
          case _Z__PRIV__TYPE_M_OBJ: {
              switch (tid->minor) {
                  case 1: /* Dynt */ {
                      z__Dynt d = va_arg(arg, z__Dynt);
                      fprintf(fp, 
                          z__ansi_fmt((cl256_fg, COLOR_DYNT))
                          "(%s){p = %p [%u/%u]*%zu T %u} "
                          z__ansi_fmt((plain))
                          , d.comment
                          , d.data
                          , d.lenUsed, d.len
                          , d.unitsize, d.typeID);
                  } break;

                  case 2: /* C String */ {
                      fprintf(fp,
                          z__ansi_fmt((cl256_fg, COLOR_STRING))
                          "%s "
                          z__ansi_fmt((plain)), va_arg(arg, char *));
                  } break;

                  case 3: /* String */ {
                      fprintf(fp,
                          z__ansi_fmt((cl256_fg, COLOR_STRING))
                          "%s "
                          z__ansi_fmt((plain)), va_arg(arg, z__String).data);

                  } break;

                  case 4: /* String List */ {
                      z__StringList sl = va_arg(arg, z__StringList);
                      for (size_t i = 0; i < sl.lenUsed; i++) {
                          fprintf(fp,
                              z__ansi_fmt((cl256_fg, COLOR_STRING))
                              "%s "
                              z__ansi_fmt((plain)), sl.data[i]);
                      }
                  } break;
                  default: goto _L_return_FAIL;
              } break;
          }

          default:  goto _L_return_FAIL; 
        }
        fputs(z__ansi_fmt((plain)), fp);
    }

    fputs("\n", fp);
    va_end(arg);
    return 1;

    _L_return_FAIL:
    fputs(z__ansi_fmt((cl256_fg, 1))
            "Unknown"
          z__ansi_fmt((plain)) "\n", fp);
    va_end(arg);
    return 0;
}

