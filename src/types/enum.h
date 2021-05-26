#ifndef ZAKAROUF__ZTYPES_TYPES__ENUM_H
#define ZAKAROUF__ZTYPES_TYPES__ENUM_H

#include "tuple.h"
#include "../prep/map.h"

#define z__Enum__PRIV__Args_get_1() zpp__PRIV__Args_get_1
#define z__Enum__PRIV__Args_skip_1() zpp__Args_skip_1
#define z__Enum__PRIV__Args_HAS_COMMA() zpp__Args_HAS_COMMA

#define z__Enum__PRIV__Arg_ToTuple_1(x)\
    z__TTuple(z__Enum__PRIV__Args_skip_1()x) z__Enum__PRIV__Args_get_1()x;
#define z__Enum__PRIV__Arg_ToTuple_0(x) int x;

#define z__Enum__PRIV__Arg_ToTuple(x)\
    zpp__CAT(z__Enum__PRIV__Arg_ToTuple_, z__Enum__PRIV__Args_HAS_COMMA()x)(x)\

#define z__Enum__PRIV__TupleArgmap(...) zpp__Args_map(z__Enum__PRIV__Arg_ToTuple, __VA_ARGS__)

#define z__Enum__PRIV__FirstArgof_Param(x)\
    z__Enum__PRIV__Args_get_1()x

#define z__Enum__PRIV__mapTupleArg_to_C_Enum(...) enum{ zpp__Args_maplist(z__Enum__PRIV__FirstArgof_Param, __VA_ARGS__) }


/* Apply Function for each type of enum */
#define z__Enum__PRIV__Apply_Functions_map(x)\
    zpp__PRIV__Args_get_1 x (z__Tuple___createMember( zpp__Args_skip_1 x))\
    {\
        \
    }

#define z__Enum__PRIV__Apply_Functions(EnumType, ...) zpp__Args_map(z__Enum__PRIV__Apply_Functions_map, __VA_ARGS__)

/* More Powerful Enum Type Using Tuples
 * Usage:
 *    z__Enum(
            RawData,
                (floatData, int, float *),
                (IntData, int, int *),
                (Exception, char *)
        );
 * Pitfall: Dont have the last member have a comma
 * Example
 * z__Enum(
        Result,
            (Ok),
            (Err, char *) // <== No Comma
        );
    This is Valid
 * z__Enum(
        Result,
            (Ok),
            (Err, char *), // <== Comma
        );
    This Not Valid, Will reuslt in a error
 */
#define z__Enum(Name, ...)\
    typedef struct Name Name;\
    struct Name {\
        union {\
            z__Enum__PRIV__TupleArgmap(__VA_ARGS__)\
        } data;\
        z__i16 _in_use;\
    };\
    z__Enum__PRIV__mapTupleArg_to_C_Enum(__VA_ARGS__);\
    /* Assign Funtions */\
   // z__Enum__PRIV__Apply_Functions(EnumType, __VA_ARGS__)
    


#define z__Enum_match(en)\
        for(int keep = 1; keep; keep = 0)\
        for(z__typeof(en) *z__tmp__enum = &en; keep; keep ^= 1)\
            switch((z__tmp__enum)->_in_use)\

#define z__Enum_slot(M, ...) break; case M: { z__Tuple__toReference((z__tmp__enum)->data.M, __VA_ARGS__);
#define z__Enum_unslot }

#endif