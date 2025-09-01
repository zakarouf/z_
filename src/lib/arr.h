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

#ifndef ZAKAROUF__ZTYPES_TYPES__ARR_H
#define ZAKAROUF__ZTYPES_TYPES__ARR_H

/**@file arr.h
 *  @brief Type Generic Dynamic Arrays
 *
 *  Type Generic Dynamic Arrays using C-macros,
 *  this file provides all the required definations and functions to use it.
 */

#include "prep/args.h"
#include "prep/nm/cond.h"

#include "std/primitives.h"
#include "std/mem.h"

#include "typeof.h"

#define Z__CONFIG__ARR__GROWTH_FACTOR__NUM      8
#define Z__CONFIG__ARR__SHRINK_FACTOR__NUM      8

/* Known Type-safe arrays */

//-------------------- Fixed-size Array ---------------------//

/**
 * @def z__ArrFx(T, N)
 * @brief Create A stact allocated Fixed sized array.
 *
 * @param T Type
 * @param N Length
 */
#define z__ArrFx(T, N) z__typeof(T [N])

/*-------------------- Dynamic Array ---------------------*/

/**
 * @def z__Arr(T)
 * @brief Define an Anonymous struct type of unit-type \a T.
 *
 * @param T Type of the units.
 */
#define z__Arr(...)\
    struct                  \
    {                       \
        __VA_ARGS__ *data;  \
        z__u32 len;         \
        z__u32 lenUsed;     \
    }

/**
 */
#define z__Arr_getLen(arr)          (arr).len
#define z__Arr_getUsed(arr)         (arr).lenUsed
#define z__Arr_getData(arr)         (arr).data
#define z__Arr_getUnitSize(arr)     sizeof(*(arr).data)
#define z__Arr_getSize(arr)         (z__Arr_getUnitSize(arr) * z__Arr_getLen(arr))
#define z__Arr_getSizeUsed(arr)     (z__Arr_getUnitSize(arr) * z__Arr_getUsed(arr))
#define z__Arr_getVal(arr, index)   (arr).data[index]
#define z__Arr_getTop(arr)          (arr).data[(arr).lenUsed-1]
#define z__Arr_getTopEmpty(arr)     (arr).data[(arr).lenUsed]


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

// Bytes
typedef z__Arr(z__byte) z__byteArr;

// Size
typedef z__Arr(z__size) z__sizeArr;

// Boolean
typedef z__Arr(z__bool) z__boolArr;

// Void *
typedef z__Arr(z__ptr) z__ptrArr;
typedef z__Arr(void) z__voidArr;

/**
 * @def z__Arr_new(arr, size)
 * @brief Initializes array by allocting memory and setting up the size.
 *
 * @param arr Array
 * @param sz Initial length of the array.
 */
#define z__Arr_new(arr, sz)\
   {                                                       \
        (arr)->data = z__MALLOC(sizeof(*(arr)->data)*sz);   \
        (arr)->len = sz;                                    \
        (arr)->lenUsed = 0;                                 \
    }

/** 
 * @def z__Arr_delete(arr)
 * @brief Deletes the array and frees memory.
 *
 * @param arr Array
 */
#define z__Arr_delete(arr)\
    {                          \
        (arr)->len = 0;        \
        (arr)->lenUsed = 0;    \
        z__FREE((arr)->data);  \
    }

/**
 * @def z__Arr_init(arr_T, ...)
 * @brief Initialize an array, and return it as rvalue.
 *
 * @param arr_T Either Array Type or lvalue whose type-array will be returned.
 * @param ... List of arrguments that will be copied into the initialize array.
 */
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

/**
 * @def z__Arr_newFromPtr(arr, src, srclen)
 * @brief Initialize array, copy pointer data from \a src to arr data.
 *
 * @param arr Array
 * @param src Pointer to the data to make copy from.
 * @param srclen Number of units inside \a src.
 */
#define z__Arr_newFromPtr(arr, src, srclen)\
    {                                                           \
        z__Arr_new(arr, srclen);                                \
        z__typeof((arr)->data) src_in = src;                    \
        memcpy((arr)->data, src_in, sizeof(*src_in) * srclen);  \
        (arr)->lenUsed = srclen;                                \
    }

