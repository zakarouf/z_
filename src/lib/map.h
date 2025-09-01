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
        __VA_ARGS__                 \
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

#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "u8arr.h"
#include "forrange.h"

z__Map(VoidMapNormal, void);
#define self VoidMapNormal *map = _map_;

void z__Map_new__raw(void *_map_, z__u64 plotsize, z__u32 x, z__u32 y, z__u32 layers)
{
    self;
    
    map->size = (z__u32Vec2){ .x = x, .y = y};
    map->layers = layers;
    map->layers_capacity = layers + 8;
    
    map->plots = z__CALLOC(sizeof(*map->plots), map->layers_capacity);
    z__forrange(i, layers) {
        map->plots[i] = z__MALLOC(plotsize * x * y);
    }
}

void z__Map_delete__raw(void *_map_)
{
    self;
    
    z__forrange(i, map->layers) {
        z__FREE(map->plots[i]);
    }
    z__FREE(map->plots);

    memset(map, 0, sizeof(*map));
}

void z__Map_dump__raw(void *_map_, z__u64 plotsize, z__u8Arr *data)
{
    self;

    z__u8Arr_pushStream(data, &map->size, sizeof(map->size));
    z__u8Arr_pushStream(data, &map->layers, sizeof(map->layers));
    z__u8Arr_pushStream(data, &plotsize, sizeof(plotsize));

    z__forrange(i, map->layers) {
        z__u8Arr_pushStream(data, map->plots[i], plotsize * map->size.x * map->size.y);
    }
}

int z__Map_new_load__raw(void *_map_, z__u64 plotsize, z__u8Arr *data, z__size from)
{
    self;

    z__u8Arr_loadStream(data, from, sizeof(map->size), &map->size); from += sizeof(map->size);
    z__u8Arr_loadStream(data, from, sizeof(map->layers), &map->layers); from += sizeof(map->layers);

    z__u64 _plotsize = 0;
    z__u8Arr_loadStream(data, from, sizeof(_plotsize), &_plotsize); from += sizeof(_plotsize);

    if(_plotsize != plotsize) return 0;

    z__Map_new__raw(map, _plotsize, map->size.x, map->size.y, map->layers);
    z__size const size = _plotsize * map->size.x * map->size.y;
    z__forrange(i, map->layers) {
        z__u8Arr_loadStream(data, from, size, map->plots[i]); from += size;
    }
    return 1;
}

z__u32 z__Map_layer_push__raw(void *_map_, z__u64 plotsize)
{
    self;
    if(map->layers >= map->layers_capacity) {
        map->layers_capacity *= 2;
        map->plots = z__REALLOC_SAFE(map->plots, sizeof(*map->plots) * map->layers_capacity);
    }
    map->plots[map->layers] = z__MALLOC(plotsize * map->size.x * map->size.y);
    map->layers += 1;
    return map->layers;
}

void z__Map_layer_clear__raw(void *_map_, z__u64 plotsize, z__u32 layer)
{
    self;
    if(layer >= map->layers) return;
    memset(map->plots[layer], 0, plotsize * map->size.x * map->size.y);
}

void z__Map_layer_pop__raw(void *_map_)
{
    self;
    z__FREE(map->plots[map->layers-1]);
    map->layers -= 1;
}

int z__Map_layer_swap__raw(void *_map_, z__u32 l1, z__u32 l2)
{
    self;
    if(l1 > map->layers) return 0;
    if(l2 > map->layers) return 0;

    z__swap(map->plots[l1], map->plots[l2]);
    return 1;
}

int z__Map_layer_swap_at_top__raw(void *_map_, z__u32 layer)
{
    self;
    return z__Map_layer_swap__raw(map, map->layers-1, layer);
}

int z__Map_layer_copy__raw(void *_map_, z__u64 plotsize, z__u32 dest, z__u32 src)
{
    self;
    if(src >= map->layers) return 0;
    if(dest >= map->layers) return 0;
    if(src == dest) return 1;
    memcpy(map->plots[dest], map->plots[src], plotsize * map->size.x * map->size.y);
    return 1;
}

int z__Map_layer_push_copy__raw(void *_map_, z__u64 plotsize, z__u32 src)
{
    z__u32 dest = z__Map_layer_push__raw(_map_, plotsize);
    return z__Map_layer_copy__raw(_map_, plotsize, dest, src);
}

#undef self
#endif //Z__IMPLEMENTATION

#endif
