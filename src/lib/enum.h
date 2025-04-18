#ifndef ZAKAROUF__ZTYPES_TYPES__ENUM_H
#define ZAKAROUF__ZTYPES_TYPES__ENUM_H

#include "_export.h"
#include "std/primitives.h"
#include "tuple.h"
#include "record.h"
#include "prep/map.h"

/**
 * Powerful Sum Type Using Tuples & Records
 * Usage:
 * z__Enum(
    WebEvent,
        // An unit-like
        (PageLoad),
        (PageUnload),

        // Like Tuple Struct
        (KeyPressed, char),
        (Paste, char *, int),

        // Or Records (Structures)
        (Click, (int, x, y))
    );
 * Pitfall: Dont have the last member have a comma
 * Example
 * The below Code is Valid
 * z__Enum(
        Result,
            (Ok),
            (Err, char *) // <== No Comma
        );
    
  Whilst This Code below is not.
 * z__Enum(
        Result,
            (Ok),
            (Err, char *), // <== Comma, Will result in Error
        );


 */
#define z__Enum(Name, ...)\
    z__EnumDef(Name, __VA_ARGS__);\
    /* Assign Funtions */\
    z__Enum__PRIV__Apply_Functions(Name, __VA_ARGS__)


/* Without the Function Generation, Rest are same */
#define z__EnumDef(Name, ...)\
    typedef z__Enum__PRIV__mapArgGlobal_to_C_Enum(__VA_ARGS__) Name##Tags;  \
    typedef struct Name Name;                               \
    struct Name {                                           \
        union {                                             \
           z__Enum__PRIV__Apply__memberMap_map(__VA_ARGS__) \
        } data;                                             \
        Name##Tags tag;                                     \
    }

#define z__Enum__PRIV__onlytype(Name, tag_T , ...)\
    typedef struct Name Name;                               \
    struct Name {                                           \
        union {                                             \
           z__Enum__PRIV__Apply__memberMap_map(__VA_ARGS__) \
        } data;                                             \
        tag_T tag;                                          \
    }

#define z__EnumBare(Name, Tag_T, ...)\
    z__Enum__PRIV__onlytype(Name, Tag_T, __VA_ARGS__)


#define z__Enum_mtag(M) zpp__CAT(ENUM_TAG__, M)


#define z__Enum_chip(En, sl, ...)                           \
    {                                                       \
        (En)->tag = zpp__CAT(ENUM_TAG__, sl);               \
        z__Enum__PRIV__chip__if(&(En)->data.sl, __VA_ARGS__); \
    }

#define z__Enum_grave(En, sl, ...)\
    zpp__From(                                                  \
        z__typeof(En) z__Enum_grave__var__tmp;                  \
        z__Enum_chip(&z__Enum_grave__var__tmp, sl, __VA_ARGS__);\
        z__Enum_grave__var__tmp;                                \
    )

#define z__Enum_match(en)                                       \
        for(int keep = 1; keep; keep = 0)                       \
        for(z__typeof(en) *z__tmp__enum = &en; keep; keep ^= 1) \
            switch((z__tmp__enum)->tag)                         \

#define z__Enum_slot(...) z__Enum__PRIV__slot__if(__VA_ARGS__)

#define z__Enum_emptyslot break; default:
#define z__Enum_unslot }

