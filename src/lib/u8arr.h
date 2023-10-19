#ifndef ZAKAROUF_Z_IMP_U8ARR_H
#define ZAKAROUF_Z_IMP_U8ARR_H

#include "arr.h"

z__u8* z__u8Arr_pushStream(z__u8Arr *arr, void const *data, z__u32 data_size);
int    z__u8Arr_loadStream(z__u8Arr *arr, z__size from, z__size size, void *data);
z__u8* z__u8Arr_pushBlank(z__u8Arr *arr, z__u32 size);

#endif // !ZAKAROUF_Z_IMP_U8ARR_H
