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


#endif
