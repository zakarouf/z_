#ifndef ZAKAROUF__DYNAMIC_TYPE_H
#define ZAKAROUF__DYNAMIC_TYPE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "ztypes_config.h"

#ifdef Z___TYPE_INCLUED_CGLM
    #include <cglm/cglm.h>
#endif

typedef uint8_t  z__u8;
typedef uint16_t z__u16;
typedef uint32_t z__u32;
typedef uint64_t z__u64;

typedef uint_fast8_t  z__u8_f;
typedef uint_fast16_t z__u16_f;
typedef uint_fast32_t z__u32_f;
typedef uint_fast64_t z__u64_f;

//uint_fast8_t;
typedef int8_t  z__i8;
typedef int16_t z__i16;
typedef int32_t z__i32;
typedef int64_t z__i64;

typedef int_fast8_t  z__i8_f;
typedef int_fast16_t z__i16_f;
typedef int_fast32_t z__i32_f;
typedef int_fast64_t z__i64_f;

typedef float z__f32;
typedef double z__f64;

typedef int z__int;
typedef float z__float;
typedef bool z__bool;
typedef void* z__ptr;

typedef intmax_t z__imax;
typedef uintmax_t z__umax;
typedef intptr_t z__iptr;
typedef uintptr_t z__uptr;

typedef ptrdiff_t z__ptrdiff;


#ifdef Z___TYPE_CONFIG__USE_VECTORS

    // CGLM PRE_REQUSITE GOES HERE...
    #ifdef Z___TYPE_USE_CGLM
        
    #endif

    #ifdef Z___TYPE_CONFIG__USE_TYPE_ARR_VECTOR
        /* |x, y, z, w| -> w is the last */
        #ifdef Z___TYPE_INCLUED_CGLM


            typedef z__int  				z__ivec2[2];
            typedef ivec3   				z__ivec3;
            typedef z__int  				z__ivec4[4];

            typedef vec2    				z__vec2;
            typedef vec3    				z__vec3;
            typedef vec4    				z__vec4;

            typedef versor  				z__versor;

            typedef mat2  					z__mat2;
            typedef mat3  					z__mat3;
            typedef mat4  					z__mat4;



        #else


            typedef z__i32                  z__ivec2[2];
            typedef z__i32                  z__ivec3[3];
            typedef z__i32                  z__ivec4[4];

            typedef z__f32                  z__vec2[2];
            typedef z__f32                  z__vec3[3];
            typedef z__f32                  z__vec4[4];

            typedef z__vec4                 z__versor;

            typedef z__vec2                 z__mat2[2];
            typedef z__vec3                 z__mat3[3];
            typedef z__vec4                 z__mat4[4];

        #endif

        #define z__vec_x(vec) vec[0]
        #define z__vec_y(vec) vec[1]
        #define z__vec_z(vec) vec[2]
        #define z__vec_w(vec) vec[3]


    #endif

    #ifdef Z___TYPE_CONFIG__USE_TYPE_STRUCT_VECTOR

		#define z__Vector(T, ...)\
			struct              \
			{					\
				T __VA_ARGS__;	\
			}

        #ifdef Z___TYPE_CONFIG__USE_f64_FOR_VECTOR_STRUCT
			#define __vecDefType z__f64
        #else
			#define __vecDefType z__f32
        #endif

            typedef z__Vector(__vecDefType, x, y) z__Vector2;
            typedef z__Vector(__vecDefType, x, y, z) z__Vector3;
            typedef z__Vector(__vecDefType, x, y, z, w) z__Vector4;
        #undef __vecDefType

        #ifdef Z___TYPE_CONFIG__USE_i64_FOR_INT_VECTOR_STRUCT
			#define __vecDefType z__i64
        #else
			#define __vecDefType z__i32
        #endif

            typedef z__Vector(__vecDefType, x, y) z__Vint2;
            typedef z__Vector(__vecDefType, x, y, z) z__Vint3;
            typedef z__Vector(__vecDefType, x, y, z, w) z__Vint4;
        #undef __vecDefType

    #endif

#endif //#ifdef Z___TYPE_CONFIG__USE_VECTORS

void *z__safe_realloc(void * data, size_t size);
// Unknown Unsafe type Arrays
typedef struct __ZAKAROUF__SIMPARR_TYPE_STRUCT
{
    z__ptr data;
    z__u32 size;
    z__u32 len;
    z__u32 lenUsed;
    char *comment;

}z__Dynt;


#define z__typeof sizeof
typedef size_t z__type;
z__Dynt z__Dynt_create(z__type T, z__u32 len, const char *comment, z__i32 commentLength);
void z__Dynt_delete(z__Dynt* arrt, z__bool nameFree);
void z__Dynt_push( z__Dynt *arrt, void *val);
void z__Dynt_pop( z__Dynt *arrt);
void z__Dynt_resize(z__Dynt *arrt, z__u32 newsize);
z__Dynt z__Dynt_makeCopy(const z__Dynt arrt);