/**
 * @def z__Arr_initFromPtr(arrT, src, srclen)
 * @brief Initializes the array, copys the pointer src, return the array as rvalue.
 *
 * @param arrT Either the Array Type or the Array var \a lvalue.
 * @param src Pointer
 * @param srclen Length of the pointer data
 */
#define z__Arr_initFromPtr(arrT, src, srclen)\
    ({                                                                      \
        arr_T z__Arr_initFromPtr__var__temp_arr;                            \
        z__Arr_newFromPtr(&z__Arr_initFromPtr__var__temp_arr, src, srclen); \
        z__Arr_initFromPtr__var__temp_arr;                                  \
    })

/**
 * @def z__Arr_newExtractFrom_StructArrPtr(arr, s_ptr, member, len)
 * @brief Initialize the array, with a pointer to struct array's member.
 *
 * @param arr Array
 * @param s_ptr Struct array pointer
 * @param member The struct member to fish out
 * @param len Length of the \a s_ptr.
 */
#define z__Arr_newExtractFrom_StructArrPtr(arr, s_ptr, member, len)\
    {                                                                   \
        z__Arr_new(arr, len);                                           \
        z__ptr src_in = &(s_ptr)->member;                               \
                                                                        \
        for(z__size i = 0; i < len; i++){                               \
            z__Arr_push_nocheckMC(arr, src_in);                         \
            src_in += sizeof(*s_ptr);                                   \
        }                                                               \
    }

/**
* @def z__Arr_newCopy(arr, arr_src)
* @brief Create a new Array that is a copy of \a arr_src
* 
* @param arr The Array
* @param arr_src The Source Array
*/
#define z__Arr_newCopy(arr, arr_src)\
    {                                                                       \
        z__Arr_new(arr, (arr_src).len);                                     \
        z__typeof((arr)->data) src_in = (arr_src).data;                     \
        memcpy((arr)->data, src_in, sizeof(*src_in) * (arr_src).len);       \
        (arr)->lenUsed = (arr_src).lenUsed;                                 \
    }

/**
 * @def z__Arr_clone(arr)
 * @brief Returns an copy of the any Array.
 *
 * @param arr The Source Array
 * @return Copy of the array
 */
#define z__Arr_clone(arr)\
    ({                                                                  \
        z__typeof(arr) temp_arr;                                        \
        z__Arr_new(&temp_arr, arr.len);                                 \
        memcpy(temp_arr.data, arr.data, sizeof(*arr.data) * arr.len);   \
        temp_arr.lenUsed = arr.lenUsed;                                 \
        temp_arr;                                                       \
    })

/**
 * Create an array from a pointer slice, copies it, return it to lhs.
 */
#define z__Arr_cloneFromPtr(arr_T, src, srclen)\
    ({                                              \
        arr_T temp_arr;                             \
        z__Arr_newFromPtr(&temp_arr, src, srclen);  \
        temp_arr;                                   \
    })

/**
 * Copies an array into another already initiazed array, replaces the values
 */
#define z__Arr_copy(dest_arr, arr)\
    {\
        if((dest_arr)->len <= (arr).lenUsed) {\
            (dest_arr)->data = z__REALLOC_SAFE((dest_arr)->data, (arr).lenUsed * sizeof(*(arr).data));  \
            (dest_arr)->len = (arr).lenUsed;                                                            \
        }                                                                                               \
        memcpy((dest_arr)->data, (arr).data, (arr).lenUsed * sizeof(*(arr).data));                      \
        (dest_arr)->lenUsed = (arr).lenUsed;                                                            \
    }

/**
 * Resize an array, reallocate space if newSize is greater than total capacity
 */
#define z__Arr_resize(arr, newSize)\
    {                                                                               \
        if ((arr)->lenUsed > newSize) {                                             \
           (arr)->lenUsed = newSize;                                                \
        }                                                                           \
        (arr)->data = z__REALLOC_SAFE((arr)->data, newSize * sizeof(*(arr)->data)); \
        (arr)->len = newSize;                                                       \
    }

/**
 * Resizes array capacity to its used length.
 */
