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

#ifndef ZAKAROUF_Z_IMP__DYNT_H
#define ZAKAROUF_Z_IMP__DYNT_H

#include "std/primitives.h"

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


#define z__Dynt_getUnitSize(arr)            ((arr).unitsize)
#define z__Dynt_getRawData(arr)             ((arr).data)
#define z__Dynt_getComment(arr)             ((arr).comment)
#define z__Dynt_getLen(arr)                 ((arr).len)
#define z__Dynt_getUsed(arr)                ((arr).lenUsed)

#define z__Dynt_getAddress(arr, index)      (z__Dynt_getRawData(arr) + (index * z__Dynt_getUnitSize(arr)))
#define z__Dynt_getTop(arr, T)         ( *(T*)( z__Dynt_getRawData(arr) + ((z__Dynt_getUsed(arr) - 1) * z__Dynt_getUnitSize(arr))) )
#define z__Dynt_getVal(arr, index , T) ( *(T*)( z__Dynt_getRawData(arr) + (index * z__Dynt_getUnitSize(arr))) )


z__Dynt z__Dynt_new(z__size unitsize, z__u32 len, z__u8 typeID, const char *comment, z__i32 commentLength);
void z__Dynt_newFromRaw(z__Dynt *obj, void const *ptr, z__size unitsize, z__size len, z__u8 typeID, char const *comment, z__i32 commentLen);

void z__Dynt_delete(z__Dynt *arrt);
void z__Dynt_push( z__Dynt *arrt, void *val);
void z__Dynt_pop( z__Dynt *arrt);
void z__Dynt_resize(z__Dynt *arrt, z__u32 newsize);
z__Dynt z__Dynt_makeCopy(const z__Dynt arrt);
int z__Dynt_isdataequal(const z__Dynt *d1, const z__Dynt *d2);
int z__Dynt_isduplicate(const z__Dynt *d1, const z__Dynt *d2);


#define z__Dynt_newFromArr(arrt, arr, id, comment, commentLen)\
        z__Dynt_newFromRaw(             \
                arrt                    \
              , (arr).data              \
              , sizeof(*(arr).data)     \
              , (arr).lenUsed           \
              , id                      \
              , comment, commentLen);   \



#ifdef Z__IMPLEMENTATION

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "std/mem.h"
    
z__Dynt z__Dynt_new(z__size unitsize, z__u32 len, z__u8 typeID, const char *comment, z__i32 commentLength)
{
    z__Dynt arrt = {
        .data = z__MALLOC(unitsize * len),
        .unitsize = unitsize,
        .len = len,
        .lenUsed = 0,
        .typeID = typeID
    };

    if (commentLength == 0) {
        arrt.comment = NULL;
        arrt.commentLen = commentLength;
    } else if (commentLength == -1) {
        arrt.comment = z__MALLOC(sizeof(char) * strnlen(comment, 1024));
        snprintf(arrt.comment, 1024, "%s", comment);
        arrt.commentLen = 1024;
    } else {
        arrt.comment = z__MALLOC(sizeof(char) * commentLength);
        memcpy(arrt.comment, comment, commentLength);
        arrt.comment[commentLength-1] = 0;
        arrt.commentLen = commentLength;
    }

    return arrt;
}

void z__Dynt_newFromRaw(z__Dynt *obj, void const *ptr, z__size unitsize, z__size len, z__u8 typeID, char const *comment, z__i32 commentLen)
{
    *obj = z__Dynt_new(unitsize, len, typeID, comment, commentLen);
    memcpy(obj->data, ptr, unitsize * len);
}

void z__Dynt_push( z__Dynt *arrt, void *val)
{
    if (arrt->lenUsed >= arrt->len)
    {
        arrt->len += arrt->len * 2;
        arrt->data = z__REALLOC_SAFE(arrt->data,  arrt->unitsize * (arrt->len) );
    }
    
    void *tmpptr = ((z__byte*)(arrt->data)) + (arrt->lenUsed * arrt->unitsize);
    memcpy(tmpptr, val, arrt->unitsize);
    arrt->lenUsed += 1;
}

void z__Dynt_pop( z__Dynt *arrt)
{
    arrt->lenUsed -= 1;
    if ((arrt->len - arrt->lenUsed) >= 8)
    {
        arrt->len -= 8;
        arrt->data = z__REALLOC_SAFE(arrt->data,  arrt->unitsize * (arrt->len) );
    }
}

inline void z__Dynt_resize(z__Dynt *arrt, z__u32 newsize)
{
    arrt->len = newsize;
    if (arrt->lenUsed > arrt->len)
    {
        arrt->lenUsed = arrt->len;
    }

    arrt->data = z__REALLOC_SAFE(arrt->data, arrt->unitsize * (arrt->len));
}

z__Dynt z__Dynt_makeCopy(const z__Dynt arrt)
{
    z__Dynt arrtCopy = {
        .data = z__MALLOC(arrt.len * arrt.unitsize),
        .len = arrt.len,
        .lenUsed = arrt.lenUsed,
        .unitsize = arrt.unitsize,
        .commentLen = arrt.commentLen
    };

    z__u32 namelen = arrt.commentLen;
    if (namelen > 0)
    {
        arrtCopy.comment = z__MALLOC(sizeof(char) * namelen);
        memcpy(arrtCopy.comment, arrt.comment, namelen);
    } else {
        arrtCopy.comment = NULL;
    }

    return arrtCopy;

}

int z__Dynt_isdataequal(const z__Dynt *d1, const z__Dynt *d2)
{
    if(d1->unitsize * d1->lenUsed != d2->unitsize * d2->lenUsed) return 0;
    return !memcmp(d1->data, d2->data, d1->lenUsed * d1->unitsize);
}

int z__Dynt_isduplicate(const z__Dynt *d1, const z__Dynt *d2)
{
    if(d1->commentLen != d2->commentLen) return 0;
    if(strncmp(d1->comment, d2->comment, d1->commentLen) != 0) return 0;
    return z__Dynt_isdataequal(d1, d2);
}


void z__Dynt_delete(z__Dynt* arrt)
{
    z__FREE(arrt->data);
    arrt->len = 0;
    arrt->lenUsed = 0;
    arrt->unitsize = 0;

    if (arrt->commentLen > 0){
        z__FREE(arrt->comment);
    }
    arrt->commentLen = 0;
}
#endif // Z__IMPLEMENTATION

#endif
