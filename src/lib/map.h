#ifndef ZAKAROUF_Z_IMP__PLOTMAP_H
#define ZAKAROUF_Z_IMP__PLOTMAP_H

#include "std/primitives.h"
#include "vector.h"

#include "u8arr.h"

/**
 * z__Map()
 * Tileset Oriented Map Type with layers or z-dimention.
 * size: Dimention of Map
 * layers: Total no. of z layers used
 * layers_capacity: Total no. of z layers allocated
 */
#define z__Map(Name, T, ...)    \
    typedef struct Name Name;       \
    struct Name {                   \
        z__u32Vec2 size;            \
        z__u32 layers;              \
        z__u32 layers_capacity;     \
        T **plots;                  \
        __VA_ARGS__;                \
    }

void z__Map_new__raw(void *map, z__u64 plotsize, z__u32 x, z__u32 y, z__u32 layers);
void z__Map_delete__raw(void *map);

int  z__Map_new_load__raw(void *_map_, z__u64 plotsize, z__u8Arr *data, z__size from);
void z__Map_dump__raw(void *map, z__u64 plotsize, z__u8Arr *data);

z__u32 z__Map_layer_push__raw(void *map, z__u64 plotsize);
void z__Map_layer_pop__raw(void *map);
void z__Map_layer_clear__raw(void *map, z__u64 plotsize, z__u32 layer);

int z__Map_layer_copy__raw(void *_map_, z__u64 plotsize, z__u32 dest, z__u32 src);
int z__Map_layer_push_copy__raw(void *_map_, z__u64 plotsize, z__u32 src);

int z__Map_layer_swap__raw(void *map, z__u32 l1, z__u32 l2);
int z__Map_layer_swap_at_top__raw(void *map, z__u32 layer);
#endif
