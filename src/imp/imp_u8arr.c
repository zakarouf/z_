#include "string.h"
#include "u8arr.h"
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

