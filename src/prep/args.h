#ifndef ZAKAROUF__ZPREP_ARGS_H
#define ZAKAROUF__ZPREP_ARGS_H

#include "base.h"
#include "num.h"

#include "gen/args/get.h"
#include "gen/args/getupto.h"
#include "gen/args/skip.h"
#include "gen/args/var.h"


#define zpp__Args_HAS_COMMA(...) zpp__PRIV__VARIADICS_COUNT_AUX(__VA_ARGS__, \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                          \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                       \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                       \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                       \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                       \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                       \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                       \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                       \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                       \
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0)

#define zpp__Args_IS_EMPTY(...)\
zpp__PRIV_Args_ISEMPTY_MATCH(                                                              \
             zpp__Args_HAS_COMMA(__VA_ARGS__),                  \
             zpp__Args_HAS_COMMA(zpp__PRIV_COMMA __VA_ARGS__),     \
             zpp__Args_HAS_COMMA(__VA_ARGS__ ()),                      \
             zpp__Args_HAS_COMMA(zpp__PRIV_COMMA __VA_ARGS__ ())          \
             )

#define zpp__PRIV_Args_ISEMPTY_MATCH(_0, _1, _2, _3) zpp__Args_HAS_COMMA(zpp__CAT5(zpp__PRIV_Args_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define zpp__PRIV_Args_IS_EMPTY_CASE_0000 P00_IS_EMPTY_CASE_0000
#define zpp__PRIV_Args_IS_EMPTY_CASE_0001 ,
#define zpp__PRIV_Args_IS_EMPTY_CASE_0010 P00_IS_EMPTY_CASE_0010
#define zpp__PRIV_Args_IS_EMPTY_CASE_0011 P00_IS_EMPTY_CASE_0011
#define zpp__PRIV_Args_IS_EMPTY_CASE_0100 P00_IS_EMPTY_CASE_0100
#define zpp__PRIV_Args_IS_EMPTY_CASE_0101 P00_IS_EMPTY_CASE_0101
#define zpp__PRIV_Args_IS_EMPTY_CASE_0110 P00_IS_EMPTY_CASE_0110
#define zpp__PRIV_Args_IS_EMPTY_CASE_0111 P00_IS_EMPTY_CASE_0111
#define zpp__PRIV_Args_IS_EMPTY_CASE_1000 P00_IS_EMPTY_CASE_1000
#define zpp__PRIV_Args_IS_EMPTY_CASE_1001 P00_IS_EMPTY_CASE_1001
#define zpp__PRIV_Args_IS_EMPTY_CASE_1010 P00_IS_EMPTY_CASE_1010
#define zpp__PRIV_Args_IS_EMPTY_CASE_1011 P00_IS_EMPTY_CASE_1011
#define zpp__PRIV_Args_IS_EMPTY_CASE_1100 P00_IS_EMPTY_CASE_1100
#define zpp__PRIV_Args_IS_EMPTY_CASE_1101 P00_IS_EMPTY_CASE_1101
#define zpp__PRIV_Args_IS_EMPTY_CASE_1110 P00_IS_EMPTY_CASE_1110
#define zpp__PRIV_Args_IS_EMPTY_CASE_1111 P00_IS_EMPTY_CASE_1111



#define zpp__Args_Count(...) zpp__PRIV__VARIADICS_COUNT(__VA_ARGS__)
#define zpp__Args_Overload(N, ...) zpp__CAT(N, zpp__PRIV__VARIADICS_COUNT(__VA_ARGS__) ) (__VA_ARGS__)
#define zpp__Args_OverloadCustom zpp__PRIV__VARIADICS_COUNT_AUX


#define zpp__PRIV__Args_getupto(n, ...) zpp__CAT(zpp__PRIV__Args_getupto_, n)(__VA_ARGS__)
#define zpp__Args_getupto(n, ...) zpp__PRIV__Args_getupto(n, __VA_ARGS__)


/* zpp__Args_skip(n, ...)
 *   Skip the first `n` arguments of `...`
 */
#define zpp__PRIV__Args_skip(_of, ...) zpp__CAT(zpp__Args_skip_, _of)(__VA_ARGS__)
#define zpp__Args_skip(_of, ...) zpp__PRIV__Args_skip(_of, __VA_ARGS__)

/* zpp__Args_get(n, ...)
 * Get the `n`th argument of the vardic macro
 * zpp__PRIV__Args_get_[n] */

#define zpp__PRIV__Args_get(n, ...) zpp__CAT(zpp__PRIV__Args_get_, n)(__VA_ARGS__)
#define zpp__Args_get(n, ...) zpp__PRIV__Args_get(n, __VA_ARGS__)


