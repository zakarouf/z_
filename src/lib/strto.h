#ifndef ZAKAROUF_Z_IMP__STRTO_H
#define ZAKAROUF_Z_IMP__STRTO_H

#include "typegen.h"

#define z__PRIV__strto_scan_typegen(v)\
        z__typegen_def(*(v), "",\
                , (z__i16, "%" PRIi16)    \
                , (z__u16, "%" PRIu16)    \
                , (z__i32, "%" PRIi32)     \
                , (z__u32, "%" PRIu32)     \
                , (z__i64, "%" PRIi64)   \
                , (z__u64, "%" PRIu64)   \
                \
                , (z__f32, "%f")    \
                , (z__f64, "%lF")   \
                \
                , (char, "%c")   \
                , (char *, "%s")   \
              )

#define z__strto(str, v)\
    sscanf(str, z__PRIV__strto_scan_typegen(v), v)


#define z__String_to(str, v)\
    {\
        if(str.len)\
            z__strto(str.data, v);\
    }


#endif

