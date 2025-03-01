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
        (pa)->data_a = z__MALLOC(\
                (sizeof((pa)->data_a) * (pa)->len)\
                + (sizeof((pa)->data_b) * (pa)->len)\
            );\
        (pa)->data_b = z__cast(void *, (pa)->data_a + (pa)->len);\
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
    }

#define z__PairArr_check_for_expand(pa)\
    {\
    }

#define z__PairArr_push(pa, Va, Vb)\
    {\
    }


#endif

