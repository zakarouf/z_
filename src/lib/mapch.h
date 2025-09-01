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

#ifndef ZAKAROUF_Z_IMP__MAPCH_H
#define ZAKAROUF_Z_IMP__MAPCH_H

#include "std/primitives.h"
#include "vector.h"
#include "utils.h"

#include "u8arr.h"

/**
 * z__MapCh()
 * Tileset Oriented Map Type with fixed layers or z-dimention. and Multiple Chunks.
 * size: Dimention of Each Chunk.
 * chunkCount: Total no. of chunks allocated.
 * chunkRadius: Radius of square-grid layout of chunks.
 */
#define z__MapCh(Name, T, ...)\
    typedef struct Name Name;                                                           \
    struct Name {                                                                       \
        /* Map Size in x, y, z  */                                                      \
        z__u32Vec3 size;                                                                \
                                                                                        \
        /* Total no. chunks allocated */                                                \
        z__u16 chunk_capacity;                                                          \
        /* Total no. chunks in usage */                                                 \
        z__u16 chunk_count;                                                             \
        /* Radius of square-grid layout of chunks. f(n) = ceil(2/n) - 1 */              \
        z__u16 chunk_radius;                                                            \
                                                                                        \
        /**
         * Main Data Stream
         * * Of each point of 4D array normalized to 2D array (3D each)
         * * The actual way it is being internalized is Described obove although
         *   anyone is free change it.
         */                                                                             \
        T **chunks;                                                                     \
                                                                                        \
        /**
         * Extra Stuff Declared later on (Optional)
         * NOTE Initialization & Deletion of any heap data of the vars declared
         *      here is upto the one who declared it in the first place as this module
         *      can't predict the declaration beforehand.
         */                                                         \
        __VA_ARGS__                                                 \
    }

#define z__MapCh_MAX_CHUNKCOUNT (0xFFFF)
#define z__MapCh_MAX_CHUNKRADIUS (0xFFFF/0xFF)


#define z__PRIV__map__CH_DEFAULT_RADIUS_SIZE 1
#define z__PRIV__map__CH_DEFAULT_X_SIZE 		32
#define z__PRIV__map__CH_DEFAULT_Y_SIZE 		32
#define z__PRIV__CH_DEFAULT_Z_SIZE 		16

#define z__MapCh_size(map)        (map)->size
#define z__MapCh_xsize(map)       (map)->size.x
#define z__MapCh_ysize(map)       (map)->size.y
#define z__MapCh_zsize(map)       (map)->size.z
#define z__MapCh_plots(map)       (z__MapCh_xsize(map) * z__MapCh_ysize(map) * z__MapCh_zsize(map))

#define z__MapCh_chunkCount(map)  (map)->chunkCount
#define z__MapCh_chunkRadius(map) (map)->chunkRadius

#define z__MapCh_getraw(map, ch_num, x1, y1, z1)\
    ((map)->chunks\
        [ch_num]\
            [zse_xyz3Dto1D(x1, y1, z1, (map)->size.x, (map)->size.y)])

#define z__MapCh_get(map, x1, y1, z1, ch_x, ch_y, ch_z)\
    z__MapCh_getraw(\
          map, z__xyz3Dto1D(\
                    ch_x, ch_y, ch_z\
                  , z__MapCh_calcChunk_Side_fromRad(map), z__MapCh_calcChunk_Side_fromRad(map))\
        , x1, y1, z1) \


/* (p == playerCord|xyz|, C == chunkCord|xyz|, CSize == chunkSize|xyz|) */ 
#define z__MapCh_calcAbsPos(p, C, CSize) (((CSize)*(C)) + p)


#define z__MapCh_calcChunk_Side_fromRad__num(radius)    (1 + (2 * (radius)))
#define z__MapCh_calcChunk_Count_fromRad__num(r)        z__MapCh_calcChunk_Side_fromRad__num(r) * z__MapCh_calcChunk_Side_fromRad__num(r)
#define z__MapCh_calcChunk_Mid_fromRad__num(radius)     ((z__MapCh_calcChunk_Count_fromRad__num(radius) >> 1) + 1 )

#define z__MapCh_calcChunk_Side_fromRad(map)   z__MapCh_calcChunk_Count_fromRad__num((map)->chunk_radius)
#define z__MapCh_calcChunk_Count_fromRad(map)\
    z__MapCh_calcChunk_Side_fromRad(map) * z__MapCh_calcChunk_Side_fromRad(map)

#define z__MapCh_calcChunk_Mid_fromRad(map)    z__MapCh_calcChunk_Mid_fromRad__num((map)->chunk_radius)
#define z__MapCh_setChunk_Count_fromRad(map)   { (map)->chunk_count = z__MapCh_calcChunk_Count_fromRad(map) }
#define z__MapCh_evalChunk_Count_fromRad(map)  ((map)->chunk_count == z__MapCh_calcChunk_Count_fromRad(map)? true: false)


/* ----------------------------------------- *** ----------------------------------------- */
/* ----------------------------------------- *** ----------------------------------------- */

