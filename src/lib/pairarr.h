#ifndef ZAKAROUF__ZTYPES_TYPES__PAIRARR_H
#define ZAKAROUF__ZTYPES_TYPES__PAIRARR_H

#include "std/primitives.h"
#include "std/mem.h"

#define z__PairArr(Ta, Tb)\
    struct {\
        Ta    *data_a;\
        Tb    *data_b;\
        z__u32 len, lenUsed;\
    }


#define z__PairArr_new(pa, _len)\
    {\
        (pa)->len = _len;\
        (pa)->data_a = z__MALLOC(sizeof(*(pa)->data_a) * (pa)->len);\
        (pa)->data_b = z__MALLOC(sizeof(*(pa)->data_b) * (pa)->len);\
        (pa)->lenUsed = 0;\
    }

#define z__PairArr_delete(pa)\
    {\
        z__FREE((pa)->data_a);\
        (pa)->lenUsed = 0;\
        (pa)->len = 0;\
    }

#define z__PairArr_expand(pa, by)\
    {\
        (pa)->len += by;\
        (pa)->data_a = z__REALLOC((pa)->data_a, sizeof(*(pa)->data_a) * (pa)->len);\
        (pa)->data_b = z__REALLOC((pa)->data_b, sizeof(*(pa)->data_b) * (pa)->len);\
    }

#define z__PairArr_expand_iffull(pa)\
    {\
        if((pa)->lenUsed >= (pa)->len) { z__PairArr_expand(pa, (pa)->len); }\
    }

#define z__PairArr_push_nocheck(pa, Va, Vb) \
    {                                       \
        (pa)->data_a[(pa)->lenUsed] = Va;   \
        (pa)->data_b[(pa)->lenUsed] = Vb;   \
        (pa)->lenUsed += 1;                 \
    }

#define z__PairArr_push(pa, Va, Vb)     \
    {                                   \
        z__PairArr_expand_iffull(pa);   \
        z__PairArr_push_nocheck(pa, Va, Vb);    \
    }


#endif