#define z__Enum_ifSlot(En, M, ...)\
        if(z__Enum_matches(En, M))\
        { z__Enum__PRIV__slot__Apply_if((&En)->data.M, __VA_ARGS__)

#define z__Enum_matches(En, M) (z__Enum_mtag(M) == (En).tag)

#ifdef Z___TYPE_CONFIG__USE_ENUM_ALIAS_MATCH_STATEMENT

    #define match(En) z__Enum_match(En)
    #define slot(...) z__Enum_slot(__VA_ARGS__)
    #define unslot z__Enum_unslot

    #define emptyslot z__Enum_emptyslot
    #define ifSlot(En, M, ...) z__Enum_ifSlot(En, M, __VA_ARGS__)

    #define matches(En, M) z__Enum_matches(En, M)

#endif

/************************************************************************
 *                                  PRIVATE                             *
 ************************************************************************/

#define z__Enum__PRIV__chip_Apply_if_0(...) z__Tuple_assign(zpp__PRIV__Args_get_1(__VA_ARGS__) ,zpp__Args_skip_1(__VA_ARGS__))
#define z__Enum__PRIV__chip_Apply_if_1(...) z__Record_assign(zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__Args_skip_1(__VA_ARGS__))

#define z__Enum__PRIV__chip_Apply_if(...) zpp__CAT(z__Enum__PRIV__chip_Apply_if_, zpp__IS_PAREN(zpp__PRIV__Args_get_2(__VA_ARGS__)))(__VA_ARGS__)

#define z__Enum__PRIV__chip__if_0(...) z__Enum__PRIV__chip_Apply_if(__VA_ARGS__) 
#define z__Enum__PRIV__chip__if_1(...)
#define z__Enum__PRIV__chip__if(...)\
    zpp__CAT(z__Enum__PRIV__chip__if_, zpp__Args_IS_EMPTY(zpp__Args_skip_1(__VA_ARGS__)))(__VA_ARGS__)

// Syntax, slot(x, (), a) <= For Tuple
// Syntax, slot(x, (a, b), (t, d))  <= For Record
#define z__Enum__PRIV__slot__Apply_if_1__record_apply_0_0(Memb, ...) z__Record_toReffrence(& Memb, __VA_ARGS__);
#define z__Enum__PRIV__slot__Apply_if_1__record_apply_0_1(Memb, ...) z__Tuple_toReference(Memb, __VA_ARGS__)

#define z__Enum__PRIV__slot__Apply_if_1__record_apply_0_check(Memb, a, ...) zpp__CAT(z__Enum__PRIV__slot__Apply_if_1__record_apply_0_,  zpp__Args_IS_EMPTY a )(Memb, __VA_ARGS__)

// Has None Nested Paren, Either Record or Tuple with a ignore first element.
#define z__Enum__PRIV__slot__Apply_if_1__record_apply_0(Memb, ...) z__Enum__PRIV__slot__Apply_if_1__record_apply_0_check(Memb, zpp__PRIV__Args_get_1(__VA_ARGS__), __VA_ARGS__)

// Create Bare Refference
#define z__Enum__PRIV__slot__Apply_if_1__record_apply_BareReff(Memb, x) z__typeof(Memb) * zpp__PRIV__Args_get_1 x = &Memb;

// Has One Nested Paren, Create Bare Refference
#define z__Enum__PRIV__slot__Apply_if_1__record_apply_1(Memb, ...) z__Enum__PRIV__slot__Apply_if_1__record_apply_BareReff(Memb, zpp__PRIV__Args_get_1(__VA_ARGS__)) 

// Check How many nested paren is there
#define z__Enum__PRIV__slot__Apply_if_1__record_apply_check(x) zpp__IS_PAREN(zpp__PRIV__Args_get_1 x)

#define z__Enum__PRIV__slot__Apply_if_1__record_apply(Memb, ...)\
    zpp__CAT(z__Enum__PRIV__slot__Apply_if_1__record_apply_, z__Enum__PRIV__slot__Apply_if_1__record_apply_check(zpp__PRIV__Args_get_1(__VA_ARGS__))) (Memb, __VA_ARGS__)

// For If not Tuples, i.e. Record or Bare
#define z__Enum__PRIV__slot__Apply_if_1(En_M, ...)   z__Enum__PRIV__slot__Apply_if_1__record_apply(En_M, __VA_ARGS__);

// For Tuples
#define z__Enum__PRIV__slot__Apply_if_0(En_M, ...)   z__Tuple_toReference(En_M, __VA_ARGS__);


// Check if It has paren, if not its a typle
#define z__Enum__PRIV__slot__Apply_if(En_M, ...)\
    zpp__CAT(z__Enum__PRIV__slot__Apply_if_, zpp__IS_PAREN(zpp__PRIV__Args_get_1(__VA_ARGS__)))(En_M, __VA_ARGS__)


// Something is Here, not Empty, check for tuple or record or Bare data.
#define z__Enum__PRIV__slot__if_0(M, ...)\
    break; case zpp__CAT(ENUM_TAG__, M): { z__Enum__PRIV__slot__Apply_if((z__tmp__enum)->data.M, __VA_ARGS__)

// Slot emply
#define z__Enum__PRIV__slot__if_1(...)\
    break; default: {

// Check slot is emply or not
#define z__Enum__PRIV__slot__if(...)\
    zpp__CAT(z__Enum__PRIV__slot__if_, zpp__Args_IS_EMPTY(__VA_ARGS__))(__VA_ARGS__)

/* Enum Generation */

#define z__Enum__PRIV__Args_get_1() zpp__PRIV__Args_get_1
#define z__Enum__PRIV__Args_skip_1() zpp__Args_skip_1
#define z__Enum__PRIV__Args_HAS_COMMA() zpp__Args_HAS_COMMA

#define z__Enum__PRIV__Arg_ToTuple_1(x)\
    z__TupleX(z__Enum__PRIV__Args_skip_1()x) z__Enum__PRIV__Args_get_1()x;
#define z__Enum__PRIV__Arg_ToTuple_0(x) char x;

#define z__Enum__PRIV__Arg_ToTuple(x)\
    zpp__CAT(z__Enum__PRIV__Arg_ToTuple_, z__Enum__PRIV__Args_HAS_COMMA()x)(x)\

#define z__Enum__PRIV__TupleArgmap(...) zpp__Args_map(z__Enum__PRIV__Arg_ToTuple, __VA_ARGS__)


#define z__Enum__PRIV__Arg_ToRecord_1__expand(...)\
    z__PRIV__Record__forEnum(__VA_ARGS__)

#define z__Enum__PRIV__Arg_ToRecord_1(x)\
    z__Enum__PRIV__Arg_ToRecord_1__expand(zpp__EXPAND x)

#define z__Enum__PRIV__Arg_ToRecord_0(x) char x;

#define z__Enum__PRIV__Arg_ToRecord(x)\
    zpp__CAT(z__Enum__PRIV__Arg_ToRecord_, z__Enum__PRIV__Args_HAS_COMMA()x)(x)\



#define z__Enum__PRIV__memberMap_of_if(x) zpp__CAT(z__Enum__PRIV__memberMap_of_if_ ,zpp__IS_PAREN(zpp__PRIV__Args_get_2 x))(x)

#define z__Enum__PRIV__memberMap_of_if_0(x) z__Enum__PRIV__Arg_ToTuple(x);
#define z__Enum__PRIV__memberMap_of_if_1(x) z__Enum__PRIV__Arg_ToRecord(x)


#define z__Enum__PRIV__Apply__memberMap_of_if(x) zpp__CAT(z__Enum__PRIV__Apply__memberMap_of_if_, zpp__Args_HAS_COMMA x)(x)

#define z__Enum__PRIV__Apply__memberMap_of_if_0(x) char x;
#define z__Enum__PRIV__Apply__memberMap_of_if_1(x) z__Enum__PRIV__memberMap_of_if(x)

#define z__Enum__PRIV__Apply__memberMap_map(...) zpp__Args_map(z__Enum__PRIV__Apply__memberMap_of_if, __VA_ARGS__)


#define z__Enum__PRIV__FirstArgof_Param(x)\
    z__Enum__PRIV__Args_get_1()x

#define z__Enum__PRIV__mapArgGlobal_to_C_Enum(...)\
    enum{ zpp__Args_maplist_fn_Pattern(z__Enum__PRIV__FirstArgof_Param, ENUM_TAG__, ,__VA_ARGS__)}
    //zpp__Args_maplist(z__Enum__PRIV__FirstArgof_Param, ) }

#define z__Enum_createTags(...)\
    enum {   }


/* Apply Function for each type of enum */

#define z__Enum__PRIV__GEN__fn__Record__createArgList(x) zpp__Args_skip_1 x
#define z__Enum__PRIV__GEN__fn__Record__createArgList_map(...) zpp__Args_maplist(z__Enum__PRIV__GEN__fn__Record__createArgList, __VA_ARGS__)

#define z__Enum__PRIV__GEN__fn__Record(x)\
    Z__INLINE __attribute__((const)) zpp__PRIV__Args_get_1 x (z__Enum__PRIV__GEN__fn__Record__createArgList_map(zpp__Args_skip_1 x))\
    z__PRIV__Record__forEnum_createMembers(zpp__Args_skip_1 x)  \
    {                                                           \
        z__typeof(zpp__PRIV__Args_get_1 x (                     \
                    z__Enum__PRIV__GEN__fn__Record__createArgList_map(\
                        zpp__Args_skip_1 x)) ) result;\
        z__Enum_chip(&result, zpp__PRIV__Args_get_1 x,                                              \
                zpp__Args_toDuplicateParenList( \
                    z__Enum__PRIV__GEN__fn__Record__createArgList_map(zpp__Args_skip_1 x) ));\
        return result;                                                                              \
    }

#define z__Enum__PRIV__GEN__fn__Tuple(x)\
    Z__INLINE __attribute__((const)) zpp__PRIV__Args_get_1 x (z__Tuple___createMemberList(zpp__Args_skip_1 x))\
    {                                                           \
        z__typeof( zpp__PRIV__Args_get_1 x (                    \
                    zpp__Args_getupto(                          \
                        zpp__PRIV__DEC(zpp__Args_Count x),      \
                        zpp__num_underscore158_asc()) )) result;\
                                                                \
        z__Enum_chip(&result, zpp__PRIV__Args_get_1 x,          \
                zpp__Args_getupto(                              \
                    zpp__PRIV__DEC(zpp__Args_Count x),          \
                    zpp__num_underscore158_asc()));             \
        return result;                                          \
    }

#define z__Enum__PRIV__GEN__fn__Unit(x)\
    Z__INLINE __attribute__((const)) zpp__PRIV__Args_get_1 x () \
    {                                                           \
        z__typeof(zpp__PRIV__Args_get_1 x () ) result;          \
        z__Enum_chip(&result, zpp__PRIV__Args_get_1 x);         \
        return result;                                          \
    }

#define z__Enum__PRIV__GEN__fn__either_record_or_tuple_if_0(x) z__Enum__PRIV__GEN__fn__Tuple(x)
#define z__Enum__PRIV__GEN__fn__either_record_or_tuple_if_1(x) z__Enum__PRIV__GEN__fn__Record(x)

#define z__Enum__PRIV__GEN__fn__either_record_or_tuple_if(x)\
    zpp__CAT(z__Enum__PRIV__GEN__fn__either_record_or_tuple_if_, zpp__IS_PAREN(zpp__PRIV__Args_get_2 x))(x)


#define z__Enum__PRIV__Apply_Functions_check_if_0(x) z__Enum__PRIV__GEN__fn__Unit(x)
#define z__Enum__PRIV__Apply_Functions_check_if_1(x) z__Enum__PRIV__GEN__fn__either_record_or_tuple_if(x)

#define z__Enum__PRIV__Apply_Functions_check_if(x)\
    zpp__CAT(z__Enum__PRIV__Apply_Functions_check_if_, zpp__Args_HAS_COMMA x)(x)
 
#define z__Enum__PRIV__Apply_Functions(EnumType, ...)\
    zpp__PRIV__Args_map__fn_Pattern(z__Enum__PRIV__Apply_Functions_check_if, EnumType, , __VA_ARGS__);



#endif
