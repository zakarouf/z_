#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "base.h"
#include "dynt.h"
#include "mem.h"

    
z__Dynt z__Dynt_new(z__size size, z__u32 len, const char *comment, z__i32 commentLength, z__u8 typeID)
{
    z__Dynt arrt;

    arrt.data = malloc(size * len);
    arrt.size = size;
    arrt.len = len;
    arrt.lenUsed = 0;
    arrt.typeID = typeID;

    if (commentLength == 0) {
        arrt.comment = NULL;
    } else if (commentLength == -1) {
        arrt.comment = malloc(sizeof(char) * strnlen(comment, 1024));
        snprintf(arrt.comment, 1024, "%s", comment);
    } else {
        arrt.comment = malloc(sizeof(char) * commentLength);
        memcpy(arrt.comment, comment, commentLength);
    }

    return arrt;
}
z__Dynt z__Dynt_newFromFile(const char filepath[], z__size sizePerVal, const char *comment, z__i32 commentLength, z__u8 typeID)
{
    FILE *fp;
    if((fp = fopen(filepath, "rb")) == NULL)
    {
        return (z__Dynt){NULL, NULL, 0, 0, 0, 0};
    }

    fseek(fp, 0, SEEK_END);
    long fsz = ftell(fp);
    fsz += 1;
    fseek(fp, 0, SEEK_SET);  /* same as rewind(fp); */

    z__u64 len = fsz/sizePerVal;

    void *data = malloc(len * sizePerVal);
    fread(data, 1, fsz-1, fp);
    fclose(fp);

    return (z__Dynt){
         .data = data
        ,.size = sizePerVal
        ,.len = len
        ,.lenUsed = (len) -1
    };
}
void z__Dynt_push( z__Dynt *arrt, void *val)
{
    if (arrt->lenUsed >= arrt->len)
    {
        arrt->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
        arrt->data = z__REALLOC_SAFE(arrt->data,  arrt->size * (arrt->len) );
    }
    
    void *tmpptr = (arrt->data) + (arrt->lenUsed * arrt->size);
    memcpy(tmpptr, val, arrt->size);
    arrt->lenUsed += 1;
}
void z__Dynt_pop( z__Dynt *arrt)
{
    arrt->lenUsed -= 1;
    if ((arrt->len - arrt->lenUsed) >= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
    {
        arrt->len -= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
        arrt->data = z__REALLOC_SAFE(arrt->data,  arrt->size * (arrt->len) );
    }
}
inline void z__Dynt_resize(z__Dynt *arrt, z__u32 newsize)
{
    arrt->len = newsize;
    if (arrt->lenUsed > arrt->len)
    {
        arrt->lenUsed = arrt->len;
    }

    arrt->data = z__REALLOC_SAFE(arrt->data, arrt->size * (arrt->len));
}
z__Dynt z__Dynt_makeCopy(const z__Dynt arrt)
{
    z__Dynt arrtCopy = {
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
inline void z__Dynt_delete(z__Dynt* arrt, z__bool nameFree)
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
