#ifndef ZAKAROUF_Z_IMP__FORRANGE_H
#define ZAKAROUF_Z_IMP__FORRANGE_H

#include "typeof.h"
#include "prep/args.h"

#define z__PRIV__forrange_5(iterator, from, upto, step, T)\
    for (T iterator = (from); iterator < (upto); iterator += (step))
    
#define z__PRIV__forrange_4(iterator, from, upto, step)\
    z__PRIV__forrange_5(iterator, from, upto, step, size_t)

#define z__PRIV__forrange_3(iterator, from, upto)\
    z__PRIV__forrange_4(iterator, from, upto, 1)

#define z__PRIV__forrange_2(iterator, upto)\
    z__PRIV__forrange_3(iterator, 0, upto)

/* Reverse */
#define z__PRIV__forrange_r_4(iterator, from, upto, step)\
    for (size_t iterator = from; iterator >= upto; iterator -= step)

#define z__PRIV__forrange_r_3(iterator, from, upto)\
    z__PRIV__forrange_r_4(iterator, from, upto, -1)


#define z__forrange(...)    zpp__Args_Overload(z__PRIV__forrange_, __VA_ARGS__)
#define z__forrange_r(...)  zpp__Args_Overload(z__PRIV__forrange_r_, __VA_ARGS__)
#define z__forrange_t(iterator, from, upto) z__forrange(iterator, from, upto, 1, z__typeof(from))
#define z__forrange_in(iterator, from, _len) z__forrange_t(iterator, from, from + _len)

#endif
