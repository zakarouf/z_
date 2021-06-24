#ifndef ZAKAROUF__ZTYPES_TYPES__OPTION_H
#define ZAKAROUF__ZTYPES_TYPES__OPTION_H

#include "enum.h"

typedef z__Enum__PRIV__mapArgGlobal_to_C_Enum((Some), (None)) Option__Tags;
#define z__Option(Name, ...)\
    z__Enum__PRIV__onlytype(\
        Option__##Name,\
        Option__Tags,\
            (Some, __VA_ARGS__),\
            (None)\
        )

#define z__OptionType(Name)      Option__##Name
#define z__Some(Name, ...)  z__Enum_grave(Option__##Name, Some, __VA_ARGS__)
#define z__None(Name)       z__Enum_grave(Option__##Name, None)



#endif

