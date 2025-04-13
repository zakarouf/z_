#ifndef ZAKAROUF_Z_IMP_U8ARR_H
#define ZAKAROUF_Z_IMP_U8ARR_H

#include "arr.h"

z__u8* z__u8Arr_pushStream(z__u8Arr *arr, void const *data, z__u32 data_size);
int    z__u8Arr_loadStream(z__u8Arr *arr, z__size from, z__size size, void *data);
z__u8* z__u8Arr_pushBlank(z__u8Arr *arr, z__u32 size);

#ifdef Z__IMPLEMENTATION
#include "string.h"
#include <string.h>

z__u8* z__u8Arr_pushBlank(z__u8Arr *arr, z__u32 size)
{
    if((size + arr->lenUsed) > arr->len) {
        z__Arr_expand(arr, size);
    }

    z__u8 *data = arr->data + arr->lenUsed;
    memset(data, 0, size);

    arr->lenUsed += size;
    return data;
}

z__u8* z__u8Arr_pushStream(z__u8Arr *arr, void const *data, z__u32 data_size)
{
    if(data_size + arr->lenUsed > arr->len) {
        z__Arr_expand(arr, data_size);
    }
    memcpy(arr->data + arr->lenUsed, data, data_size);
    z__u8 *new_data = arr->data + arr->lenUsed;
    arr->lenUsed += data_size;
    return new_data;
}

int z__u8Arr_loadStream(z__u8Arr *arr, z__size from, z__size size, void *data)
{
    if(from > arr->lenUsed) return 0;
    if((from + size) > arr->lenUsed) return 0;
   
    memcpy(data, arr->data + from, size);
    return 1;
}

#endif //Z__IMPLEMENTATION

#endif // !ZAKAROUF_Z_IMP_U8ARR_H
