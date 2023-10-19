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
    ({                                              \
        z__typeof(number) = _temp_number = number;  \
        z__is_in_range(_temp_number, min, max);     \
    )}

#define z__abs_unsafe(number) (number>0? number : -number)
#define z__abs(number) \
    ({                                          \
        z__typeof(number) _temp_number = number;\
        z__abs_unsafe(_temp_number);            \
    })

#define z__hasOppositeSign(x, y) ((x ^ y) < 0)
#define z__isPowOf2(x) !(x & (x - 1))

#define z__cmp_ptr_data(pX, pX_len, pY, pY_len, cmpfn)\
    ((sizeof(*pX) * pX_len) == (sizeof(*pY) * pY_len))?\
        (cmpfn(pX, pY, (sizeof(*pX) * pX_len))):\
        ((int)(sizeof(*pX) * pX_len) - (int)(sizeof(*pY) * pY_len))

#endif

