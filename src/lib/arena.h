#ifndef ZAKAROUF__Z__ARRLLIST_H
#define ZAKAROUF__Z__ARRLLIST_H

#include "std/primitives.h"

typedef struct z__Arena z__Arena;
struct z__Arena {
    z__byte *pool;
    z__size capacity;
    z__size used;
    z__Arena *next;
};

z__Arena*   z__Arena_new(z__size pool_capacity);
void        z__Arena_delete(z__Arena *a);
void*       z__Arena_alloc(z__Arena *a, z__size size);
z__size     z__Arena_total_used(z__Arena *a);

#endif

