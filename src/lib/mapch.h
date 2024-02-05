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
        __VA_ARGS__;                                                \
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

#endif

