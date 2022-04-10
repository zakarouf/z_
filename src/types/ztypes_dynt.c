#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "base.h"
#include "dynt.h"
#include "mem.h"

    
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
        arrt->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
        arrt->data = z__REALLOC_SAFE(arrt->data,  arrt->unitsize * (arrt->len) );
    }
    
    void *tmpptr = (arrt->data) + (arrt->lenUsed * arrt->unitsize);
    memcpy(tmpptr, val, arrt->unitsize);
    arrt->lenUsed += 1;
}

void z__Dynt_pop( z__Dynt *arrt)
{
    arrt->lenUsed -= 1;
    if ((arrt->len - arrt->lenUsed) >= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
    {
        arrt->len -= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
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


inline void z__Dynt_delete(z__Dynt* arrt)
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
