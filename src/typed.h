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

#endif


#define z__ptrArr_getvalSize(arr)\
	(z__ptrArr)arr.size
#define z__ptrArr_getVal(arr, at)\
	((arr.data) + (at * arr.size))
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



#endif