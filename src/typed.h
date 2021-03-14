#ifndef ZAKAROUF__DYNAMIC_TYPE_H
#define ZAKAROUF__DYNAMIC_TYPE_H


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


#define Z___TYPE_CONFIG__USE_TYPE_ARRAYS
#define Z___TYPE_CONFIG__USE_F64_FOR_VECTOR


typedef uint8_t  z__u8;
typedef uint16_t z__u16;
typedef uint32_t z__u32;
typedef uint64_t z__u64;

typedef int8_t  z__i8;
typedef int16_t z__i16;
typedef int32_t z__i32;
typedef int64_t z__i64;

typedef int z__int;

typedef float z__f32;
typedef double z__f64;

typedef bool z__bool;

typedef void* z__ptr;

typedef struct _ZSE_Vint2
{
	z__int x, y;
}z__Vint2;

typedef struct _ZSE_Vint3
{
	z__int x, y, z;
}z__Vint3;

typedef struct _ZSE_Vint4
{
	z__int x, y, z, w;
}z__Vint4;


#ifdef Z___TYPE_CONFIG__USE_F64_FOR_VECTOR

	typedef struct _ZSE_Vector2
	{
		z__f64 x, y;
	}z__Vector2;

	typedef struct _ZSE_Vector3
	{
		z__f64 x, y, z;
	}z__Vector3;

	typedef struct _ZSE_Vector4
	{
		z__f64 x, y, z, w;
	}z__Vector4;

#else

	typedef struct _ZSE_Vector2
	{
		z__f32 x, y;
	}z__Vector2;

	typedef struct _ZSE_Vector3
	{
		z__f32 x, y, z;
	}z__Vector3;

	typedef struct _ZSE_Vector4
	{
		z__f32 x, y, z, w;
	}z__Vector4;

#endif

typedef struct __ZAKAROUF__SIMPARR_TYPE_STRUCT
{
	z__ptr data;
	z__u32 size;
	z__u32 len;
	z__u32 lenUsed;
	char *comment;

}z__ptrArr;

z__ptrArr z__ptrArr_create(size_t size, z__u32 len, const char *name, size_t nameLength);
void z__ptrArr_delete(z__ptrArr* arrt, z__bool nameFree);
void z__ptrArr_push( z__ptrArr *arrt, void *val);
void z__ptrArr_pop( z__ptrArr *arrt);
z__ptrArr z__ptrArr_makeCopy(const z__ptrArr arrt);


#ifdef Z___TYPE_CONFIG__USE_TYPE_ARRAYS

	// Signed

	typedef struct __ZAKAROUF__i8Arr_TYPE_STRUCT
	{
		z__i8 *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__i8Arr;

	typedef struct __ZAKAROUF__i16Arr_TYPE_STRUCT
	{
		z__i16 *data;

		z__u32 len;
		z__u32 lenUsed;

	}z__i16Arr;

	typedef struct __ZAKAROUF__i32Arr_TYPE_STRUCT
	{
		z__i32 *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__i32Arr;

	typedef struct __ZAKAROUF__i64Arr_TYPE_STRUCT
	{
		z__i64 *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__i64Arr;

	// Unsigned

	typedef struct __ZAKAROUF__u8Arr_TYPE_STRUCT
	{
		z__u8 *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__u8Arr;

	typedef struct __ZAKAROUF__u16Arr_TYPE_STRUCT
	{
		z__u16 *data;

		z__u32 len;
		z__u32 lenUsed;

	}z__u16Arr;

	typedef struct __ZAKAROUF__u32Arr_TYPE_STRUCT
	{
		z__u32 *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__u32Arr;

	typedef struct __ZAKAROUF__u64Arr_TYPE_STRUCT
	{
		z__u64 *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__u64Arr;


	typedef struct __ZAKAROUF__f32Arr_TYPE_STRUCT
	{
		z__f32 *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__f32Arr;

	typedef struct __ZAKAROUF__f64Arr_TYPE_STRUCT
	{
		z__f64 *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__f64Arr;

	typedef struct __ZAKAROUF__boolArr_TYPE_STRUCT
	{
		z__bool *data;
		
		z__u32 len;
		z__u32 lenUsed;

	}z__boolArr;


	z__i8Arr z__i8Arr_create(z__u32 len);
	z__i16Arr z__i16Arr_create(z__u32 len);
	z__i32Arr z__i32Arr_create(z__u32 len);
	z__i64Arr z__i64Arr_create(z__u32 len);

	z__u8Arr z__u8Arr_create(z__u32 len);
	z__u16Arr z__u16Arr_create(z__u32 len);
	z__u32Arr z__u32Arr_create(z__u32 len);
	z__u64Arr z__u64Arr_create(z__u32 len);

	z__f64Arr z__f64Arr_create(z__u32 len);

	z__boolArr z__boolArr_create(z__u32 len);


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


	#define z__i8Arr_pop(arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__i8Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__i16Arr_pop( arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__i16Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__i32Arr_pop( arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__i32Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__i64Arr_pop( arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__i64Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__u8Arr_pop(arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__u8Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__u16Arr_pop( arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__u16Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__u32Arr_pop( arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__u32Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__u64Arr_pop( arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__u64Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__f32Arr_pop( arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__f32Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__f64Arr_pop( arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__f64Arr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}
	#define z__boolArr_pop(arr)\
		{\
			arr.lenUsed -= 1;\
			if ((arr.len - arr.lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)\
			{\
				z__boolArr_resize(&arr, arr.len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);\
			}\
		}


	#define z__Arr_delete(arr)\
	{\
	    arr.len = 0;\
	    arr.lenUsed = 0;\
	    free(arr.data);\
	}

#endif


#define z__Arr_getLen(arr)\
	arr.len
#define z__Arr_getUsed(arr)\
	arr.lenUsed
#define z__Arr_getData(arr)\
	arr.data
#define z__Arr_getVal(arr, at)\
	arr.data[at]
#define z__Arr_getTop(arr)\
	arr.data[arr.lenUsed-1]

#define z__ptrArr_getvalSize(arr)\
	(z__ptrArr)arr.size
#define z__ptrArr_getVal(arr, at)\
	((arr.data) + (at * arr.size))




#ifdef Z___TYPE_CONFIG__USE_TYPE_DYNT

typedef struct _Z_CREATE_DYNT_INFO_ST
{   
    size_t typeSize;
    z__u32 len;

    char *name;
    size_t nameSize;
    z__ptr initVal;
    size_t initValSize;


}z__CreateDyntInfo;

typedef struct __ZAKAROUF__DYNAMIC_TYPE_ATTRIBUTE_STRUCT
{

	size_t size;
	char * name;
	const z__u16 mod;


}z__Dynt__attr;

typedef struct __ZAKAROUF__DYNAMIC_TYPE_STRUCT
{
	z__ptr data;
	z__u32 len;
	z__u32 lenUsed;

	z__Dynt__attr attr;

}z__Dynt;

#endif //#ifdef Z___TYPE_CONFIG__USE_TYPE_DYNT

#endif // Header Guard
