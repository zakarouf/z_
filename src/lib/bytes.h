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

#ifndef ZAKAROUF_Z_IMP__BYTES_H
#define ZAKAROUF_Z_IMP__BYTES_H

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

#define z__bytes_get(data, T, idx) (z__typeof(T) *)(((z__byte *)data) + (sizeof(T) * idx))



/**
 * Create a New Byte Stream Type.
 */
void z__Bytes_new(z__Bytes *, z__u32 const);

/**
 * Create a New Byte Stream and Loads up data;
 */
void z__Bytes_newFromPtr(z__Bytes *bt, const z__u8 *src, z__size _size);

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

#ifdef Z__IMPLEMENTATION
#include <string.h>
#include <stdlib.h>

void z__Bytes_new(z__Bytes *bt, z__u32 len)
{
    z__Arr_new(&bt->bytes, len);
    bt->cursor = 0;
    bt->cursor_last = 0;
    
}

void z__Bytes_newFromPtr(z__Bytes *bt, const z__u8 *src, z__size len)
{
    z__Bytes_new(bt, len + 8);
    memcpy(bt->bytes.data, src, len);
    bt->bytes.lenUsed = len;
}

void z__Bytes_delete(z__Bytes *bt)
{
    z__Arr_delete(&bt->bytes);
    bt->cursor = 0;
    bt->cursor_last = 0;
}

void z__Bytes_push(z__Bytes *bt, z__u8 const val)
{
    z__Arr_push(&bt->bytes, val);

}

void z__Bytes_pushStream(z__Bytes *bt, void const * const data, z__size data_size)
{
    if(((bt->bytes.lenUsed) * sizeof(&bt->bytes.data) + data_size) 
            >= bt->bytes.len * sizeof(&bt->bytes.data) ) {
        z__Arr_resize(
            &bt->bytes, 
            ((bt->bytes.lenUsed) * sizeof(&bt->bytes.data) 
             + data_size + 32));
    }
    memcpy(&bt->bytes.data[bt->bytes.lenUsed], data, data_size);
    bt->bytes.lenUsed += data_size;
}

void z__Bytes_pushBytes_range(z__Bytes *bt, z__Bytes const *src, z__u64 from, z__u64 len)
{
    z__Bytes_pushStream(bt, src->bytes.data + from, len);
}

void z__Bytes_pushBytes(z__Bytes *bt, z__Bytes const *src)
{
    z__Bytes_pushStream(bt, src->bytes.data, src->bytes.lenUsed);
}

int z__Bytes_cmp(z__Bytes *bt1, z__Bytes *bt2)
{
    if(bt1->bytes.lenUsed != bt2->bytes.lenUsed) {
        return (z__i64)bt1->bytes.lenUsed - (z__i64)bt2->bytes.lenUsed;
    }
    return memcmp(bt1->bytes.data, bt2->bytes.data, bt1->bytes.lenUsed);
}

int z__Bytes_isdataequal(z__Bytes *bt1, z__Bytes *bt2)
{
    if(bt1->bytes.lenUsed != bt2->bytes.lenUsed) return 0;
    return !memcmp(bt1->bytes.data, bt2->bytes.data, bt1->bytes.lenUsed);
}

void z__Bytes_pop(z__Bytes *bt)
{
    z__Arr_pop_nocheck(&bt->bytes);
    if(bt->cursor >= bt->bytes.lenUsed) bt->cursor--;
    if(bt->cursor_last >= bt->bytes.lenUsed) bt->cursor_last--;
}

void z__Bytes_popStream(z__Bytes *bt, z__size sz)
{
    if(sz >= bt->bytes.lenUsed) sz = bt->bytes.lenUsed;
    bt->bytes.lenUsed -= sz;

    if(bt->cursor >= bt->bytes.lenUsed) bt->cursor = bt->bytes.lenUsed;
    if(bt->cursor_last >= bt->bytes.lenUsed) bt->cursor_last = bt->bytes.lenUsed;
}

void z__Bytes_resize(z__Bytes *bt, z__size sz)
{
    z__Arr_resize(&bt->bytes, sz);

    if(bt->cursor >= bt->bytes.lenUsed) bt->cursor = bt->bytes.lenUsed;
    if(bt->cursor_last >= bt->bytes.lenUsed) bt->cursor_last = bt->bytes.lenUsed;
}

z__u32 z__Bytes_setCur_next(z__Bytes *bt, z__size by)
{
    (bt)->cursor_last = (bt)->cursor;
    if((bt)->cursor + by < (bt)->bytes.lenUsed) {
        (bt)->cursor += by;                  
        return true; 
    }
    return false; 
}

#endif //Z__IMPLEMENTATION

#endif
