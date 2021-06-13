#ifndef ZAKAROUF__ZTYPES_TYPES__RESULT_H
#define ZAKAROUF__ZTYPES_TYPES__RESULT_H

#include "enum.h"

typedef z__Enum__PRIV__mapArgGlobal_to_C_Enum((Ok), (Err)) Result__Tags;
#define z__Result(Name, T, E)\
    z__Enum__PRIV__onlytype(\
        Result__##Name,\
        Result__Tags,\
            (Ok, T),\
            (Err, E)\
        )



#define z__ResultType(Name) Result__##Name
#define z__Ok(Name, ...) z__Enum_grave(Result__##Name, Ok, __VA_ARGS__)
#define z__Err(Name, ...) z__Enum_grave(Result__##Name, Err, __VA_ARGS__)


#endif

