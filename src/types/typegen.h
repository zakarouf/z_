#ifndef ZAKAROUF__ZTYPES_TYPES__TYPEGEN_H
#define ZAKAROUF__ZTYPES_TYPES__TYPEGEN_H

#include "../prep/map.h"
#include "../prep/args.h"

#define z__PRIV__typegen_def_map(V) zpp__PRIV__Args_get_1 V: zpp__Args_skip_1 V,
#define z__typegen_def(A, defaultVal, P, ...)\
    _Generic(A,                     \
        zpp__Args_map(z__PRIV__typegen_def_map, __VA_ARGS__)  \
        default: defaultVal) P

#endif

