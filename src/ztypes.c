#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ztypes.h"

void *z__safe_realloc(void * data, size_t size)
{
    void *tmpdata = realloc(data, size);
    if (tmpdata != NULL)
    {
        if (tmpdata != data)
        {
            return tmpdata;
        }
    }
    return data;
}

z__Dynt z__Dynt_create(z__type type, z__u32 len, const char *comment, z__i32 commentLength)
{
    z__Dynt arrt;

    arrt.data = malloc(type * len);
    arrt.size = type;
    arrt.len = len;
    arrt.lenUsed = 0;

    if (commentLength == 0) {
        arrt.comment = NULL;
    } else if (commentLength == -1) {
        arrt.comment = malloc(sizeof(char) * strnlen(comment, 1024));
        snprintf(arrt.comment, 1024, "%s", comment);
    } else {
        arrt.comment = malloc(sizeof(char) * commentLength);
        memcpy(arrt.comment, comment, commentLength);
    }

    return arrt;
}
void z__Dynt_push( z__Dynt *arrt, void *val)
{
    if (arrt->lenUsed >= arrt->len)
    {
        arrt->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
        arrt->data = z__safe_realloc(arrt->data,  arrt->size * (arrt->len) );
    }
    
    void *tmpptr = (arrt->data) + (arrt->lenUsed * arrt->size);
    memcpy(tmpptr, val, arrt->size);
    arrt->lenUsed += 1;
}
void z__Dynt_pop( z__Dynt *arrt)
{
    arrt->lenUsed -= 1;
    if ((arrt->len - arrt->lenUsed) >= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)
    {
        arrt->len -= Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
        arrt->data = z__safe_realloc(arrt->data,  arrt->size * (arrt->len) );
    }
}
inline void z__Dynt_resize(z__Dynt *arrt, z__u32 newsize)
{
    arrt->len = newsize;
    if (arrt->lenUsed > arrt->len)
    {
        arrt->lenUsed = arrt->len;
    }

    arrt->data = z__safe_realloc(arrt->data, arrt->size * (arrt->len));
}
z__Dynt z__Dynt_makeCopy(const z__Dynt arrt)
{
    z__Dynt arrtCopy = {
        .data = malloc(arrt.len * arrt.size),
        .len = arrt.len,
        .lenUsed = arrt.lenUsed,
        .size = arrt.size
    };

    z__u32 namelen = strlen(arrt.comment);
    if (namelen > 0)
    {
        arrtCopy.comment = malloc(sizeof(char) * namelen);
        memcpy(arrtCopy.comment, arrt.comment, namelen);
    } else {
        arrtCopy.comment = NULL;
    }

    return arrtCopy;

}
inline void z__Dynt_delete(z__Dynt* arrt, z__bool nameFree)
{
    free(arrt->data);
    arrt->len = 0;
    arrt->lenUsed = 0;
    arrt->size = 0;

    if (nameFree)
    {
        if (arrt->comment != NULL)
        {
            free(arrt->comment);
        }
    }
}


#ifdef Z___TYPE_CONFIG__USE_TYPE_ARRAYS
	#ifdef Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS

		z__ptrArr z__ptrArr_create(z__u32 len)
		{
		    return (z__ptrArr) {
		        .data = malloc(sizeof (z__ptr) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}

		z__i8Arr z__i8Arr_create(z__u32 len)
		{
		    return (z__i8Arr) {
		        .data = malloc(sizeof (z__i8) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__i8Arr_push( z__i8Arr *arr, z__i8 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data,  sizeof(z__i8)* (arr->len) );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__i16Arr z__i16Arr_create(z__u32 len)
		{
		    return (z__i16Arr) {
		        .data = malloc(sizeof(z__i16) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__i16Arr_push( z__i16Arr *arr, z__i16 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__i16)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__i32Arr z__i32Arr_create(z__u32 len)
		{
		    return (z__i32Arr) {
		        .data = malloc(sizeof(z__i32) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__i32Arr_push( z__i32Arr *arr, z__i32 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__i32)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__i64Arr z__i64Arr_create(z__u32 len)
		{
		    return (z__i64Arr) {
		        .data = malloc(sizeof(z__i64) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__i64Arr_push( z__i64Arr *arr, z__i64 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__i64)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__u8Arr z__u8Arr_create(z__u32 len)
		{
		    return (z__u8Arr) {
		        .data = malloc(sizeof(z__u8) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__u8Arr_push( z__u8Arr *arr, z__u8 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__u8)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__u16Arr z__u16Arr_create(z__u32 len)
		{
		    return (z__u16Arr) {
		        .data = malloc(sizeof(z__u16) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__u16Arr_push( z__u16Arr *arr, z__u16 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__u16)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__u32Arr z__u32Arr_create(z__u32 len)
		{
		    return (z__u32Arr) {
		        .data = malloc(sizeof(z__u32) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__u32Arr_push( z__u32Arr *arr, z__u32 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__u32)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__u64Arr z__u64Arr_create(z__u32 len)
		{
		    return (z__u64Arr) {
		        .data = malloc(sizeof(z__u64) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__u64Arr_push( z__u64Arr *arr, z__u64 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__u64)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__f32Arr z__f32Arr_create(z__u32 len)
		{
		    return (z__f32Arr) {
		        .data = malloc(sizeof(z__f32) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__f32Arr_push( z__f32Arr *arr, z__f32 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__f32)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}


		z__f64Arr z__f64Arr_create(z__u32 len)
		{
		    return (z__f64Arr) {
		        .data = malloc(sizeof(z__f64) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__f64Arr_push( z__f64Arr *arr, z__f64 val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__f64)*arr->len );
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}



		z__boolArr z__boolArr_create(z__u32 len)
		{
		    return (z__boolArr) {
		        .data = malloc(sizeof(z__bool) * len),
		        .len = len,
		        .lenUsed = 0
		    };
		}
		inline void z__boolArr_push( z__boolArr *arr, z__bool val)
		{
		    if (arr->lenUsed >= arr->len)
		    {
		        arr->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;
		        arr->data = z__safe_realloc(arr->data, sizeof(z__bool) *arr->len);
		    }
		    arr->data[arr->lenUsed] = val;
		    arr->lenUsed += 1;
		}



		inline void z__i8Arr_resize( z__i8Arr *arr, z__i8 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__i8));
		}
		inline void z__i16Arr_resize( z__i16Arr *arr, z__i16 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__i16));
		}
		inline void z__i32Arr_resize( z__i32Arr *arr, z__i32 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__i32));
		}
		inline void z__i64Arr_resize( z__i64Arr *arr, z__i64 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__i64));
		}
		inline void z__u8Arr_resize( z__u8Arr *arr, z__u8 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__u8));
		}
		inline void z__u16Arr_resize( z__u16Arr *arr, z__u16 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__u16));
		}
		inline void z__u32Arr_resize( z__u32Arr *arr, z__u32 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__u32));
		}
		inline void z__u64Arr_resize( z__u64Arr *arr, z__u64 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__u64));
		}
		inline void z__f32Arr_resize( z__f32Arr *arr, z__f32 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__f32));
		}
		inline void z__f64Arr_resize( z__f64Arr *arr, z__f64 newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__f64));
		}
		inline void z__boolArr_resize( z__boolArr *arr, z__bool newSize)
		{
		    arr->len = newSize;
		    if (arr->lenUsed > arr->len)
		    {
		        arr->lenUsed = arr->len;
		    }
		    arr->data = z__safe_realloc(arr->data, arr->len * sizeof(z__bool));
		}

	#endif // #define Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS
#endif //#ifdef Z___TYPE_CONFIG__USE_TYPE_ARRAYS
