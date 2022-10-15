#include <stdlib.h>
#include <string.h>
#include "bytes.h"

void z__Bytes_new(z__Bytes *bt, z__u32 len)
{
    z__Arr_new(&bt->bytes, len);
    bt->cursor = 0;
    bt->cursor_last = 0;
    
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


