#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "typed.h"

static void *safe_realloc(void * data, size_t size)
{
    void *tmpdata = realloc(data, size);
    if (tmpdata != NULL)
    {
        if (tmpdata != data)
        {
            return tmpdata;
        }
    }
    return data;
}


z__ptrArr z__ptrArr_create(size_t size, z__u32 len, const char *name, size_t nameLength)
{
    z__ptrArr arrt;

    arrt.data = malloc(size * len);
    arrt.size = size;
    arrt.len = len;
    arrt.lenUsed = 0;

    if (nameLength == 0)
    {
        arrt.comment = NULL;
    }
    else
    {
        arrt.comment = malloc(sizeof(char) * nameLength);
        memcpy(arrt.comment, name, nameLength);
    }

    return arrt;
}
void z__ptrArr_push( z__ptrArr *arrt, void *val)
{
    if (arrt->lenUsed >= arrt->len)
    {
        arrt->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
        arrt->data = safe_realloc(arrt->data,  arrt->size * (arrt->len) );
    }
    
    void *tmpptr = (arrt->data) + (arrt->lenUsed * arrt->size);
    memcpy(tmpptr, val, arrt->size);
    arrt->lenUsed += 1;
}
void z__ptrArr_pop( z__ptrArr *arrt)
{
    arrt->lenUsed -= 1;
    if ((arrt->len - arrt->lenUsed) >= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
    {
        arrt->len -= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
        arrt->data = safe_realloc(arrt->data,  arrt->size * (arrt->len) );
    }
}
void z__ptrArr_resize(z__ptrArr *arrt, z__u32 newsize)
{
    arrt->len = newsize;
    if (arrt->lenUsed > arrt->len)
    {
        arrt->lenUsed = arrt->len;
    }

    arrt->data = safe_realloc(arrt->data, arrt->size * (arrt->len));
}
z__ptrArr z__ptrArr_makeCopy(const z__ptrArr arrt)
{
    z__ptrArr arrtCopy = {
        .data = malloc(arrt.len * arrt.size),
        .len = arrt.len,
        .lenUsed = arrt.lenUsed,
        .size = arrt.size
    };

    z__u32 namelen = strlen(arrt.comment);
    if (namelen > 0)
    {
        arrtCopy.comment = malloc(sizeof(char) * namelen);
        memcpy(arrtCopy.comment, arrt.comment, namelen);
    } else {
        arrtCopy.comment = NULL;
    }

    return arrtCopy;

}
void z__ptrArr_delete(z__ptrArr* arrt, z__bool nameFree)
{
    free(arrt->data);
    arrt->len = 0;
    arrt->lenUsed = 0;
    arrt->size = 0;

    if (nameFree)
    {
        if (arrt->comment != NULL)
        {
            free(arrt->comment);
        }
    }
}







z__Dynt z__Dynt_CreateNew(z__CreateDyntInfo info)
{
    return (z__Dynt){0};
}