#define z__Arr_resize_pack(arr)\
    {                                                                                       \
        (arr)->data = z__REALLOC_SAFE((arr)->data, (arr)->lenUsed * sizeof(*(arr)->data));  \
        (arr)->len = (arr)->lenUsed;                                                        \
    }

/**
 * Expands the total capacity of the array
 */
#define z__Arr_expand(arr, by)\
    {                                                                                   \
        (arr)->len += by;                                                               \
        (arr)->data = z__REALLOC_SAFE((arr)->data, sizeof(*(arr)->data) * ((arr)->len));\
    }

/**
 * Expands the total capacity of the array, set all the bits to 0
 */
#define z__Arr_expand_set0(arr, by)\
    {                                                               \
        z__Arr_expand(arr, by);                                     \
        memset(                                                     \
            &(arr)->data[(arr)->lenUsed]                            \
            , 0                                                     \
            , sizeof(*(arr)->data) * ((arr)->len - (arr)->lenUsed));\
    }

/**
 * Expand if lenof(arr) >= capacityof(arr)
 */
#define z__Arr_expand_if_reached_limit(arr)\
    {\
        if ((arr)->lenUsed >= (arr)->len)                                                       \
        {                                                                                       \
            (arr)->len *= 2;                                                                    \
            (arr)->data = z__REALLOC_SAFE((arr)->data,  sizeof(*(arr)->data)* ((arr)->len) );   \
        }                                                                                       \
    }

/**
 * Expand of passed number `by` added to used length is greater than the capacity
 */
#define z__Arr_expand_ifneeded(arr, by)\
    {\
        if(((arr)->lenUsed + by) > (arr)->len) {\
            z__Arr_expand(arr, by);\
        }\
    }

/**
 * Push a value no check on capacity.
 */
#define z__Arr_push_nocheck(arr, ...)\
    {                                               \
        (arr)->data[(arr)->lenUsed] = __VA_ARGS__;  \
        (arr)->lenUsed += 1;                        \
    }

/**
 * Push data stream value no check on capacity.
 */
#define z__Arr_pushStream_nocheck(arr, data_ptr, data_len)  \
    {                                                       \
       memcpy((arr)->data + (arr)->lenUsed                  \
             , data_ptr                                     \
             , data_len * sizeof(*data_ptr));               \
        (arr)->lenUsed += data_len;                         \
    }

/**
 * Push a value, using memcpy
 */
#define z__Arr_pushMC_nocheck(arr, ...)\
    {                                                                               \
        memcpy(&(arr)->data[(arr)->lenUsed], (__VA_ARGS__), sizeof(*(arr)->data));  \
        (arr)->lenUsed += 1;                                                        \
    }

/**
 * Increments the length and use constructor.
 */
