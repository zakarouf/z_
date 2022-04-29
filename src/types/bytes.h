#ifndef ZAKAROUF__ZTYPES_TYPES__BYTES_H
#define ZAKAROUF__ZTYPES_TYPES__BYTES_H

#include "arr.h"

typedef struct z__Bytes {
    z__Arr(z__u8) bytes;
    z__size cursor;
    z__size cursor_last;
} z__Bytes;

void z__Bytes_new(z__Bytes *, z__u32 const);
void z__Bytes_delete(z__Bytes *bt);
void z__Bytes_push(z__Bytes *, z__u8 const);
void z__Bytes_pushStream(z__Bytes *, void const * const, z__size const);
void z__Bytes_pop(z__Bytes *);
void z__Bytes_popStream(z__Bytes *, z__size const);
void z__Bytes_resize(z__Bytes *, z__size const);
int z__Bytes_isdataequal(z__Bytes *bt1, z__Bytes *bt2);
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
