#ifndef ZAKAROUF_Z_IMP_U8ARR_H
#define ZAKAROUF_Z_IMP_U8ARR_H

#include "../types/arr.h"

z__u8* z__u8Arr_pushStream(z__u8Arr *arr, void const *data, z__u32 data_size);
z__u8* z__u8Arr_pushBlank(z__u8Arr *arr, z__u32 size);

#endif // !ZAKAROUF_Z_IMP_U8ARR_H
