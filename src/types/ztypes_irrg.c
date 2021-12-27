#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "base.h"
#include "irrg.h"
#include "mem.h"

#ifdef Z___TYPE_CONFIG__USE_IRREGULAR_ARRAYTYPE
    z__Irrg z__Irrg_new(z__u32 len)
    {
        return (z__Irrg) {
            .data = malloc(sizeof(z__ptr*)*len),
            .size = malloc(sizeof(z__size*)*len),
            .typeID = malloc(sizeof(z__u8)*len),
            .len = len,
            .lenUsed = 0,
            .comment = malloc(sizeof(char*)*len)
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
            free(irgt->data[i]);
            free(irgt->comment[i]);
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
            z__size news = irgt->len + Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
            z__Irrg_resize(irgt, news);

        }

        irgt->data[irgt->lenUsed] = malloc(size);
        memcpy(irgt->data[irgt->lenUsed], val, size);

        irgt->size[irgt->lenUsed] = size;
        irgt->typeID[irgt->lenUsed] = typeID;

        if (commentLength == 0) {
            irgt->comment[irgt->lenUsed] = NULL;
        } else if (commentLength == -1) {
            irgt->comment[irgt->lenUsed] = malloc(sizeof(char) * strnlen(comment, 1024));
            snprintf(irgt->comment[irgt->lenUsed], 1024, "%s", comment);
        } else {
            irgt->comment[irgt->lenUsed] = malloc(sizeof(char) * commentLength);
            memcpy(irgt->comment[irgt->lenUsed], comment, commentLength);
        }

        irgt->lenUsed += 1;

    }

    void z__Irrg_pop(z__Irrg *irgt)
    {
        if (irgt->lenUsed-1 >= 0)
        {
            free(irgt->data[irgt->lenUsed-1]);
            irgt->lenUsed -= 1;

            if ((irgt->len - irgt->lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
            {
                z__size news = irgt->len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
                z__Irrg_resize(irgt, news);
            }
        }

    }

    void z__Irrg_delete(z__Irrg *irgt)
    {
        for (int i = irgt->lenUsed; i >= 0; --i)
        {
            free(irgt->data[i]);
            free(irgt->comment[i]);
            
        }
        free(irgt->size);
        free(irgt->typeID);

        free(irgt->data);
        free(irgt->comment);

        irgt->len = 0;
        irgt->lenUsed = 0;
    }
#endif
