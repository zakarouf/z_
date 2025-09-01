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

#ifndef ZAKAROUF__ZTYPES_TYPES__BASE_UTIL_H
#define ZAKAROUF__ZTYPES_TYPES__BASE_UTIL_H

#define z__xy2Dto1D(x, y, X) ((x) + ((y) * (X)))
#define z__xyz3Dto1D(x, y, z, X, Y) (z__xy2Dto1D(x, y, X) + ((z) * (X) * (Y))) 

#define z__min_unsafe(x, y) (x > y? y : x)
#define z__min(x, y)\
    ({                              \
        z__typeof(x) tmpx = x;      \
        z__typeof(y) tmpy = y;      \
        z__min_unsafe(tmpx, tmpy);  \
     })

#define z__max_unsafe(x, y) (x > y? x : y)
#define z__max(x, y)\
    ({                              \
        z__typeof(x) tmpx = x;      \
        z__typeof(y) tmpy = y;      \
        z__max_unsafe(tmpx, tmpy);  \
     })

#define z__swap(x, y)\
    {                               \
        z__typeof(x) _temp_x = x;   \
        x = y;                      \
        y = _temp_x;                \
    }

#define z__is_in_range_unsafe(number, min, max) ((number >= min) & (number <= max))
#define z__is_in_range(number, min, max)\
    ({                                                  \
        z__typeof(number) _temp_number = number;        \
        z__is_in_range_unsafe(_temp_number, min, max);  \
    )}

#define z__abs_unsafe(number) (number>0? number : -number)
#define z__abs(number) \
    ({                                          \
        z__typeof(number) _temp_number = number;\
        z__abs_unsafe(_temp_number);            \
    })

#define z__hasOppositeSign(x, y) ((x ^ y) < 0)
#define z__isPowOf2(x) !(x & (x - 1))

/* Normalize u32, between 0.0 to 1.0 in float-32 */
#define z__u32norm(u32) z__cast(z__f32, ((u32 >> 8) * (1.0f / (1U << 24))))

/* Normalize u64, between 0.0 to 1.0 in float-64 */
#define z__u64norm(u64) z__cast(z__f64, ((u64 >> 11) * (1.0 / (1ULL << 53))))



#define z__cmp_ptr_data(pX, pX_len, pY, pY_len, cmpfn)\
    ((sizeof(*pX) * pX_len) == (sizeof(*pY) * pY_len))?\
        (cmpfn(pX, pY, (sizeof(*pX) * pX_len))):\
        ((int)(sizeof(*pX) * pX_len) - (int)(sizeof(*pY) * pY_len))


/**
 * Functions
 */
#include "std/primitives.h"

z__u32 z__u64_count_digits(z__u64 number);


/** IMPLEMENTATION **/
#ifdef Z__IMPLEMENTATION
z__u32 z__u64_count_digits(z__u64 number)
{
    z__u32 count = 0;
    while(number) {
        number >>= 1;
        count += 1;
    }
    return count;
}
#endif // Z__IMPLEMENTATION 

#endif

