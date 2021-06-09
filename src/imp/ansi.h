#ifndef ZAKAROUF_Z_IMP__ANSI_H
#define ZAKAROUF_Z_IMP__ANSI_H


#include "../prep/base.h"
#include "../prep/args.h"
#include "../prep/map.h"

/* Formats Text */
#define z__ansi_fmt(...) z__ANSIFMT__PRIV__FMT(__VA_ARGS__)

/* Handles Screen */
#define z__ansi_scr(...) z__ANSISCR__PRIV_DO_SCR(__VA_ARGS__)


// PRIV STUFFF

#define z__ANSIFMT__PRIV__ESCAPE "\x1b"

#define z__ANSIFMT__PRIV__FMT__C__plain(...)      "0"
#define z__ANSIFMT__PRIV__FMT__C__reset(...)      ""
#define z__ANSIFMT__PRIV__FMT__C__bold(...)       "1"
#define z__ANSIFMT__PRIV__FMT__C__dim(...)        "2"
#define z__ANSIFMT__PRIV__FMT__C__italic(...)     "3"
#define z__ANSIFMT__PRIV__FMT__C__underline(...)  "4"
#define z__ANSIFMT__PRIV__FMT__C__reverse(...)    "7"

#define z__ANSIFMT__PRIV__FMT__C__no(...) "2" zpp__CAT(z__ANSIFMT__PRIV__FMT__C__, zpp__PRIV__Args_get_1(__VA_ARGS__))("")

#define z__ANSIFMT__PRIV__FMT__C__cl256(...)       "38;5;" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) ";48;5;" zpp__TO_STRING(zpp__PRIV__Args_get_1(zpp__Args_skip_1(__VA_ARGS__)))

#define z__ANSIFMT__PRIV__FMT__C__clrgb(...)\
    "38;2;" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_2(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_3(__VA_ARGS__)) ";"\
    "48;2;" zpp__TO_STRING(zpp__PRIV__Args_get_4(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_5(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_6(__VA_ARGS__))

#define z__ANSIFMT__PRIV__FMT__C__clrgb_fg(...)\
    "38;2;" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_2(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_3(__VA_ARGS__)) 

#define z__ANSIFMT__PRIV__FMT__C__clrgb_bg(...)\
    "48;2;" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_2(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_3(__VA_ARGS__))


#define z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT1(test, next) zpp__PRIV__MAP_NEXT0(test,";"  next, 0)
#define z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT(test, next)  z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT1(zpp__PRIV__MAP_GET_END test, next)

#define z__ANSIFMT__PRIV__SEMICOL_LIST0(f, x, peek, ...) f(x) z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT(peek, z__ANSIFMT__PRIV__SEMICOL_LIST1)(f, peek, __VA_ARGS__)
#define z__ANSIFMT__PRIV__SEMICOL_LIST1(f, x, peek, ...) f(x) z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT(peek, z__ANSIFMT__PRIV__SEMICOL_LIST0)(f, peek, __VA_ARGS__)

#define z__ANSIFMT__PRIV__SEMICOL_LIST(f, ...) zpp__PRIV__EVAL(z__ANSIFMT__PRIV__SEMICOL_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define z__ANSIFMT_SM_LIST(f, ...) z__ANSIFMT__PRIV__SEMICOL_LIST(f, __VA_ARGS__)

#define z__ANSIFMT__PRIV__DO_FMT_MAP(of)  zpp__CAT(z__ANSIFMT__PRIV__FMT__C__, zpp__PRIV__Args_get_1 of)(zpp__Args_skip_1 of)
#define z__ANSIFMT__PRIV__DO_FMT(...) z__ANSIFMT_SM_LIST(z__ANSIFMT__PRIV__DO_FMT_MAP, __VA_ARGS__)

#define z__ANSIFMT__PRIV__FMT(...) z__ANSIFMT__PRIV__ESCAPE "[" z__ANSIFMT__PRIV__DO_FMT(__VA_ARGS__) "m"


#define z__ANSISCR__PRIV__SCR__C__curs(...) "?25"
#define z__ANSISCR__PRIV__SCR__C__clear(...) "2J"
#define z__ANSISCR__PRIV__SCR__C__clear_line(...) "2K"
#define z__ANSISCR__PRIV__SCR__C__high(...) "h"
#define z__ANSISCR__PRIV__SCR__C__low(...) "l"
#define z__ANSISCR__PRIV__SCR__C__jump(...) "H"
#define z__ANSISCR__PRIV__SCR__C__jumpxy(...)\
            zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_2(__VA_ARGS__)) "H"

#define z__ANSISCR__PRIV__SCR__C__alt_buff(...) "?1049"

#define z__ANSISCR__PRIV_DO_SCR_MAP(of) z__ANSIFMT__PRIV__ESCAPE "[" zpp__CAT(z__ANSISCR__PRIV__SCR__C__, zpp__PRIV__Args_get_1 of)(zpp__Args_skip_1 of)
#define z__ANSISCR__PRIV_DO_SCR(...) zpp__Args_map(z__ANSISCR__PRIV_DO_SCR_MAP, __VA_ARGS__)


#endif
