#ifndef ZAKAROUF__ZTYPES_TYPES__DYNT_H
#define ZAKAROUF__ZTYPES_TYPES__DYNT_H

#include "base.h"

/* Unknown Similar size Unsafe type Arrays */
typedef struct __ZAKAROUF__SIMPARR_TYPE_STRUCT
{
    z__ptr data;
    char *comment;
    z__size size;
    z__u32 len;
    z__u32 lenUsed;
    z__u8  typeID;

}z__Dynt;


z__Dynt z__Dynt_new(z__size size, z__u32 len, const char *comment, z__i32 commentLength, z__u8 typeID);
z__Dynt z__Dynt_newFromFile(const char filepath[], z__size sizePerVal, const char *comment, z__i32 commentLength, z__u8 typeID);
void z__Dynt_delete(z__Dynt* arrt, z__bool nameFree);
void z__Dynt_push( z__Dynt *arrt, void *val);
void z__Dynt_pop( z__Dynt *arrt);
void z__Dynt_resize(z__Dynt *arrt, z__u32 newsize);
z__Dynt z__Dynt_makeCopy(const z__Dynt arrt);

#define z__Dynt_getValSize(arr)           (arr.size)
#define z__Dynt_getTop(arr, T)         ( *( T *)( (arr.data) + ((arr.lenUsed-1) * arr.size)) )
#define z__Dynt_getVal(arr, index , T) ( *( T *)( (arr.data) + (index * arr.size)) )
#define z__Dynt_getAddress(arr, index) ((arr.data) + (index * arr.size))
#define z__Dynt_getComment(arr)           (arr.comment)
#define z__Dynt_getLen(arr)               (arr.len)
#define z__Dynt_getUsed(arr)              (arr.lenUsed)


#endif
