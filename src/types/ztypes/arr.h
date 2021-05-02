#ifndef ZAKAROUF__ZTYPES_TYPES__ARR_H
#define ZAKAROUF__ZTYPES_TYPES__ARR_H

#include "../config.h"
#include "mem.h"

/* Known Type-safe arrays */
#define z__ArrFx(T, sz, N) T N[sz]

#define z__ArrSxDef(T, sz, tagName)\
    struct  _z__SxArr_deftag_ ## tagName	\
    {                           		\
        T data[sz];             		\
        const z__i32 len;       		\
        z__i32 lenUsed;         		\
    }

#define z__ArrSx(SDeftag, N)\
    struct _z__SxArr_deftag_ ## SDeftag N = {.len = sizeof(N.data)/sizeof(N.data[0]), .lenUsed = 0}

#define z__ArrSxT(T, N)\
    T N = {.len = sizeof(N.data)/sizeof(N.data[0]), .lenUsed = 0}

#define z__ArrSxI(T, sz, N)\
    z__SxArrDef(T, sz, N) N = {.len = sz, .lenUsed = 0}

#define z__ArrSx_push(arr)\
    {                                           \
        if((arr)->lenUsed < (arr->len))         \
        {                                       \
            (arr)->data[(arr)->lenUsed] = val;  \
            (arr)->lenUsed += 1;                \
        };                                      \
    }
#define z__ArrSx_pop(arr)\
    {                           \
        if((arr)->lenUsed >= 0) \
        {                       \
            (arr)->lenUsed -= 1;\
        };                      \
    }

#define z__Arr(T)\
    struct              \
    {                   \
        T* data;        \
        z__i32 len;     \
        z__i32 lenUsed; \
    }

#define z__Arr_delete(arr)\
    {                           \
        (arr)->len = 0;        \
        (arr)->lenUsed = 0;    \
        free((arr)->data);      \
    }

#define z__Arr_new(arr, sz)\
    {                                                   \
        (arr)->data = malloc(sizeof(*(arr)->data)*sz);  \
        (arr)->len = sz;                                \
        (arr)->lenUsed = 0;                             \
    }
#define z__Arr_push(arr, val...)\
    {                                                                                           \
        if ((arr)->lenUsed >= (arr)->len)                                                       \
        {                                                                                       \
            (arr)->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;                                   \
            (arr)->data = z__REALLOC_SAFE((arr)->data,  sizeof(*(arr)->data)* ((arr)->len) );   \
        }                                                                                       \
        (arr)->data[(arr)->lenUsed] = val;                                                      \
        (arr)->lenUsed += 1;                                                                    \
    }
#define z__Arr_pushMC(arr, val...)\
    {                                                                                           \
        if ((arr)->lenUsed >= (arr)->len)                                                       \
        {                                                                                       \
            (arr)->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;                                   \
            (arr)->data = z__REALLOC_SAFE((arr)->data,  sizeof(*(arr)->data)* ((arr)->len) );   \
        }                                                                                       \
        memcpy(&(arr)->data[(arr)->lenUsed], (val), sizeof(*(arr)->data));                      \
        (arr)->lenUsed += 1;                                                                    \
    }
#define z__Arr_pushN(arr, val...)\
    {                                           \
        (arr)->data[(arr)->lenUsed] = val;      \
        (arr)->lenUsed += 1;                    \
    }
#define z__Arr_pushNMC(arr, val...)\
    {                                                                       \
        memcpy(&(arr)->data[(arr)->lenUsed], (val), sizeof(*(arr)->data));  \
        (arr)->lenUsed += 1;                                                \
    }
#define z__Arr_resize(arr, newSize)\
    {                                                                               \
        if ((arr)->lenUsed > newSize)                                               \
        {                                                                           \
           ( arr)->lenUsed = newSize;                                               \
        }                                                                           \
        (arr)->data = z__REALLOC_SAFE((arr)->data, newSize * sizeof(*(arr)->data)); \
        (arr)->len = newSize;                                                       \
    }
