#ifndef ZAKAROUF__ZTYPES_TYPES__ARR_H
#define ZAKAROUF__ZTYPES_TYPES__ARR_H

#include "../config_types.h"
#include "base.h"
#include "mem.h"

/* Known Type-safe arrays */

//-------------------- Fixed-size Array ---------------------//
#define z__ArrFx(T, N) z__typeof(T [N])

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
    z__ArrSxDef(T, sz, N) N = {.len = sz, .lenUsed = 0}; N

#define z__ArrSx_push(arr, val...)\
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

//-------------------- Dynamic Array ---------------------//
#define z__Arr(T)\
    struct              \
    {                   \
        T* data;        \
        z__i32 len;     \
        z__i32 lenUsed; \
    }

#define z__Arr_new(arr, sz)\
    {                                                   \
        (arr)->data = malloc(sizeof(*(arr)->data)*sz);  \
        (arr)->len = sz;                                \
        (arr)->lenUsed = 0;                             \
    }

#define z__Arr_delete(arr)\
    {                          \
        (arr)->len = 0;        \
        (arr)->lenUsed = 0;    \
        free((arr)->data);     \
    }

#define z__Arr_I(T, arr_n)\
    z__Arr(T) arr_n; z__Arr_new(&arr_n, 8)

#define z__Arr_init(arr_T, ...)\
    ({                                                                  \
        z__typeof(arr_T) temp_arr;                                      \
        z__Arr_new(&temp_arr, zpp__Args_Count(__VA_ARGS__));            \
        z__typeof(temp_arr.data) itr = temp_arr.data;                   \
        z__typeof(itr) testa = (z__typeof(*testa)[]){__VA_ARGS__};      \
        memcpy(itr, testa, sizeof(*itr) * zpp__Args_Count(__VA_ARGS__));\
        temp_arr.lenUsed = temp_arr.len;                                \
        temp_arr;                                                       \
    })

#define z__Arr_newFromPtr(arr, src, srclen)\
    {                                                           \
        z__Arr_new(arr, srclen);                                \
        z__typeof((arr)->data) src_in = src;                    \
        memcpy((arr)->data, src_in, sizeof(*src_in) * srclen);  \
        (arr)->lenUsed = srclen;                                \
    }

#define z__Arr_initFromPtr(arrT, src, srclen)\
    ({                                                                      \
        arr_T z__Arr_initFromPtr__var__temp_arr;                            \
        z__Arr_newFromPtr(&z__Arr_initFromPtr__var__temp_arr, src, srclen); \
        z__Arr_initFromPtr__var__temp_arr;                                  \
    })

#define z__Arr_newExtractFrom_StructArrPtr(arr, s_ptr, member, len)\
    {                                                                   \
        z__Arr_new(arr, len);                                           \
        z__ptr src_in = &s_ptr->member;                                 \
                                                                        \
        for(z__size i = 0; i < len; i++){                               \
            z__Arr_push_nocheckMC(arr, src_in);                         \
            src_in += sizeof(*s_ptr);                                   \
        }                                                               \
    }

#define z__Arr_newCopy(arr, arr_src)\
    {                                                                       \
        z__Arr_new(arr, arr_src.len);                                       \
        z__typeof(arr->data) src_in = arr_src.data;                         \
        memcpy((arr)->data, src_in, sizeof(*src_in) * arr_src.len);         \
        (arr)->lenUsed = arr_src.lenUsed;                                   \
    }

#define z__Arr_clone(arr)\
    ({                                                                  \
        z__typeof(arr) temp_arr;                                        \
        z__Arr_new(&temp_arr, arr.len);                                 \
        memcpy(temp_arr.data, arr.data, sizeof(*arr.data) * arr.len);   \
        temp_arr.lenUsed = arr.lenUsed;                                 \
        temp_arr;                                                       \
    })

#define z__Arr_cloneFromPtr(arr_T, src, srclen)\
    ({                                              \
        arr_T temp_arr;                             \
        z__Arr_newFromPtr(&temp_arr, src, srclen);  \
        temp_arr;                                   \
    })


#define z__Arr_resize(arr, newSize)\
    {                                                                               \
        if ((arr)->lenUsed > newSize)                                               \
        {                                                                           \
           ( arr)->lenUsed = newSize;                                               \
        }                                                                           \
        (arr)->data = z__REALLOC_SAFE((arr)->data, newSize * sizeof(*(arr)->data)); \
        (arr)->len = newSize;                                                       \
    }

