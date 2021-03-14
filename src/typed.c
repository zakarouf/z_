#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "typed.h"

typedef uint32_t z__type;

/* RESERVED TYPES
 *
 * int
 * i8
 * i16
 * i32
 * i64
 * f32
 * f64
 */
typedef struct _Z__DYNAMICTYPED_TYPES_DEFAULT_ST
{
    z__Dynt *types;
    uint32_t used;
    uint32_t size;

}_z__DEF_TYPES;







z__Dynt z__Dynt_CreateNew(z__CreateDyntInfo info)
{
    return (z__Dynt){0};
}