#define z__Arr_pop(arr)\
    {                                                                               \
        (arr)->lenUsed -= 1;                                                        \
        if (((arr)->len - (arr)->lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)     \
        {                                                                           \
            z__Arr_resize(arr, (arr)->len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);    \
        }                                                                           \
    }
#define z__Arr_join(dest, from)\
    {                                                                                                   \
        z__i32 totalLength = (dest)->lenUsed*sizeof(*(dest)->data) + from.lenUsed*sizeof(*from.data);   \
        if (totalLength > (dest)->len)                                                                  \
        {                                                                                               \
            z__Arr_resize(dest, totalLength+1)                                                          \
        }                                                                                               \
        memcpy(&(dest)->data[(dest)->lenUsed], from.data, from.lenUsed * sizeof(*(dest)->data));        \
    }

#define z__Arr_slice_5(arr, dest, from, upto, step)\
{                                                       \
    if ((arr).lenUsed > (dest)->len) {                  \
        z__Arr_resize(dest, (arr).lenUsed);             \
    }                                                   \
    int j = 0, i = from;                                \
    for (; i < upto; i += step,j++) {                   \
        (dest)->data[j] = (arr).data[i];                \
    }                                                   \
    (dest)->lenUsed = (j)+1;                            \
}
#define z__Arr_slice_4(arr, dest, from, upto) z__Arr_slice_5(arr, dest, from, upto, 1)
#define z__Arr_slice_3(arr, dest, from) z__Arr_slice_4(arr, dest, from, (arr).lenUsed-1)
#define z__Arr_slice_2(arr, dest) z__Arr_slice_4(arr, dest, 0, (arr).lenUsed-1)
#define z__Arr_slice(...) zpp__Args_Overload(z__Arr_slice_, __VA_ARGS__)


#define z__Arr_sliceR_5(arr, dest, from, upto, step)\
{                                                                                               \
    if ((arr).lenUsed > (dest)->len) {                                                          \
        z__Arr_resize(dest, (arr).lenUsed);                                                     \
    }                                                                                           \
    int j = 0, i = (arr).lenUsed-from, _upto = (((arr).lenUsed-from > 0)?(arr).lenUsed-from:0);   \
    for (; i > _upto; i -= step, j++) {                                                         \
        (dest)->data[j] = (arr).data[i];                                                        \
    }                                                                                           \
    (dest)->lenUsed = (j)+1;                                                                    \
}

#define z__Arr_sliceR_4(arr, dest, from, upto) z__Arr_sliceR_5(arr, dest, from, upto, 1)
#define z__Arr_sliceR_3(arr, dest, from) z__Arr_sliceR_4(arr, dest, from, (arr).lenUsed)
#define z__Arr_sliceR_2(arr, dest) z__Arr_sliceR_4(arr, dest, 0, (arr).lenUsed)
#define z__Arr_sliceR(...) zpp__Args_Overload(z__Arr_sliceR_, __VA_ARGS__)


#define z__Arr_map_4(arr, mapValStep, mapValFrom, operator)                             \
{                                                                                       \
    z__typeof(*(arr)->data)z__Arr_map__TMP_DATA = mapValFrom;                           \
    for(int i = 0; i < (arr)->len; i++, z__Arr_map__TMP_DATA operator##= mapValStep)    \
    {                                                                                   \
        (arr)->data[i] = z__Arr_map__TMP_DATA;                                          \
    }; (arr)->lenUsed = (arr)->len;                                                     \
}

#define z__Arr_map_3(arr, mapValStep, mapValFrom) z__Arr_map_4(arr, mapValStep, mapValFrom, +)
#define z__Arr_map_2(arr, mapValStep) z__Arr_map_4(arr, mapValStep, 0, +)
#define z__Arr_map_1(arr) { memset((arr)->data, 0, (arr)->len * sizeof(*(arr)->data)); }
#define z__Arr_map(...) zpp__Args_Overload(z__Arr_map_, __VA_ARGS__)


#ifdef Z___TYPE_CONFIG__USE_TYPE_ARR_PREDEFINED
	
	#include "base.h"

    // Signed
    typedef z__Arr(z__i8)  z__i8Arr;
    typedef z__Arr(z__i16) z__i16Arr;
    typedef z__Arr(z__i32) z__i32Arr;
    typedef z__Arr(z__i64) z__i64Arr;

    // Unsigned
    typedef z__Arr(z__u8)  z__u8Arr;
    typedef z__Arr(z__u16) z__u16Arr;
    typedef z__Arr(z__u32) z__u32Arr;
    typedef z__Arr(z__u64) z__u64Arr;

    // Floats
    typedef z__Arr(z__f32) z__f32Arr;
    typedef z__Arr(z__f64) z__f64Arr;

    // Boolean
    typedef z__Arr(z__bool) z__boolArr;

    // Void *
    typedef z__Arr(z__ptr) z__ptrArr;
    typedef z__Arr(void) z__voidArr;



    #ifdef Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS

        // Initialization
        z__i8Arr z__i8Arr_new(z__u32 len);
        z__i16Arr z__i16Arr_new(z__u32 len);
        z__i32Arr z__i32Arr_new(z__u32 len);
        z__i64Arr z__i64Arr_new(z__u32 len);

        z__u8Arr z__u8Arr_new(z__u32 len);
        z__u16Arr z__u16Arr_new(z__u32 len);
        z__u32Arr z__u32Arr_new(z__u32 len);
        z__u64Arr z__u64Arr_new(z__u32 len);

        z__f64Arr z__f64Arr_new(z__u32 len);

        z__boolArr z__boolArr_new(z__u32 len);

        z__ptrArr z__ptrArr_new(z__u32 len);

        // Adding Value At top
        void z__i8Arr_push( z__i8Arr *arr, z__i8 val);
        void z__i16Arr_push( z__i16Arr *arr, z__i16 val);
        void z__i32Arr_push( z__i32Arr *arr, z__i32 val);
        void z__i64Arr_push( z__i64Arr *arr, z__i64 val);

        void z__u8Arr_push( z__u8Arr *arr, z__u8 val);
        void z__u16Arr_push( z__u16Arr *arr, z__u16 val);
        void z__u32Arr_push( z__u32Arr *arr, z__u32 val);
        void z__u64Arr_push( z__u64Arr *arr, z__u64 val);

        void z__f32Arr_push( z__f32Arr *arr, z__f32 val);
        void z__f64Arr_push( z__f64Arr *arr, z__f64 val);

        void z__boolArr_push( z__boolArr *arr, z__bool val);

        // Resizing Arrays
        void z__i8Arr_resize( z__i8Arr *arr, z__i8 newSize);
        void z__i16Arr_resize( z__i16Arr *arr, z__i16 newSize);
        void z__i32Arr_resize( z__i32Arr *arr, z__i32 newSize);
        void z__i64Arr_resize( z__i64Arr *arr, z__i64 newSize);

        void z__u8Arr_resize( z__u8Arr *arr, z__u8 newSize);
        void z__u16Arr_resize( z__u16Arr *arr, z__u16 newSize);
        void z__u32Arr_resize( z__u32Arr *arr, z__u32 newSize);
        void z__u64Arr_resize( z__u64Arr *arr, z__u64 newSize);

        void z__f32Arr_resize( z__f32Arr *arr, z__f32 newSize);
        void z__f64Arr_resize( z__f64Arr *arr, z__f64 newSize);

        void z__boolArr_resize( z__boolArr *arr, z__bool newSize);


        // Removing Value from the top
        #define _z__Arrpop_tmpl(arr, func)\
            {                                                                           \
                (arr)->lenUsed -= 1;                                                    \
                if (((arr)->len - (arr)->lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT) \
                {                                                                       \
                    func (arr, (arr)->len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);        \
                }                                                                       \
            }

        #define z__i8Arr_pop(arr)   _z__Arrpop_tmpl(arr, z__i8Arr_resize )
        #define z__i16Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__i16Arr_resize)
        #define z__i32Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__i32Arr_resize)
        #define z__i64Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__i64Arr_resize)
        #define z__u8Arr_pop(arr)   _z__Arrpop_tmpl(arr, z__u8Arr_resize )
        #define z__u16Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__u16Arr_resize)
        #define z__u32Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__u32Arr_resize)
        #define z__u64Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__u64Arr_resize)
        #define z__f32Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__f32Arr_resize)
        #define z__f64Arr_pop(arr)  _z__Arrpop_tmpl(arr, z__f64Arr_resize)
        #define z__boolArr_pop(arr) _z__Arrpop_tmpl(arr, z__boolArr_resize)


    #endif //Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS


#endif

#ifdef Z___TYPE_CONFIG__USE_ARR_FUNTION_GENERATION_TEMPLATE

    #define z__Arr_FN(T, vT)                            \
        typedef z__Arr(vT) T;                           \
        Z__INLINE T z__Arr_ ## T ## _new(z__u32 len)  \
        {                                               \
            return (T) {                                \
                .data = malloc(sizeof (vT) * len),      \
                .len = len,                             \
                .lenUsed = 0                            \
            };                                          \
        }                                               \
        \
        Z__INLINE T z__Arr_ ## T ## _push(z__u32 len)
        

#endif


#define z__Arr_getLen(arr)          arr.len
#define z__Arr_getUsed(arr)         arr.lenUsed
#define z__Arr_getData(arr)         arr.data
#define z__Arr_getVal(arr, index)   arr.data[index]
#define z__Arr_getTop(arr)          arr.data[arr.lenUsed-1]
#define z__Arr_getTopMT(arr)        arr.data[arr.lenUsed]


#endif