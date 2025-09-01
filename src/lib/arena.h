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

#ifndef ZAKAROUF__Z__ARENA_ALLOCATOR_H
#define ZAKAROUF__Z__ARENA_ALLOCATOR_H

#include "std/primitives.h"

typedef struct z__Arena z__Arena;
typedef struct z__ArenaRegion z__ArenaRegion;
struct z__ArenaRegion {
    z__byte *pool;
    z__size capacity;
    z__size used;
    z__ArenaRegion *next;
};

struct z__Arena {
    z__ArenaRegion 
        *begin, *end;
};

z__Arena*   z__Arena_new(z__size pool_capacity);
void        z__Arena_delete(z__Arena *a);
void*       z__Arena_alloc(z__Arena *a, z__size size);
z__size     z__Arena_total_used(z__Arena *a);


#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include "std/mem.h"
#include "std/primitives.h"

static  z__ArenaRegion *ArenaRegion_new(z__size max_capacity)
{
    z__ArenaRegion *region = z__MALLOC(sizeof(*region) + max_capacity);
    region->pool = z__cast(void *, region + 1);
    region->capacity = max_capacity;
    region->next = NULL;
    region->used = 0;
    return region;
}

static z__bool ArenaRegion_check(z__ArenaRegion *r)
{
    if(!r->capacity) return 0;
    if(r->used > r->capacity) return 0;
    if(!r->pool) return 0;

    return 1;
}

z__Arena *z__Arena_new(z__size pool_capacity)
{
    z__ArenaRegion *reg = ArenaRegion_new(pool_capacity + sizeof(z__Arena));
    z__Arena *arena = z__cast(void *, reg->pool);
    reg->used += sizeof(z__Arena);

    arena->begin = reg;
    arena->end = reg;

    return arena;
}

void z__Arena_delete(z__Arena *arena)
{
    z__ArenaRegion *reg = arena->begin;
    z__ArenaRegion *reg_next = reg->next;
    z__FREE(reg);
    reg = reg_next;
    while(reg) {
        reg->next = reg;
        z__FREE(reg);
        reg = reg->next;
    }
}

void *z__Arena_alloc(z__Arena *arena, z__size size)
{
    z__ArenaRegion *r = arena->end;
    z__size availiable = r->capacity - r->used;
    if(availiable < size) {
        z__ArenaRegion *new_r = ArenaRegion_new(size > r->capacity?
                                                size : r->capacity);
        r->next = new_r;
        arena->end = r->next;
        r = new_r;
    }

    void *mem = r->pool + r->used;
    r->used += size;
    return mem;
}

z__size z__Arena_total_used(z__Arena *arena)
{
    z__ArenaRegion *r = arena->begin;
    z__size total = r->used;
    r = r->next;
    while(r != NULL) {
        total += r->used;
        r = r->next;
    }
    return total;
}

z__size z__Arena_total(z__Arena *arena)
{
    z__ArenaRegion *r = arena->begin;
    z__size total = r->capacity;
    r = r->next;
    while(r != NULL) {
        total += r->capacity;
        r = r->next;
    }
    return total;
}

z__bool z__Arena_check(z__Arena *arena)
{
    if(!arena) return 0;
    z__bool line_check = 0;

    z__ArenaRegion *r = arena->begin;
    if(!ArenaRegion_check(r)) return 0;

    r = r->next;
    while(r != NULL) {
        if(!ArenaRegion_check(r)) return 0;
        r = r->next;
        if(r == arena->end) {
            if(r->next == NULL) {
                line_check = 1;
            }
        }
    }

    return line_check;
}

#endif //Z__IMPLEMENTATION

#endif

