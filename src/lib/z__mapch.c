#include <stdio.h>
#include <stdlib.h>
#include "u8arr.h"
#include "forrange.h"
#include "mapch.h"

z__MapCh(VoidMap, void);
#define self VoidMap *map = _map;

void z__MapCh_new__raw(void *_map, z__u32 plotsize, z__u32Vec3 size, z__u16 ch_count, z__u16 chunk_radius)
{
    self;

    printf("%p\n", map);fflush(stdout);
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