#define z__Arr_push_cons_nocheck(arr, cons, ...)\
    {                               \
        (arr)->lenUsed += 1;        \
        cons(&z__Arr_getTop((*arr)) ,##__VA_ARGS__);   \
    }

/**
 * Push a value to array
 */
#define z__Arr_push(arr, ...)\
    {                                                   \
        z__Arr_expand_if_reached_limit(arr)             \
        z__Arr_push_nocheck(arr, __VA_ARGS__);          \
    }

/**
 * Push stream of data, multiple entry
 */
#define z__Arr_pushStream(arr, data_ptr, data_len)          \
    {                                                       \
        z__Arr_expand_ifneeded(arr, data_len);              \
        z__Arr_pushStream_nocheck(arr, data_ptr, data_len); \
    }

/**
 * Push a value to array, use memcpy to copy value
 */
#define z__Arr_pushMC(arr, ...)\
    {                                                                               \
        z__Arr_expand_if_reached_limit(arr);                                        \
        z__Arr_pushMC_nocheck(arr, __VA_ARGS__);                                    \
    }

/**
 * Just Increments the length.
 */
#define z__Arr_pushInc(arr)\
    {                                           \
        z__Arr_expand_if_reached_limit(arr);    \
        (arr)->lenUsed += 1;                    \
    }

/**
 * Just Increments the length, multiple indices
 */
#define z__Arr_pushIncBy(arr, by)\
    {                                   \
        z__Arr_expand_ifneeded(arr, by);\
        (arr)->lenUsed += by;           \
    }

#define z__Arr_push_cons(arr, cons, ...)\
    {                               \
        z__Arr_pushInc(arr);        \
        z__Arr_push_cons_nocheck(arr, cons ,##__VA_ARGS__)\
    }

#define z__Arr_pop_nocheck(arr)\
    {                                                                               \
        (arr)->lenUsed -= 1;                                                        \
    }

#define z__Arr_pop(arr)\
    {                                                                                   \
        (arr)->lenUsed -= 1;                                                            \
        if (((arr)->len - (arr)->lenUsed) > Z__CONFIG__ARR__SHRINK_FACTOR__NUM) { \
            z__Arr_resize(arr, (arr)->len - Z__CONFIG__ARR__SHRINK_FACTOR__NUM);  \
        }                                                                               \
    }

#define z__Arr_pop_getval(arr, v)\
    {                                   \
        *(v) = z__Arr_getTop((*arr));   \
        z__Arr_pop(arr);                \
    }

#define z__Arr_join(dest, from)\
    {                                                                                                   \
        z__i32 totalLength = (dest)->lenUsed*sizeof(*(dest)->data) + from.lenUsed*sizeof(*from.data);   \
        if (totalLength > (dest)->len){                                                                 \
            z__Arr_resize(dest, totalLength+1)                                                          \
        }                                                                                               \
        memcpy(&(dest)->data[(dest)->lenUsed], from.data, from.lenUsed * sizeof(*(dest)->data));        \
    }

/**
 */
#define z__Arr_cmpdata(arr, _ptr_data, size)(\
    (zpp__ter__if((sizeof(*(arr).data) * (arr).lenUsed) < (size)) -1\
     zpp__ter__elif((sizeof(*(arr).data) * (arr).lenUsed) > (size)) 1\
     zpp__ter__else(memcmp((arr).data, _ptr_data, (size)))))

#define z__Arr_cmp(arr1, arr2)\
    z__Arr_cmpdata(arr1, (arr2).data, sizeof(*(arr2).data) * (arr2).lenUsed)

/**
 * Returns True if equal
 */
#define z__Arr_isdataequal(arr1, arr2)\
    (                                                           \
        zpp__ter__if((arr1).lenUsed * sizeof(*(arr1).data)      \
            != (arr2).lenUsed * sizeof(*(arr2).data)) (         \
            false                                               \
        ) zpp__ter__else (                                      \
            !memcmp((arr1).data, (arr2).data, (arr1).lenUsed)   \
        )                                                       \
    )


/**
 * Create a newly allocated array from a slice of another array
 */
#define z__Arr_newSlice(...)            zpp__Args_Overload(z__PRIV__Arr_newSlice_, __VA_ARGS__)

/**
 * Create an Array slice
 */
#define z__Arr_slice(...)               zpp__Args_Overload(z__PRIV__Arr_slice_, __VA_ARGS__)

/**
 * Create an array slice in reverse
 */
#define z__Arr_sliceR(...)              zpp__Args_Overload(z__PRIV__Arr_sliceR_, __VA_ARGS__)


/* foreach loop variant for Arr 
 * Example: z__Arr_foreach(i, arr){
 *              printf("%d\n", *i);
 *          }
 *          z__Arr_foreach(i, arr, reverse, 4, 0, 1) {
 *              printf("%d\n", *i);
 *          }
 *  FOR OLDER VERSIONS
 *  NOTE: OLDER VERSIONS ARE DEPRICATED
 */
#define z__Arr_foreach(iterator, arr, ...)              z__PRIV__Arr_foreach(iterator, arr, ##__VA_ARGS__)

/**
 *
 */
#define z__Arr_map(iterator, arr, options, expr)\
    z__Arr_foreach(iterator, arr, zpp__UNPAREN(options)) { expr ; }

/**
 * Map a function into elements of a array
 */
#define z__Arr_mapfn(arr, fn, ...)\
    z__Arr_map(_i, arr, (__VA_ARGS__), fn(_i))
    //z__Arr_foreach(_i, arr ,##__VA_ARGS__) { fn(i); }

/**
 * Maps number array
 */
#define z__Arr_mapnum(...)\
    zpp__Args_Overload(z__PRIV__Arr_mapnum_, __VA_ARGS__)

/**
 * Shift elements towards right
 */
#define z__Arr_shift_right_nocheck(arr, n, ...)\
    z__PRIV__Arr_shift_right_nocheck(arr, n, ##__VA_ARGS__)

/**
 * Shift elements towards left
 */
#define z__Arr_shift_left_nocheck(arr, n, ...)\
    z__PRIV__Arr_shift_left_nocheck(arr, n, ##__VA_ARGS__)

/**
 * PRIVs
 */

/**
 */
#define z__PRIV__Arr_newSlice_5(dest, arr, from, upto, step)\
    {\
        z__size _from = from    \
            ,   _upto = upto    \
            ,   _step = step    \
            ,   _j = 0;         \
        z__Arr_new(dest, ((_upto - _from)/_step) +1);\
        for(;_from < _upto; _from += _step){        \
            (dest)->data[_j] = (arr).data[_from];   \
            _j += 1;                                \
        }                                           \
        (dest)->lenUsed = _j;                       \
    }

#define z__PRIV__Arr_newSlice_4(dest, arr, from, upto)\
    {\
        z__size _len = upto - from;                         \
        z__size _from = from;                               \
        z__Arr_new(dest, _len);                             \
        z__typeof((arr).data) _data = (dest)->data;         \
        memcpy(_data, &(arr).data[_from], sizeof(*_data) * _len);\
        (dest)->lenUsed = _len;                             \
    }

#define z__PRIV__Arr_newSlice_3(dest, arr, from) z__PRIV__Arr_newSlice_4(dest, arr, from, (arr).lenUsed-1)
#define z__PRIV__Arr_newSlice_2(dest, arr) z__Arr_newCopy(dest, arr)
#define z__PRIV__Arr_newSlice_1(arr) z__Arr_clone(arr)




/**
 */
#define z__PRIV__Arr_slice_5(arr, dest, from, upto, step)\
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

#define z__PRIV__Arr_slice_4(arr, dest, from, upto)\
    {\
        if ((arr).lenUsed > (dest)->len) {                  \
            z__Arr_resize(dest, (arr).lenUsed);             \
        }                                                   \
        int z__Arr_slice__var__from = from < 0?0:from;      \
        int z__Arr_slice__var__upto = upto > (arr).lenUsed? (arr).lenUsed : upto;   \
                                                                                    \
        memcpy((dest)->data, (arr).data[z__Arr_slice__var__from], (z__Arr_slice__var__upto - z__Arr_slice__var__from) * sizeof(*(arr).data))\
        (dest)->lenUsed = z__Arr_slice__var__upto - z__Arr_slice__var__from;\
    }

//#define z__Arr_slice_4(arr, dest, from, upto) z__Arr_slice_5(arr, dest, from, upto, 1)
#define z__PRIV__Arr_slice_3(arr, dest, from) z__PRIV__Arr_slice_4(arr, dest, from, (arr).lenUsed-1)
#define z__PRIV__Arr_slice_2(arr, dest) z__PRIV__Arr_slice_3(arr, dest, 0)




/**
 */
#define z__PRIV__Arr_sliceR_5(arr, dest, from, upto, step)\
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

#define z__PRIV__Arr_sliceR_4(arr, dest, from, upto) z__PRIV__Arr_sliceR_5(arr, dest, from, upto, 1)
#define z__PRIV__Arr_sliceR_3(arr, dest, from)       z__PRIV__Arr_sliceR_4(arr, dest, from, (arr).lenUsed)
#define z__PRIV__Arr_sliceR_2(arr, dest)             z__PRIV__Arr_sliceR_4(arr, dest, 0, (arr).lenUsed)
    
/**
*/
#define z__PRIV__Arr_mapnum_4(arr, mapValStep, mapValFrom, operator)                          \
    {                                                                                       \
        z__typeof(*(arr)->data)z__Arr_map__TMP_DATA = mapValFrom;                           \
        for(int i = 0; i < (arr)->len; i++, z__Arr_map__TMP_DATA operator##= mapValStep){   \
            (arr)->data[i] = z__Arr_map__TMP_DATA;                                          \
        };                                                                                  \
        (arr)->lenUsed = (arr)->len;                                                        \
    }

#define z__PRIV__Arr_mapnum_3(arr, mapValStep, mapValFrom)  z__PRIV__Arr_mapnum_4(arr, mapValStep, mapValFrom, +)
#define z__PRIV__Arr_mapnum_2(arr, mapValStep)              z__PRIV__Arr_mapnum_4(arr, mapValStep, 0, +)
#define z__PRIV__Arr_mapnum_1(arr)                          { memset((arr)->data, 0, (arr)->len * sizeof(*(arr)->data)); }




/**
 */
#define z__PRIV__Arr_foreach_6(iterator, arr, comp, from, upto, step) \
    for(z__typeof((arr).data) iterator = (arr).data + from \
       ;iterator zpp__CAT(z__PRIV__Arr_foreach__compas_, comp) (arr).data + upto\
       ;iterator zpp__CAT(z__PRIV__Arr_foreach__compas_step_, comp) step)

#define z__PRIV__Arr_foreach__compas_normal <
#define z__PRIV__Arr_foreach__compas_reverse >=

#define z__PRIV__Arr_foreach__compas_step_normal  +=
#define z__PRIV__Arr_foreach__compas_step_reverse -=

#define z__PRIV__Arr_foreach__compas_def_from_normal(arr) 0
#define z__PRIV__Arr_foreach__compas_def_from_reverse(arr) (arr).lenUsed-1

#define z__PRIV__Arr_foreach__compas_def_upto_normal(arr) (arr).lenUsed
#define z__PRIV__Arr_foreach__compas_def_upto_reverse(arr) 0

#define z__PRIV__Arr_foreach_5(item, arr, c, from, upto) z__PRIV__Arr_foreach_6(item, arr, c, from, upto, 1)

#define z__PRIV__Arr_foreach_4(item, arr, c, from)\
    z__PRIV__Arr_foreach_5(item, arr, c, from, zpp__CAT(z__PRIV__Arr_foreach__compas_def_upto_, c)(arr))

#define z__PRIV__Arr_foreach_3(item, arr, c)\
    z__PRIV__Arr_foreach_4(item, arr, c, zpp__CAT(z__PRIV__Arr_foreach__compas_def_from_, c)(arr))

#define z__PRIV__Arr_foreach_2(item, arr)                z__PRIV__Arr_foreach_3(item, arr, normal)
#define z__PRIV__Arr_foreach(...)                        zpp__Args_Overload(z__PRIV__Arr_foreach_, __VA_ARGS__)



/**
 */
#define z__PRIV__Arr_shift_right_nocheck_4(arr, n, index, len)\
    z__mem_shift_right((arr)->data, sizeof(*(arr)->data), len, index, n)

#define z__PRIV__Arr_shift_right_nocheck_3(arr, n, index) z__PRIV__Arr_shift_right_nocheck_4(arr, n, index, (arr)->lenUsed - (index + n))
#define z__PRIV__Arr_shift_right_nocheck_2(arr, n)      z__PRIV__Arr_shift_right_nocheck_3(arr, n, 0)

#define z__PRIV__Arr_shift_right_nocheck(...)   zpp__Args_Overload(z__PRIV__Arr_shift_right_nocheck_, __VA_ARGS__)



/**
 */
#define z__PRIV__Arr_shift_left_nocheck_4(arr, n, index, len)\
    z__mem_shift_left((arr)->data, sizeof(*(arr)->data), len, index, n)
#define z__PRIV__Arr_shift_left_nocheck_3(arr, n, index)z__PRIV__Arr_shift_left_nocheck_4(arr, n, index, (arr)->lenUsed - index)
#define z__PRIV__Arr_shift_left_nocheck_2(arr, n)   z__PRIV__Arr_shift_left_nocheck_3(arr, n, n)

#define z__PRIV__Arr_shift_left_nocheck(...)   zpp__Args_Overload(z__PRIV__Arr_shift_left_nocheck_, __VA_ARGS__)

#endif

