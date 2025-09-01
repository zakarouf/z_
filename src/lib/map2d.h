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
        __VA_ARGS__                 \
    }

void z__Map2D_new__raw(void *_map, z__size plotsize, const z__u32 x, z__u32 const y);
void z__Map2D_delete__raw(void *_map);

#define z__Map2D_new(map, x, y) z__Map2D_new__raw(map, sizeof(*(map)->plots), x, y)
#define z__Map2D_delete(map) { (void)(map)->plots; z__Map2D_delete__raw(map); }

#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include "std/mem.h"

z__Map2D(VoidMap2D, void);
#define self VoidMap2D *map = _map_;

void z__Map2D_new__raw(void *_map_, z__size plotsize, z__u32 const x, z__u32 const y)
{
    self;
    map->plots = z__MALLOC(plotsize * x * y);
    map->plotsize = plotsize;
    map->size.x = x;
    map->size.y = y;
}

void z__Map2D_delete__raw(void *_map_)
{
    self;
    z__FREE(map->plots);
}

#undef self
#endif //Z__IMPLEMENTATION

#endif

