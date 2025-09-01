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