#define z__Arr_push(arr, val...)\
    {                                                                                           \
        if ((arr)->lenUsed >= (arr)->len)                                                       \
        {                                                                                       \
            (arr)->len += Z___TYPE_CONFIG__ARR__GROWTH_FACTOR__NUM;                                   \
            (arr)->data = z__REALLOC_SAFE((arr)->data,  sizeof(*(arr)->data)* ((arr)->len) );   \
        }                                                                                       \
        (arr)->data[(arr)->lenUsed] = val;                                                      \
        (arr)->lenUsed += 1;                                                                    \
    }

#define z__Arr_pushMC(arr, val...)\
    {                                                                                           \
        if ((arr)->lenUsed >= (arr)->len)                                                       \
        {                                                                                       \
            (arr)->len += Z___TYPE_CONFIG__ARR__GROWTH_FACTOR__NUM;                                   \
            (arr)->data = z__REALLOC_SAFE((arr)->data,  sizeof(*(arr)->data)* ((arr)->len) );   \
        }                                                                                       \
        memcpy(&(arr)->data[(arr)->lenUsed], (val), sizeof(*(arr)->data));                      \
        (arr)->lenUsed += 1;                                                                    \
    }

#define z__Arr_push_nocheck(arr, val...)\
    {                                           \
        (arr)->data[(arr)->lenUsed] = val;      \
        (arr)->lenUsed += 1;                    \
    }

#define z__Arr_push_nocheckMC(arr, val...)\
    {                                                                       \
        memcpy(&(arr)->data[(arr)->lenUsed], (val), sizeof(*(arr)->data));  \
        (arr)->lenUsed += 1;                                                \
    }

#define z__Arr_pop(arr)\
    {                                                                               \
        (arr)->lenUsed -= 1;                                                        \
        if (((arr)->len - (arr)->lenUsed) > Z___TYPE_CONFIG__ARR__SHRINK_FACTOR__NUM)     \
        {                                                                           \
            z__Arr_resize(arr, (arr)->len - Z___TYPE_CONFIG__ARR__SHRINK_FACTOR__NUM);    \
        }                                                                           \
    }

