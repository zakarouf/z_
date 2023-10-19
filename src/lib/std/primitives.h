#ifndef ZAKAROUF__ZTYPES_BASE_H
#define ZAKAROUF__ZTYPES_BASE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#ifdef Z__CONFIG__PRIMITIVES_USE_MACRO_TYPE_CONVERTOR
#undef Z__CONFIG__PRIMITIVES_USE_MACRO_TYPE_CONVERTOR
#else
#define Z__CONFIG__PRIMITIVES_USE_MACRO_TYPE_CONVERTOR
#endif

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

#define z__cast(T, val) ((T)(val))

#ifdef Z__CONFIG__PRIMITIVES_USE_MACRO_TYPE_CONVERTOR
// Type config_types
#define z__i8(v) ((z__i8)(v))
#define z__i16(v) ((z__i16)(v))
#define z__i32(v) ((z__i32)(v))
#define z__i64(v) ((z__i64)(v))

#define z__u8(v) ((z__u8)(v))
#define z__u16(v) ((z__u16)(v))
#define z__u32(v) ((z__u32)(v))
#define z__u64(v) ((z__u64)(v))

#define z__int(v) ((z__int)(v))
#define z__float(v) ((z__float)(v))
#define z__byte(v)  ((z__byte)(v))
#define z__bool(v)  ((z__bool)(v))
#define z__ptr(v) ((z__ptr)(v))

#define z__size(v) ((z__size)(v))

#endif


#endif // Header Guard