void z__MapCh_new__raw(void *map, z__u32 plotsize, z__u32Vec3 size, z__u16 ch_count, z__u16 chunk_radius);
void z__MapCh_delete__raw(void *map);
void z__MapCh_dump_meta__raw(void *map, z__u8Arr *result);
void z__MapCh_load_meta__raw(void *map, z__u8Arr *data, z__size from);
void z__MapCh_dump_chunk__raw(void *map, z__u32 plotsize, z__u16 which_chunk, z__u8Arr *result);
void z__MapCh_load_chunk__raw(void *map, z__u32 plotsize, z__u16 which_chunk, z__u8Arr *data, z__size from);

#define z__MapCh_new(map, x, y, z, ch_count, ch_rad)\
    {(void)(map)->chunk_count; (void)(map)->chunk_radius; (void)(map)->size; (void)(map)->chunks;\
        z__MapCh_new__raw(map, sizeof(**(map)->chunks), (z__u32Vec3){.raw = {x, y, z}}, ch_count, ch_rad);}

#define z__MapCh_new_fromrad(map, x, y, z, ch_rad)\
    {(void)(map)->chunk_count; (void)(map)->chunk_radius; (void)(map)->size; (void)(map)->chunks;\
        z__MapCh_new(map, x, y, z, z__MapCh_calcChunk_Count_fromRad__num(ch_rad), ch_rad);}

#define z__MapCh_delete(map)\
    {(void)(map)->chunk_count; (void)(map)->chunk_radius; (void)(map)->size; (void)(map)->chunks;\
        z__MapCh_delete__raw(map);}

#define z__MapCh_dump_meta(map, result)\
    {(void)(map)->chunk_count; (void)(map)->chunk_radius; (void)(map)->size; (void)(map)->chunks;\
        z__MapCh_dump_meta__raw(map, result);}

#define z__MapCh_load_meta(map, data, from)\
    {(void)(map)->chunk_count; (void)(map)->chunk_radius; (void)(map)->size; (void)(map)->chunks;\
        z__MapCh_load_meta__raw(map, data, from);}

#define z__MapCh_dump_chunk(map, chunk, result)\
    {(void)(map)->chunk_count; (void)(map)->chunk_radius; (void)(map)->size; (void)(map)->chunks;\
        z__MapCh_dump_chunk__raw(map, sizeof(**(map)->chunks), chunk, result);}

#define z__MapCh_load_chunk(map, chunk, data)\
    {(void)(map)->chunk_count; (void)(map)->chunk_radius; (void)(map)->size; (void)(map)->chunks;\
        z__MapCh_load_chunk__raw(map, sizeof(**(map)->chunks), chunk, data);}




#ifdef Z__IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include "u8arr.h"
#include "forrange.h"

z__MapCh(VoidMapCh, void);
#define self VoidMapCh *map = _map;

void z__MapCh_new__raw(void *_map, z__u32 plotsize, z__u32Vec3 size, z__u16 ch_count, z__u16 chunk_radius)
{
    self;

    map->size = size;
    map->chunk_count = ch_count;
    map->chunk_radius = chunk_radius;

    map->chunks = z__CALLOC(sizeof(*map->chunks), map->chunk_count);
    for (size_t i = 0; i < map->chunk_count; ++i) {
        map->chunks[i] = z__MALLOC(plotsize * z__MapCh_plots(map));
    }
}

void z__MapCh_delete__raw(void *_map)
{
    self;

    z__forrange(i, map->chunk_count) {
        z__FREE(map->chunks[i]);
    }
    z__FREE(map->chunks);
}

void z__MapCh_dump_chunk__raw(void *_map, z__u32 plotsize, z__u16 which_chunk, z__u8Arr *result)
{
    self;

    z__u8Arr_pushStream(result, (map)->chunks[which_chunk], plotsize * z__MapCh_plots(map));
}

void z__MapCh_load_chunk__raw(void *_map, z__u32 plotsize, z__u16 which_chunk, z__u8Arr *data, z__size from)
{
    self;

    z__u8Arr_loadStream(data, from, plotsize * z__MapCh_plots(map), map->chunks[which_chunk]);
}

void z__MapCh_dump_meta__raw(void *_map, z__u8Arr *result)
{
    self;

    z__u8Arr_pushStream(result, &(map)->size, sizeof((map)->size));                 \
    z__u8Arr_pushStream(result, &(map)->chunk_radius, sizeof((map)->chunk_radius)); \
    z__u8Arr_pushStream(result, &(map)->chunk_count, sizeof((map)->chunk_count));   \
}

void z__MapCh_load_meta__raw(void *_map, z__u8Arr *data, z__size from)
{
    self;

    z__u8Arr_loadStream(data, from, sizeof(map->size), &map->size);
    z__u8Arr_loadStream(data, from, sizeof(map->chunk_radius), &map->chunk_radius);
    z__u8Arr_loadStream(data, from, sizeof(map->chunk_count), &map->chunk_count);
}


#undef self

#endif // Z__IMPLEMENTATION

#endif

