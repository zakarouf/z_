#ifndef ZAKAROUF__ZTYPES_BASE_H
#define ZAKAROUF__ZTYPES_BASE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "../config.h"


/* Basic Types */
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
typedef z__u8 z__byte;

typedef intmax_t z__imax;
typedef uintmax_t z__umax;
typedef intptr_t z__iptr;
typedef uintptr_t z__uptr;

typedef ptrdiff_t z__ptrdiff;

#define z__sizeof sizeof
typedef size_t z__size;

#include "fnptr.h"

#endif // Header Guard
