#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "std/mem.h"
#include "utils.h"

#include "u8arr.h"
#include "map2d.h"
#include "forrange.h"

z__Map2D(VoidMap, void);
#define self VoidMap *map = _map_;

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

