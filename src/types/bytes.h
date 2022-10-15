#ifndef ZAKAROUF__ZTYPES_TYPES__BYTES_H
#define ZAKAROUF__ZTYPES_TYPES__BYTES_H

#include "arr.h"

/**
 * z__Bytes
 * Handling Byte Stream; raw data.
 */
typedef struct z__Bytes {

    /* Byte Data */
    z__u8Arr bytes;
    
    /* Byte Cursor (Index) */
    z__size cursor;

    /* Last Position of Byte Cursor (Index) */
    z__size cursor_last;
} z__Bytes;

/**
 * Create a New Byte Stream Type.
 */
void z__Bytes_new(z__Bytes *, z__u32 const);

/**
 * Deconstructor
 */
void z__Bytes_delete(z__Bytes *bt);

/**
 * Push a singular byte into the stream
 */
void z__Bytes_push(z__Bytes *, z__u8 const);

/**
 * Push an array of bytes into the stream
 */
void z__Bytes_pushStream(z__Bytes *, void const * const, z__size const);

/**
 * Push a z__Bytes type's data in a range
 */
void z__Bytes_pushBytes_range(z__Bytes *bt, z__Bytes const *src, z__u64 from, z__u64 len);

/**
 * Push a z__Bytes type's data as a whole
 */
void z__Bytes_pushBytes(z__Bytes *bt, z__Bytes const *src);

/**
 * Delete the last pushed byte off the stream
 */
void z__Bytes_pop(z__Bytes *);

/**
 * Delete the last `n` pushed bytes off the stream
 */
void z__Bytes_popStream(z__Bytes *, z__size const);

/**
 * Resize the stream
 */
void z__Bytes_resize(z__Bytes *, z__size const);

/**
 * Compare Function for z__Bytes
 */
int z__Bytes_cmp(z__Bytes *bt1, z__Bytes *bt2);

/**
 * Check if data from two Byte Stream is equal;
 * Return Either True or False if the data is equal or unequal respectively
 */
int z__Bytes_isdataequal(z__Bytes *bt1, z__Bytes *bt2);

/**
 * Moves the Byte Cursor Forward by `n` bytes
 */
z__u32 z__Bytes_setCur_next(z__Bytes *bt, z__size by);

#define z__Bytes_get(T, Bytes, i) (*(T *)(&(Bytes)->bytes.data[i]))
#define z__Bytes_getCur(T, Bytes) (*(T *)(&(Bytes)->bytes.data[(Bytes)->cursor]))
#define z__Bytes_getCurL(T, Bytes) (*(T *)(&(Bytes)->bytes.data[(Bytes)->cursor_last]))
#define z__Bytes_getTop(T, Bytes) (*(T *)(&(Bytes)->bytes.data[(Bytes)->bytes.lenUsed-1]))

#define z__Bytes_getCur_setnext(T, Bytes) ({    \
    z__Bytes_setCur_next(Bytes, sizeof(T));     \
    z__Bytes_getCurL(T, Bytes);                 \
})

#define z__Bytes_resetCur(Bytes)\
    {                               \
        (Bytes)->cursor = 0;        \
        (Bytes)->cursor_last = 0;   \
    }

#define z__Bytes_pushV(Bytes, t) z__Bytes_pushStream(Bytes, &(t), sizeof(t))

/**/

#define z__bytes_get(data, T, idx) (z__typeof(T) *)(((z__byte *)data) + (sizeof(T) * idx))

#endif

