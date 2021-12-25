#ifndef ZAKAROUF__ZTYPES_TYPES__DYNT_H
#define ZAKAROUF__ZTYPES_TYPES__DYNT_H

#include "base.h"

/* Unknown Similar size Unsafe type Arrays */
typedef struct z__Dynt
{
    z__ptr data;
    char *comment;
    z__u32 commentLen;
    z__size unitsize;
    z__u32 len, lenUsed;
    z__u8 typeID;

}z__Dynt;


z__Dynt z__Dynt_new(z__size unitsize, z__u32 len, z__u8 typeID, const char *comment, z__i32 commentLength);
void z__Dynt_newFromRaw(z__Dynt *obj, void const *ptr, z__size unitsize, z__size len, z__u8 typeID, char const *comment, z__i32 commentLen);
z__Dynt z__Dynt_newFromFile(const char filepath[], z__size unitsize, z__u8 typeID, const char *comment, z__i32 commentLength);

void z__Dynt_delete(z__Dynt *arrt);
void z__Dynt_push( z__Dynt *arrt, void *val);
void z__Dynt_pop( z__Dynt *arrt);
void z__Dynt_resize(z__Dynt *arrt, z__u32 newsize);
z__Dynt z__Dynt_makeCopy(const z__Dynt arrt);

#define z__Dynt_newFromArr(arrt, arr, id, comment, commentLen)\
        z__Dynt_newFromRaw(             \
                arrt                    \
              , (arr).data              \
              , sizeof(*(arr).data)     \
              , (arr).lenUsed           \
              , id                      \
              , comment, commentLen);   \


#define z__Dynt_getUnitSize(arr)            ((arr).unitsize)
#define z__Dynt_getRawData(arr)             ((arr).data)
#define z__Dynt_getComment(arr)             ((arr).comment)
#define z__Dynt_getLen(arr)                 ((arr).len)
#define z__Dynt_getUsed(arr)                ((arr).lenUsed)

#define z__Dynt_getAddress(arr, index)      (z__Dynt_getRawData(arr) + (index * z__Dynt_getUnitSize(arr)))
#define z__Dynt_getTop(arr, T)         ( *(T*)( z__Dynt_getRawData(arr) + ((z__Dynt_getUsed(arr) - 1) * z__Dynt_getUnitSize(arr))) )
#define z__Dynt_getVal(arr, index , T) ( *(T*)( z__Dynt_getRawData(arr) + (index * z__Dynt_getUnitSize(arr))) )


#endif
