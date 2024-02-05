#ifndef ZAKAROUF_Z_IMP__MAP2D_H
#define ZAKAROUF_Z_IMP__MAP2D_H

#include "std/primitives.h"
#include "vector.h"

#include "u8arr.h"

/**
 * z__Map2D()
 * Tileset Oriented Map Type with layers or z-dimention.
 * size: Dimention of Map
 * layers: Total no. of z layers used
 * layers_capacity: Total no. of z layers allocated
 */
#define z__Map2D(Name, T, ...)    \
    typedef struct Name Name;       \
    struct Name {                   \
        z__u32Vec2 size;            \
		z__size plotsize;			\
        T *plots;                   \
        __VA_ARGS__;                \
    }

void z__Map2D_new__raw(void *_map, z__size plotsize, const z__u32 x, z__u32 const y);
void z__Map2D_delete__raw(void *_map);

#define z__Map2D_new(map, x, y) z__Map2D_new__raw(map, sizeof(*(map)->plots), x, y)
#define z__Map2D_delete(map) { (void)(map)->plots; z__Map2D_delete__raw(map); }

#endif