#define z__Arr_pop_nocheck(arr)\
    {                                                                               \
        (arr)->lenUsed -= 1;                                                        \                                                                          \
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

#define z__Arr_isdataequal(arr1, arr2)\
    (\
        zpp__ter__if((arr1).lenUsed * sizeof(*(arr1).data)      \
            != (arr2).lenUsed * sizeof(*(arr2).data)) (         \
            false                                               \
        ) zpp__ter__else (                                      \
            !memcmp((arr1).data, (arr2).data, (arr1).lenUsed)   \
        )                                                       \
    )

#define z__Arr_slice_5(arr, dest, from, upto, step)\
    {                                                       \
        if ((arr).lenUsed > (dest)->len) {                  \
            z__Arr_resize(dest, (arr).lenUsed);             \
        }                                                   \
        int j = 0, i = from;                                \
        for (; i < upto; i += step, j++) {                  \
            (dest)->data[j] = (arr).data[i];                \
        }                                                   \
        (dest)->lenUsed = (j)+1;                            \
    }

#define z__Arr_slice_4(arr, dest, from, upto)\
    {\
        if ((arr).lenUsed > (dest)->len) {                  \
            z__Arr_resize(dest, (arr).lenUsed);             \
        }                                                   \
        int z__Arr_slice__var__from = from < 0?0:from;      \
        int z__Arr_slice__var__upto = upto > (arr).lenUsed? (arr).lenUsed : upto;   \
                                                                                    \
        memcpy((dest)->data, (arr).data[z__Arr_slice__var__from], (z__Arr_slice__var__upto - z__Arr_slice__var__from) * sizeof(*(arr).data))\
    }

//#define z__Arr_slice_4(arr, dest, from, upto) z__Arr_slice_5(arr, dest, from, upto, 1)
#define z__Arr_slice_3(arr, dest, from) z__Arr_slice_4(arr, dest, from, (arr).lenUsed-1)
#define z__Arr_slice_2(arr, dest) z__Arr_slice_4(arr, dest, 0, (arr).lenUsed-1)
#define z__Arr_slice(...) zpp__Args_Overload(z__Arr_slice_, __VA_ARGS__)


#define z__Arr_sliceR_5(arr, dest, from, upto, step)\
{                                                                                               \
    if ((arr).lenUsed > (dest)->len) {                                                          \
        z__Arr_resize(dest, (arr).lenUsed);                                                     \
    }                                                                                           \
    int j = 0, i = (arr).lenUsed-from, _upto = (((arr).lenUsed-from > 0)?(arr).lenUsed-from:0); \
    for (; i > _upto; i -= step, j++) {                                                         \
        (dest)->data[j] = (arr).data[i];                                                        \
    }                                                                                           \
    (dest)->lenUsed = (j)+1;                                                                    \
}

#define z__Arr_sliceR_4(arr, dest, from, upto) z__Arr_sliceR_5(arr, dest, from, upto, 1)
#define z__Arr_sliceR_3(arr, dest, from) z__Arr_sliceR_4(arr, dest, from, (arr).lenUsed)
#define z__Arr_sliceR_2(arr, dest) z__Arr_sliceR_4(arr, dest, 0, (arr).lenUsed)
#define z__Arr_sliceR(...) zpp__Args_Overload(z__Arr_sliceR_, __VA_ARGS__)


#define z__Arr_mapnum_4(arr, mapValStep, mapValFrom, operator)                             \
{                                                                                       \
    z__typeof(*(arr)->data)z__Arr_map__TMP_DATA = mapValFrom;                           \
    for(int i = 0; i < (arr)->len; i++, z__Arr_map__TMP_DATA operator##= mapValStep)    \
    {                                                                                   \
        (arr)->data[i] = z__Arr_map__TMP_DATA;                                          \
    }; (arr)->lenUsed = (arr)->len;                                                     \
}

#define z__Arr_mapnum_3(arr, mapValStep, mapValFrom)    z__Arr_mapnum_4(arr, mapValStep, mapValFrom, +)
#define z__Arr_mapnum_2(arr, mapValStep)                z__Arr_mapnum_4(arr, mapValStep, 0, +)
#define z__Arr_mapnum_1(arr) { memset((arr)->data, 0, (arr)->len * sizeof(*(arr)->data)); }
#define z__Arr_mapnum(...) zpp__Args_Overload(z__Arr_mapnum_, __VA_ARGS__)


/* foreach loop variant for Arr 
 * Example: z__Arr_foreach(int *i, arr){
 *              printf("%d\n", *i);
 *          }
 */
#define z__Arr_PRIV_foreach_5(item, arr, from, upto, step)\
    for(  int _z_Arr_foreach_var_iterator = from   \
        , _z_Arr_foreach_var_iterator_keep = 1     \
            ; _z_Arr_foreach_var_iterator < upto   \
            ; _z_Arr_foreach_var_iterator += step, _z_Arr_foreach_var_iterator_keep ^= 1) \
        for(item = &z__Arr_getVal(arr, _z_Arr_foreach_var_iterator)\
            ; _z_Arr_foreach_var_iterator_keep \
            ; _z_Arr_foreach_var_iterator_keep ^= 1)\

#define z__Arr_PRIV_foreach_4(item, arr, from, upto)    z__Arr_PRIV_foreach_5(item, arr, from, upto, 1)
#define z__Arr_PRIV_foreach_3(item, arr, from)          z__Arr_PRIV_foreach_5(item, arr, from, arr.lenUsed, 1)
#define z__Arr_PRIV_foreach_2(item, arr)                z__Arr_PRIV_foreach_5(item, arr, 0, arr.lenUsed, 1)
#define z__Arr_PRIV_foreach(...)                        zpp__Args_Overload(z__Arr_PRIV_foreach_, __VA_ARGS__)

#define z__Arr_foreach(iterator, arr, ...)              z__Arr_PRIV_foreach(iterator, arr, ##__VA_ARGS__)



#define z__Arr_shift_right_check(arr, n, from_index0, upto_index0)\
    {                                                                       \
        z__size sh_r_var___n = n,                                           \
                sh_r_var___from = from_index0,                              \
                sh_r_var___upto = upto_index0,                              \
                sh_r_var___diff = sh_r_var___upto - sh_r_var___from;        \
                                                                                                    \
        if(sh_r_var___upto > sh_r_var___from && (sh_r_var___n + sh_r_var___diff) < (arr)->len) {    \
            memmove(&(arr)->data[sh_r_var___from +sh_r_var___n],                                    \
                &(arr)->data[sh_r_var___from],                                                      \
                (sizeof(*(arr)->data) * (sh_r_var___diff)));                                        \
                                                                                                    \
            memset(&(arr)->data[sh_r_var___from], 0, sizeof(*(arr)->data) * (sh_r_var___diff));     \
            (arr)->lenUsed = (sh_r_var___diff) + sh_r_var___n;                                      \
        }                                                                                           \
    }

#define z__Arr_PRIV_shift_right_nocheck_4(arr, n, from, upto)\
    {\
            (arr)->lenUsed = z__mem_memshift_right_nocheck((arr)->data, sizeof(*(arr)->data), n,from, upto) + n;\
    }

#define z__Arr_PRIV_shift_right_nocheck_3(arr, n, from)\
    {\
        (arr)->lenUsed = z__mem_memshift_right_nocheck((arr)->data, sizeof(*(arr)->data), n, from, (arr)->lenUsed) + n;\
    }

#define z__Arr_PRIV_shift_right_nocheck_2(arr, n)\
    {                                                       \
        z__u32 sh_r_var___n = n;                            \
        if (sh_r_var___n + (arr)->lenUsed < (arr)->len) {   \
            memmove(&(arr)->data[n], (arr)->data, sizeof(*(arr)->data) * (arr)->lenUsed);   \
            (arr)->lenUsed += sh_r_var___n;                                                 \
            memset((arr)->data, 0, sizeof(*(arr)->data) * sh_r_var___n);                    \
        }                                                                                   \
    }   

#define z__Arr_PRIV_shift_right_nocheck(...)         zpp__Args_Overload(z__Arr_PRIV_shift_right_nocheck_, __VA_ARGS__)
#define z__Arr_shift_right_nocheck(arr, n, ...)      z__Arr_PRIV_shift_right_nocheck(arr, n, ##__VA_ARGS__)

#ifdef Z___TYPE_CONFIG__USE_ARR_FUNTION_GENERATION_TEMPLATE
    /* INCOMPLETE */
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

#ifdef Z___TYPE_CONFIG__USE_TYPE_ARR_PREDEFINED
	

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


#endif


#define z__Arr_getLen(arr)          (arr).len
#define z__Arr_getUsed(arr)         (arr).lenUsed
#define z__Arr_getData(arr)         (arr).data
#define z__Arr_getUnitSize(arr)     sizeof(*(arr).data)
#define z__Arr_getSize(arr)         (z__Arr_getUnitSize(arr) * z__Arr_getLen(arr))
#define z__Arr_getSizeUsed(arr)     (z__Arr_getUnitSize(arr) * z__Arr_getUsed(arr))
#define z__Arr_getVal(arr, index)   (arr).data[index]
#define z__Arr_getTop(arr)          (arr).data[arr.lenUsed-1]
#define z__Arr_getTopEmpty(arr)     (arr).data[arr.lenUsed]


#ifdef Z___TYPE_CONFIG__ALIAS_DOLLARSIGN_FOR_MACROS

    //#define z__ArrSx$(SDeftag, N)           z__ArrSx(SDeftag, N)
    //#define z__ArrSxDef$(T, sz, tagName)    z__ArrSxDef(T, sz, tagName)
    #define z__ArrSx_push$(arr, val...)         z__ArrSx_push(arr, __VA_ARGS__)
    #define z__ArrSx_pop$(arr)                  z__ArrSx_pop(arr)


    #define z__Arr_new$(arr, sz)                z__Arr_new(arr, sz)
    #define z__Arr_delete$(arr)                 z__Arr_delete(arr)
    #define z__Arr_resize$(arr, newSize)        z__Arr_resize(arr, newSize)    
    
    #define z__Arr_push$(arr, ...)              z__Arr_push(arr, __VA_ARGS__)
    #define z__Arr_push_nocheck$(arr, ...)      z__Arr_push_nocheck(arr, __VA_ARGS__)
    #define z__Arr_push_nocheckMC$(arr, ...)    z__Arr_push_nocheckMC(arr, __VA_ARGS__)

    #define z__Arr_pop$(arr)                    z__Arr_pop(arr)
    #define z__Arr_pop_nocheck$(arr)            z__Arr_pop_nocheck(arr)

    #define z__Arr_join$(dest, from)            z__Arr_join(dest, from)
    #define z__Arr_map$(...)                    z__Arr_map(__VA_ARGS__)
    #define z__Arr_slice$(...)                  z__Arr_slice(__VA_ARGS__)
    #define z__Arr_sliceR$(...)                 z__Arr_sliceR(__VA_ARGS__)

    #define z__Arr_init$(arr_T, ...)            z__Arr_init(arr_T, __VA_ARGS__)
    #define z__Arr_newFromPtr$(arr, src, sl)    z__Arr_newFromPtr(arr, src, sl)
    #define z__Arr_newCopy$(arr, arr_src)       z__Arr_newCopy(arr, arr_src)
    #define z__Arr_clone$(arr)                  z__Arr_clone(arr)
    #define z__Arr_cloneFromPtr$(arr_T, src, sl)z__Arr_cloneFromPtr(arr_T, src, sl)

    #define z__Arr_getLen$(arr)                 z__Arr_getLen(arr)
    #define z__Arr_getUsed$(arr)                z__Arr_getUsed(arr)
    #define z__Arr_getData$(arr)                z__Arr_getData(arr)
    #define z__Arr_getVal$(arr, index)          z__Arr_getVal(arr, index)
    #define z__Arr_getTop$(arr)                 z__Arr_getTop(arr)
    #define z__Arr_getTopEmpty$(arr)            z__Arr_getTopEmpty(arr)

#endif

#endif

