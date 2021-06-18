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

/*---------------------FMT-----------------------*/

#define z__ANSIFMT__PRIV__FMT__C__plain(...)      "0"
#define z__ANSIFMT__PRIV__FMT__C__reset(...)      ""
#define z__ANSIFMT__PRIV__FMT__C__bold(...)       "1"
#define z__ANSIFMT__PRIV__FMT__C__dim(...)        "2"
#define z__ANSIFMT__PRIV__FMT__C__italic(...)     "3"
#define z__ANSIFMT__PRIV__FMT__C__underline(...)  "4"
#define z__ANSIFMT__PRIV__FMT__C__blink(...)      "5"
#define z__ANSIFMT__PRIV__FMT__C__reverse(...)    "7"
#define z__ANSIFMT__PRIV__FMT__C__invisible(...)  "8"
#define z__ANSIFMT__PRIV__FMT__C__strike(...)     "9"
#define z__ANSIFMT__PRIV__FMT__C__lit(...)         __VA_ARGS__

#define z__ANSIFMT__PRIV__FMT__C__no(...) "2" zpp__CAT(z__ANSIFMT__PRIV__FMT__C__, zpp__PRIV__Args_get_1(__VA_ARGS__))("")

#define z__ANSIFMT__PRIV__FMT__C__cl256(...)\
    "38;5;" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) ";"\
    "48;5;" zpp__TO_STRING(zpp__PRIV__Args_get_1(zpp__Args_skip_1(__VA_ARGS__)))

#define z__ANSIFMT__PRIV__FMT__C__cl256_fg(...)\
    "38;5;" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__))

#define z__ANSIFMT__PRIV__FMT__C__cl256_bg(...)\
    "48;5;" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__))

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

/*---------------------SCR-----------------------*/

#define z__ANSISCR__PRIV__SCR__C__cur_show(...)         "?25h"
#define z__ANSISCR__PRIV__SCR__C__cur_hide(...)         "?25l"

#define z__ANSISCR__PRIV__SCR__C__clr(...)          "2J"
#define z__ANSISCR__PRIV__SCR__C__clr_toend(...)    "0J"
#define z__ANSISCR__PRIV__SCR__C__clr_tostart(...)  "1J"

#define z__ANSISCR__PRIV__SCR__C__clrln(...)          "2K"
#define z__ANSISCR__PRIV__SCR__C__clrln_toend(...)    "0K"
#define z__ANSISCR__PRIV__SCR__C__clrln_tostart(...)  "1K"

#define z__ANSISCR__PRIV__SCR__C__clear(...)        z__ANSISCR__PRIV__SCR__C__clr(__VA_ARGS__)
#define z__ANSISCR__PRIV__SCR__C__clear_line(...)   z__ANSISCR__PRIV__SCR__C__clrln(__VA_ARGS__)

#define z__ANSISCR__PRIV__SCR__C__jump(...)         "H"
#define z__ANSISCR__PRIV__SCR__C__jumpxy(...)\
            zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) ";"\
            zpp__TO_STRING(zpp__PRIV__Args_get_2(__VA_ARGS__)) "H"

#define z__ANSISCR__PRIV__SCR__C__up(...)         zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "A"
#define z__ANSISCR__PRIV__SCR__C__down(...)       zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "B"
#define z__ANSISCR__PRIV__SCR__C__left(...)       zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "D"
#define z__ANSISCR__PRIV__SCR__C__right(...)      zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "C"

#define z__ANSISCR__PRIV__SCR__C__up0(...)        zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "F"
#define z__ANSISCR__PRIV__SCR__C__down0(...)      zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "E"

#define z__ANSISCR__PRIV__SCR__C__column(...)     zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "G"

#define z__ANSISCR__PRIV__SCR__C__reqxy(...)    "6n"
#define z__ANSISCR__PRIV__SCR__C__save(...)     "s"
#define z__ANSISCR__PRIV__SCR__C__load(...)     "u"
#define z__ANSISCR__PRIV__SCR__C__ssave(...)    "?47h"
#define z__ANSISCR__PRIV__SCR__C__sload(...)    "?47l"

#define z__ANSISCR__PRIV__SCR__C__altbuff_on(...) "?1049h"
#define z__ANSISCR__PRIV__SCR__C__altbuff_off(...) "?1049l"

#define z__ANSISCR__PRIV__SCR__C__mode_on(...)      "=" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "h"
#define z__ANSISCR__PRIV__SCR__C__mode_off(...)     "=" zpp__TO_STRING(zpp__PRIV__Args_get_1(__VA_ARGS__)) "l"

//#define z__ANSISCR__PRIV__SCR__C__high(...)         "h"
//#define z__ANSISCR__PRIV__SCR__C__low(...)          "l"

/*---------------------------------------------------------------*/

#define z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT1(test, next) zpp__PRIV__MAP_NEXT0(test,";"  next, 0)
#define z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT(test, next)  z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT1(zpp__PRIV__MAP_GET_END test, next)

#define z__ANSIFMT__PRIV__SEMICOL_LIST0(f, x, peek, ...) f(x) z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT(peek, z__ANSIFMT__PRIV__SEMICOL_LIST1)(f, peek, __VA_ARGS__)
#define z__ANSIFMT__PRIV__SEMICOL_LIST1(f, x, peek, ...) f(x) z__ANSIFMT__PRIV__SEMICOL_LIST_NEXT(peek, z__ANSIFMT__PRIV__SEMICOL_LIST0)(f, peek, __VA_ARGS__)

#define z__ANSIFMT__PRIV__SEMICOL_LIST(f, ...) zpp__PRIV__EVAL(z__ANSIFMT__PRIV__SEMICOL_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define z__ANSIFMT_SM_LIST(f, ...) z__ANSIFMT__PRIV__SEMICOL_LIST(f, __VA_ARGS__)

#define z__ANSIFMT__PRIV__DO_FMT_MAP(of)  zpp__CAT(z__ANSIFMT__PRIV__FMT__C__, zpp__PRIV__Args_get_1 of)(zpp__Args_skip_1 of)
#define z__ANSIFMT__PRIV__DO_FMT(...) z__ANSIFMT_SM_LIST(z__ANSIFMT__PRIV__DO_FMT_MAP, __VA_ARGS__)

#define z__ANSIFMT__PRIV__FMT(...) z__ANSIFMT__PRIV__ESCAPE "[" z__ANSIFMT__PRIV__DO_FMT(__VA_ARGS__) "m"


#define z__ANSISCR__PRIV_DO_SCR_MAP(of) z__ANSIFMT__PRIV__ESCAPE "[" zpp__CAT(z__ANSISCR__PRIV__SCR__C__, zpp__PRIV__Args_get_1 of)(zpp__Args_skip_1 of)
#define z__ANSISCR__PRIV_DO_SCR(...) zpp__Args_map(z__ANSISCR__PRIV_DO_SCR_MAP, __VA_ARGS__)


#endif
