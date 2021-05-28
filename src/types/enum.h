#ifndef ZAKAROUF__ZTYPES_TYPES__ENUM_H
#define ZAKAROUF__ZTYPES_TYPES__ENUM_H

#include "tuple.h"
#include "../prep/map.h"

#define z__Enum__PRIV__Args_get_1() zpp__PRIV__Args_get_1
#define z__Enum__PRIV__Args_skip_1() zpp__Args_skip_1
#define z__Enum__PRIV__Args_HAS_COMMA() zpp__Args_HAS_COMMA

#define z__Enum__PRIV__Arg_ToTuple_1(x)\
    z__TTuple(z__Enum__PRIV__Args_skip_1()x) z__Enum__PRIV__Args_get_1()x;
#define z__Enum__PRIV__Arg_ToTuple_0(x) struct { int _0; } x;

#define z__Enum__PRIV__Arg_ToTuple(x)\
    zpp__CAT(z__Enum__PRIV__Arg_ToTuple_, z__Enum__PRIV__Args_HAS_COMMA()x)(x)\

#define z__Enum__PRIV__TupleArgmap(...) zpp__Args_map(z__Enum__PRIV__Arg_ToTuple, __VA_ARGS__)

#define z__Enum__PRIV__FirstArgof_Param(x)\
    z__Enum__PRIV__Args_get_1()x

#define z__Enum__PRIV__mapTupleArg_to_C_Enum(...) enum{ zpp__Args_maplist_fn_Pattern(z__Enum__PRIV__FirstArgof_Param, e, , __VA_ARGS__)}
    //zpp__Args_maplist(z__Enum__PRIV__FirstArgof_Param, ) }

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
    z__Enum__PRIV__mapTupleArg_to_C_Enum(__VA_ARGS__);  \
    typedef struct Name Name;                           \
    struct Name {                                       \
        union {                                         \
            z__Enum__PRIV__TupleArgmap(__VA_ARGS__)     \
        } data;                                         \
        z__i16 _in_use;                                 \
    };\
    /* Assign Funtions */\
    z__Enum__PRIV__Apply_Functions(Name, __VA_ARGS__)
    
    
#define z__Enum_chip(En, sl, ...)                 \
    {                                               \
        (En)->_in_use = zpp__CAT(e, sl);             \
        z__Tuple_assign(&(En)->data.sl, __VA_ARGS__); \
    }

#define z__Enum_grave(En, sl, ...)\
    zpp__From(                                                      \
        z__typeof(En) z__Enum_grave__var__tmp;                    \
        z__Enum_chip(&z__Enum_grave__var__tmp, sl, __VA_ARGS__);  \
        z__Enum_grave__var__tmp;                                    \
    )

#define z__Enum_match(en)                                       \
        for(int keep = 1; keep; keep = 0)                       \
        for(z__typeof(en) *z__tmp__enum = &en; keep; keep ^= 1) \
            switch((z__tmp__enum)->_in_use)                     \

#define z__Enum_slot(M, ...) break; case e##M: { z__Tuple__toReference((z__tmp__enum)->data.M, __VA_ARGS__);
#define z__Enum_unslot }

#ifdef Z___TYPE_CONFIG__USE_ENUM_ALIAS_MATCH_STATEMENT

    #define match(En) z__Enum_match(En)
    #define slot(Tup, ...) z__Enum_slot(Tup, __VA_ARGS__)
    #define unslot z__Enum_unslot


#endif


/*/* DEPRECATED */

/* Apply Function for each type of enum */
#define z__Enum__PRIV__Apply_Functions_parameter_if_1(...) int _0
#define z__Enum__PRIV__Apply_Functions_parameter_if_0(...) z__Tuple___createMemberList(zpp__Args_skip_1(__VA_ARGS__))

#define z__Enum__PRIV__Apply_Functions_parameter_if(...)\
    zpp__CAT(z__Enum__PRIV__Apply_Functions_parameter_if_, zpp__Args_IS_EMPTY(zpp__Args_skip_1(__VA_ARGS__)))(__VA_ARGS__)


#define z__Enum__PRIV__Apply_fn__isProto_empty_1(...) _0
#define z__Enum__PRIV__Apply_fn__isProto_empty_0(...) __VA_ARGS__

#define z__Enum__PRIV__Apply_fn__isProto_empty(...)\
    zpp__CAT(z__Enum__PRIV__Apply_fn__isProto_empty_, zpp__Args_IS_EMPTY(zpp__Args_skip_1(__VA_ARGS__)))(__VA_ARGS__)

#define z__Enum__PRIV__Apply_Functions_map(x)\
    Z__INLINE __attribute__((const)) zpp__PRIV__Args_get_1 x (z__Enum__PRIV__Apply_Functions_parameter_if x )\
    {\
        z__typeof(zpp__PRIV__Args_get_1 x (z__Enum__PRIV__Apply_fn__isProto_empty(\
            zpp__Args_getupto(\
            zpp__PRIV__DEC(zpp__Args_Count x)\
            , zpp__num_underscore158_asc())))) result;\
        \
        z__Enum_chip(&result, z__Enum__PRIV__Args_get_1()x,z__Enum__PRIV__Apply_fn__isProto_empty(\
            zpp__Args_getupto(\
            zpp__PRIV__DEC(zpp__Args_Count x)\
            , zpp__num_underscore158_asc())));\
        return result;\
    }

#define z__Enum__PRIV__Apply_Functions(EnumType, ...)\
    zpp__PRIV__Args_map__fn_Pattern(z__Enum__PRIV__Apply_Functions_map, EnumType, , __VA_ARGS__);

//#define z__Enum__PRIV__Apply_Functions(EnumType, ...) zpp__Args_map(z__Enum__PRIV__Apply_Functions_map, __VA_ARGS__)


#endif