// Dups  //
#define zpp__PRIV__Args_toDuplicateParenList(...) zpp__CAT(zpp__PRIV__Args_toDuplicateParen__, zpp__Args_Count(__VA_ARGS__))(__VA_ARGS__)
#define zpp__Args_toDuplicateParenList(...) zpp__PRIV__Args_toDuplicateParenList(__VA_ARGS__)

/**
 *
 */
#define zpp__PRIV__Args_Expandif_1(...)
#define zpp__PRIV__Args_Expandif_0(prefix, suffix, ...) zpp__EXPAND prefix __VA_ARGS__ zpp__EXPAND suffix
#define zpp__PRIV__Args_Expandif(prefix, suffix, ...)\
        zpp__CAT(zpp__PRIV__Args_Expandif_, zpp__Args_IS_EMPTY(__VA_ARGS__))(prefix, suffix, __VA_ARGS__)
#define zpp__Args_Expandif(prefix, suffix, ...) zpp__PRIV__Args_Expandif(prefix, suffix, __VA_ARGS__)

// Gen  //


#define zpp__PRIV__Args_toDuplicateParen__159(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__158(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__158(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__157(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__157(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__156(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__156(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__155(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__155(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__154(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__154(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__153(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__153(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__152(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__152(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__151(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__151(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__150(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__150(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__149(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__149(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__148(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__148(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__147(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__147(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__146(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__146(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__145(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__145(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__144(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__144(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__143(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__143(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__142(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__142(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__141(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__141(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__140(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__140(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__139(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__139(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__138(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__138(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__137(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__137(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__136(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__136(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__135(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__135(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__134(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__134(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__133(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__133(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__132(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__132(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__131(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__131(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__130(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__130(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__129(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__129(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__128(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__128(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__127(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__127(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__126(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__126(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__125(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__125(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__124(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__124(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__123(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__123(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__122(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__122(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__121(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__121(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__120(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__120(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__119(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__119(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__118(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__118(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__117(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__117(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__116(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__116(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__115(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__115(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__114(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__114(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__113(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__113(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__112(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__112(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__111(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__111(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__110(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__110(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__109(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__109(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__108(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__108(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__107(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__107(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__106(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__106(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__105(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__105(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__104(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__104(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__103(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__103(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__102(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__102(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__101(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__101(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__100(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__100(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__99(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__99(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__98(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__98(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__97(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__97(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__96(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__96(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__95(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__95(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__94(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__94(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__93(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__93(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__92(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__92(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__91(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__91(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__90(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__90(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__89(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__89(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__88(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__88(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__87(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__87(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__86(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__86(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__85(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__85(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__84(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__84(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__83(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__83(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__82(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__82(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__81(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__81(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__80(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__80(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__79(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__79(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__78(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__78(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__77(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__77(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__76(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__76(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__75(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__75(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__74(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__74(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__73(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__73(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__72(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__72(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__71(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__71(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__70(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__70(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__69(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__69(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__68(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__68(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__67(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__67(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__66(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__66(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__65(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__65(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__64(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__64(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__63(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__63(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__62(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__62(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__61(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__61(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__60(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__60(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__59(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__59(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__58(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__58(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__57(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__57(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__56(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__56(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__55(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__55(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__54(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__54(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__53(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__53(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__52(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__52(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__51(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__51(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__50(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__50(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__49(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__49(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__48(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__48(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__47(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__47(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__46(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__46(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__45(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__45(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__44(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__44(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__43(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__43(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__42(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__42(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__41(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__41(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__40(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__40(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__39(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__39(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__38(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__38(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__37(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__37(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__36(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__36(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__35(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__35(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__34(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__34(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__33(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__33(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__32(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__32(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__31(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__31(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__30(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__30(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__29(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__29(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__28(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__28(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__27(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__27(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__26(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__26(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__25(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__25(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__24(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__24(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__23(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__23(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__22(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__22(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__21(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__21(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__20(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__20(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__19(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__19(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__18(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__18(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__17(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__17(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__16(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__16(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__15(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__15(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__14(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__14(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__13(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__13(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__12(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__12(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__11(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__11(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__10(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__10(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__9(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__9(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__8(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__8(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__7(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__7(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__6(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__6(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__5(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__5(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__4(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__4(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__3(zpp__Args_skip_1(__VA_ARGS__))(
#define zpp__PRIV__Args_toDuplicateParen__3(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__2(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__2(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)), zpp__PRIV__Args_toDuplicateParen__1(zpp__Args_skip_1(__VA_ARGS__))
#define zpp__PRIV__Args_toDuplicateParen__1(...) (zpp__PRIV__Args_get_1(__VA_ARGS__), zpp__PRIV__Args_get_1(__VA_ARGS__)) zpp__PRIV__Args_toDuplicateParen__0(zpp__Args_skip_1(__VA_ARGS__))

#define zpp__PRIV__Args_toDuplicateParen__0(...)

#endif
