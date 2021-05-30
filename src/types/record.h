#ifndef ZAKAROUF__ZTYPES_TYPES__RECORD_H
#define ZAKAROUF__ZTYPES_TYPES__RECORD_H

#include "../config_types.h"
#include "../prep/map.h"
#include "../prep/args.h"


#define z__Record(...)\
    struct {\
        z__Record__PRIV__createMembers(__VA_ARGS__)\
    }\

#define z__Record_Tag(TagName, ...)\
    struct z__Record__PRIV__Tag__##TagName {\
        z__Record__PRIV__createMembers(__VA_ARGS__)\
    }

#define z__Record_ofTag(TagName) struct z__Record__PRIV__Tag__##TagName


// Generation  //

#define z__Record__PRIV__createMembers_map(x) zpp__Args_get(1, zpp__EXPAND x) zpp__Args_skip_1 x;
#define z__Record__PRIV__createMembers(...) zpp__Args_map(z__Record__PRIV__createMembers_map, __VA_ARGS__)


#endif

