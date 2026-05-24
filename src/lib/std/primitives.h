#ifndef ZAKAROUF__ZTYPES_BASE_H
#define ZAKAROUF__ZTYPES_BASE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <float.h>

/* Basic Types */
// Unsigned
typedef uint8_t  z__u8;
typedef uint16_t z__u16;
typedef uint32_t z__u32;
typedef uint64_t z__u64;

typedef uint_fast8_t  z__u8_f;
typedef uint_fast16_t z__u16_f;
typedef uint_fast32_t z__u32_f;
typedef uint_fast64_t z__u64_f;

// Signed
typedef int8_t  z__i8;
typedef int16_t z__i16;
typedef int32_t z__i32;
typedef int64_t z__i64;

typedef int_fast8_t  z__i8_f;
typedef int_fast16_t z__i16_f;
typedef int_fast32_t z__i32_f;
typedef int_fast64_t z__i64_f;

// Flaats
typedef float z__f32;
typedef double z__f64;

// Misc
typedef int z__int;
typedef float z__float;
typedef _Bool z__bool;
typedef void* z__ptr;
typedef z__u8 z__byte;

typedef intmax_t z__imax;
typedef uintmax_t z__umax;
typedef intptr_t z__iptr;
typedef uintptr_t z__uptr;

typedef ptrdiff_t z__ptrdiff;

#define z__sizeof sizeof
typedef size_t z__size;


/* Max Values */
#define z__i8MAX  INT8_MAX
#define z__i16MAX INT16_MAX
#define z__i32MAX INT32_MAX
#define z__i64MAX INT64_MAX

#define z__u8MAX  UINT32_MAX
#define z__u16MAX UINT32_MAX
#define z__u32MAX UINT32_MAX
#define z__u64MAX UINT64_MAX

#define z__f64MAX DBL_MAX
#define z__f64MIN DBL_MIN 

#define z__f32MAX FLT_MAX
#define z__f32MIN FLT_MIN 

#define z__sizeMAX SIZE_MAX

/* Min Values */
#define z__i8MIN  INT8_MIN
#define z__i16MIN INT16_MIN
#define z__i32MIN INT32_MIN
#define z__i64MIN INT64_MIN


#define TYPEDEFVEC(T, n) typedef T T##x##n[n]

/* 8-bit vec */
TYPEDEFVEC(z__i8, 2);
TYPEDEFVEC(z__i8, 4);
TYPEDEFVEC(z__i8, 6);
TYPEDEFVEC(z__i8, 8);
TYPEDEFVEC(z__u8, 12);
TYPEDEFVEC(z__i8, 16);

TYPEDEFVEC(z__u8, 2);
TYPEDEFVEC(z__u8, 4);
TYPEDEFVEC(z__u8, 6);
TYPEDEFVEC(z__u8, 8);
TYPEDEFVEC(z__u8, 12);
TYPEDEFVEC(z__u8, 16);


/* 16-bit vec */
TYPEDEFVEC(z__i16, 2);
TYPEDEFVEC(z__i16, 3);
TYPEDEFVEC(z__i16, 4);
TYPEDEFVEC(z__i16, 8);

TYPEDEFVEC(z__u16, 2);
TYPEDEFVEC(z__u16, 3);
TYPEDEFVEC(z__u16, 4);
TYPEDEFVEC(z__u16, 8);


/* 32-bit vec */
TYPEDEFVEC(z__i32, 2);
TYPEDEFVEC(z__i32, 3);
TYPEDEFVEC(z__i32, 4);

TYPEDEFVEC(z__u32, 2);
TYPEDEFVEC(z__u32, 3);
TYPEDEFVEC(z__u32, 4);


/* 64-bit vec */
TYPEDEFVEC(z__i64, 2);
TYPEDEFVEC(z__i64, 3);
TYPEDEFVEC(z__i64, 4);

TYPEDEFVEC(z__u64, 2);
TYPEDEFVEC(z__u64, 3);
TYPEDEFVEC(z__u64, 4);


/* floats vec */
TYPEDEFVEC(z__f32, 2);
TYPEDEFVEC(z__f32, 3);
TYPEDEFVEC(z__f32, 4);


/* double vec */
TYPEDEFVEC(z__f64, 2);
TYPEDEFVEC(z__f64, 3);
TYPEDEFVEC(z__f64, 4);

#undef TYPEDEFVEC

#define z__cast(T, val) ((T)(val))
#define z__constptr(T) (T const * const)


#endif // Header Guard
