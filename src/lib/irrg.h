#ifndef ZAKAROUF_Z_IMP__IRRG_IMPL_H
#define ZAKAROUF_Z_IMP__IRRG_IMPL_H

#include "std/primitives.h"

/* Unsafe Irregular Object Holder array */
typedef struct __ZAKAROUF__IRREGULAR_TYPE_STRUCT
{
    z__ptr *data;
    z__size *size;
    z__u8  *typeID;
    z__i32 len;
    z__i32 lenUsed;
    char** comment;

}z__Irrg;

#define z__Irrg_getValSize(arr, of)       (arr.size[of])
#define z__Irrg_gettypeID(arr, of)        (arr.typeID[of])
#define z__Irrg_getComment(arr, of)       (arr.comment[of])
#define z__Irrg_getVal(arr, of, T)        ( *( T *)(*arr.data[of]) )
#define z__Irrg_getValTop(arr, T)         ( *( T *)(*arr.data[arr.lenUsed-1]) )
#define z__Irrg_getAddress(arr, of)       (*arr.data[of])
#define z__Irrg_getLen(arr)               (arr.len)
#define z__Irrg_getUsed(arr)              (arr.lenUsed)


z__Irrg z__Irrg_new(z__u32 len);
void z__Irrg_resize(z__Irrg *irgt, z__size newsize);
void z__Irrg_push(z__Irrg *irgt, void *val, z__size size, z__u8 typeID, const char *comment, z__i32 commentLength);
void z__Irrg_pop(z__Irrg *irgt);
void z__Irrg_delete(z__Irrg *irgt);

#endif