#define z__Dynt_getValSize(arr)           (arr.size)
#define z__Dynt_getTop(arr, T)         ( *( T *)( (arr.data) + ((arr.lenUsed-1) * arr.size)) )
#define z__Dynt_getVal(arr, index , T) ( *( T *)( (arr.data) + (index * arr.size)) )
#define z__Dynt_getValAddress(arr, index) ((arr.data) + (index * arr.size))
#define z__Dynt_getComment(arr)           (arr.comment)
#define z__Dynt_getLen(arr)               (arr.len)
#define z__Dynt_getUsed(arr)              (arr.lenUsed)


// Known Type-safe arrays
#define z__FxArr(T, sz, N) T N[sz]

#define z__SxArr(T, sz)\
    struct                      \
    {                           \
        T data[sz];       		\
        const z__i32 len;  		\
        z__i32 lenUsed;     	\
    }

#define z__dSxArr(T, sz, N)\
    struct                      \
    {                           \
        T data[sz];       		\
        const z__i32 len;  		\
        z__i32 lenUsed;     	\
    } N = {.len = sz}

#define z__iSxArr(T, N)\
    T N = {.len = sizeof(N.data)/sizeof(N.data[0])}

#define z__Arr(T)\
	struct              \
	{					\
		T* data;		\
		z__i32 len;		\
		z__i32 lenUsed;	\
	}

#define z__Arr_delete(arr)\
    {                     		\
        (arr)->len = -1;		\
        (arr)->lenUsed = -1;	\
        free((arr)->data);		\
    }

#define z__Arr_create(arr, sz)\
    {                     								\
    	(arr)->data = malloc(sizeof(*(arr)->data)*sz);	\
    	(arr)->len = sz;								\
    	(arr)->lenUsed = 0;								\
    }
#define z__Arr_push(arr, val)\
    {                     																		\
	    if ((arr)->lenUsed >= (arr)->len)														\
	    {																						\
	        (arr)->len += Z___TYPE_REALLOC_RESIZE_BY_DEFAULT;									\
	        (arr)->data = z__safe_realloc((arr)->data,  sizeof(*(arr)->data)* ((arr)->len) );	\
	    }																						\
	    (arr)->data[(arr)->lenUsed] = val;														\
	    (arr)->lenUsed += 1;																	\
    }
#define z__Arr_resize(arr, newSize)\
    {																				\
	    if ((arr)->lenUsed > newSize)												\
	    {																			\
	       ( arr)->lenUsed = newSize;												\
	    }																			\
	    (arr)->data = z__safe_realloc((arr)->data, newSize * sizeof(*(arr)->data));	\
	    (arr)->len = newSize;														\
	}
#define z__Arr_pop(arr)\
    {																				\
        (arr)->lenUsed -= 1;														\
        if (((arr)->len - (arr)->lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)		\
        {																			\
            z__Arr_resize(arr, (arr)->len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);	\
        }																			\
    }
#define z__Arr_join(dest, from)\
    {																									\
    	z__i32 totalLength = (dest)->lenUsed*sizeof(*(dest)->data) + from.lenUsed*sizeof(*from.data);	\
    	if (totalLength > (dest)->len)																	\
    	{																								\
    		z__Arr_resize(dest, totalLength+1)															\
    	}																								\
    	memcpy(&(dest)->data[(dest)->lenUsed], from.data, from.lenUsed * sizeof(*(dest)->data));		\
    }


 #define z__Arr_getLen(arr)          arr.len
 #define z__Arr_getUsed(arr)         arr.lenUsed
 #define z__Arr_getData(arr)         arr.data
 #define z__Arr_getVal(arr, index)   arr.data[index]
 #define z__Arr_getTop(arr)          arr.data[arr.lenUsed-1]


#ifdef Z___TYPE_CONFIG__USE_TYPE_ARRAYS

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


	#ifdef Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS

	    // Initialization
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

	    z__ptrArr z__ptrArr_create(z__u32 len);

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
	        {																			\
	            (arr)->lenUsed -= 1;													\
	            if (((arr)->len - (arr)->lenUsed) > Z___TYPE_REALLOC_RESIZE_BY_DEFAULT)	\
	            {																		\
	                func (arr, (arr)->len - Z___TYPE_REALLOC_RESIZE_BY_DEFAULT);		\
	            }																		\
	        }
	    #define z__i8Arr_pop(arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__i8Arr_resize)	\
	        }
	    #define z__i16Arr_pop( arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__i16Arr_resize)	\
	        }
	    #define z__i32Arr_pop( arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__i32Arr_resize)	\
	        }
	    #define z__i64Arr_pop( arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__i64Arr_resize)	\
	        }
	    #define z__u8Arr_pop(arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__u8Arr_resize)	\
	        }
	    #define z__u16Arr_pop( arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__u16Arr_resize)	\
	        }
	    #define z__u32Arr_pop( arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__u32Arr_resize)	\
	        }
	    #define z__u64Arr_pop( arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__u64Arr_resize)	\
	        }
	    #define z__f32Arr_pop( arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__f32Arr_resize)	\
	        }
	    #define z__f64Arr_pop( arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__f64Arr_resize)	\
	        }
	    #define z__boolArr_pop(arr)\
	        {											\
	        	_z__Arrpop_tmpl(arr, z__boolArr_resize)\
	        }

	    #undef _z__Arrpop_tmp

	#endif //Z___TYPE_CONFIG__USE_ARR_PREDEFINED_FUNCS


#endif



#undef z__safe_realloc

#endif // Header Guard
