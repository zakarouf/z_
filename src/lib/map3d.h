#ifndef ZAKAROUF_Z__MAP3D_H
#define ZAKAROUF_Z__MAP3D_H

#include "std/primitives.h"
#include "vector.h"
#include "utils.h"

#include "u8arr.h"

/**
 * z__Map3D()
 * Tileset Oriented Map Type with layers or z-dimention.
 * size: Dimention of Map
 * layers: Total no. of z layers used
 * layers_capacity: Total no. of z layers allocated
 */
#define z__Map3D(Name, T, ...)    \
    typedef struct Name Name;       \
    struct Name {                   \
        z__u32Vec3 size;            \
		z__u32 size_total;			\
        T  *plots;                  \
        __VA_ARGS__;                \
    }

#define z__Map3D_get(map, x, y, z) (map).plots[z__xyz3Dto1D(x, y, z, (map).size.x, (map).size.y)]
#define z__Map3D_set(map, x, y, z, value) { z__Map3D_get(map, x, y, z) = value; }

#define z__Map3D_new(map, _x, _y, _z, ...)\
    {                                                               \
        (map)->size = (z__u32Vec3) { .x = _x, .y = _y, .z = _z };   \
        (map)->size_total = _x * _y * _z;                           \
        (map)->plots = z__MALLOC( sizeof(*(map)->plots) * (map)->size_total );\
        __VA_ARGS__;\
    }

#define z__Map3D_delete(map, ...)\
    {                                   \
        __VA_ARGS__;                    \
        z__FREE((map)->plots);          \
        (map)->size = (z__u32Vec3){0};   \
        (map)->size_total = 0;           \
    }                                   \

#endif

