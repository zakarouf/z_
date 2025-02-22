#include <stdlib.h>
#include "std/mem.h"
#include "arena.h"

z__Arena *z__Arena_new(z__size max_capacity)
{
    z__Arena *arena = z__MALLOC(sizeof(*arena) + max_capacity);
    arena->pool = z__cast(void *, arena + 1);
    arena->capacity = max_capacity;
    arena->next = NULL;
    arena->used = 0;
    return arena;
}

void z__Arena_delete(z__Arena *arena)
{
    if(arena->next) z__Arena_delete(arena->next);
    z__FREE(arena);
}

void *z__Arena_alloc(z__Arena *arena, z__size size)
{
    if(arena->capacity < (arena->used + size)) {
        if(arena->next == NULL) {
            arena->next = z__Arena_new(
                    size > arena->capacity ? size: arena->capacity);
        }
        return z__Arena_alloc(arena->next, size);
    }
    arena->used += size;
    return arena->pool + arena->used;
}

z__size z__Arena_total_used(z__Arena *arena)
{
    return arena->next == NULL
        ? arena->used : z__Arena_total_used(arena) + arena->used;
}


