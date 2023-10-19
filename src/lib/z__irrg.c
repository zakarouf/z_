#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "irrg.h"
#include "std/mem.h"

z__Irrg z__Irrg_new(z__u32 len)
{
    return (z__Irrg) {
        .data = z__MALLOC(sizeof(z__ptr*)*len),
        .size = z__MALLOC(sizeof(z__size*)*len),
        .typeID = z__MALLOC(sizeof(z__u8)*len),
        .len = len,
        .lenUsed = 0,
        .comment = z__MALLOC(sizeof(char*)*len)
    };
}

void z__Irrg_resize(z__Irrg *irgt, z__size newsize)
{
    irgt->size = z__REALLOC_SAFE(irgt->size, sizeof(z__size)*newsize );
    irgt->typeID = z__REALLOC_SAFE(irgt->typeID, sizeof(z__u8)*newsize);

    // Free memory if _resize is not called from _push or pop
    for (z__size i = irgt->lenUsed; i > newsize; --i)
    {
        //printf("==%d\n", i);
        z__FREE(irgt->data[i]);
        z__FREE(irgt->comment[i]);
        irgt->lenUsed -= 1;
    }

    irgt->data = z__REALLOC_SAFE(irgt->data, sizeof(z__ptr*)*newsize);

    irgt->comment = z__REALLOC_SAFE(irgt->comment, sizeof(char*)*newsize);

    irgt->len = newsize;
}

void z__Irrg_push
(
      z__Irrg *irgt
    , void *val
    , z__size size
    , z__u8 typeID
    , const char *comment
    , z__i32 commentLength
)
{
    if (irgt->lenUsed == irgt->len)
    {
        z__size news = irgt->len * 2;
        z__Irrg_resize(irgt, news);

    }

    irgt->data[irgt->lenUsed] = z__MALLOC(size);
    memcpy(irgt->data[irgt->lenUsed], val, size);

    irgt->size[irgt->lenUsed] = size;
    irgt->typeID[irgt->lenUsed] = typeID;

    if (commentLength == 0) {
        irgt->comment[irgt->lenUsed] = NULL;
    } else if (commentLength == -1) {
        irgt->comment[irgt->lenUsed] = z__MALLOC(sizeof(char) * strnlen(comment, 1024));
        snprintf(irgt->comment[irgt->lenUsed], 1024, "%s", comment);
    } else {
        irgt->comment[irgt->lenUsed] = z__MALLOC(sizeof(char) * commentLength);
        memcpy(irgt->comment[irgt->lenUsed], comment, commentLength);
    }

    irgt->lenUsed += 1;

}

void z__Irrg_pop(z__Irrg *irgt)
{
    if (irgt->lenUsed-1 >= 0)
    {
        z__FREE(irgt->data[irgt->lenUsed-1]);
        irgt->lenUsed -= 1;

        if ((irgt->len - irgt->lenUsed) > 8)
        {
            z__size news = irgt->len - 8;
            z__Irrg_resize(irgt, news);
        }
    }

}

void z__Irrg_delete(z__Irrg *irgt)
{
    for (int i = irgt->lenUsed; i >= 0; --i)
    {
        z__FREE(irgt->data[i]);
        z__FREE(irgt->comment[i]);
        
    }
    z__FREE(irgt->size);
    z__FREE(irgt->typeID);

    z__FREE(irgt->data);
    z__FREE(irgt->comment);

    irgt->len = 0;
    irgt->lenUsed = 0;
}

