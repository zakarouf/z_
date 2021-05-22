#ifndef ZAKAROUF__ZPREP_MAP_H
#define ZAKAROUF__ZPREP_MAP_H

#include "eval.h"

#define zpp__PRIV__MAP_END(...)
#define zpp__PRIV__MAP_OUT
#define zpp__PRIV__MAP_COMMA ,

#define zpp__PRIV__MAP_GET_END2() 0, zpp__PRIV__MAP_END
#define zpp__PRIV__MAP_GET_END1(...) zpp__PRIV__MAP_GET_END2
#define zpp__PRIV__MAP_GET_END(...) zpp__PRIV__MAP_GET_END1
#define zpp__PRIV__MAP_NEXT0(test, next, ...) next zpp__PRIV__MAP_OUT
#define zpp__PRIV__MAP_NEXT1(test, next) zpp__PRIV__MAP_NEXT0(test, next, 0)
#define zpp__PRIV__MAP_NEXT(test, next)  zpp__PRIV__MAP_NEXT1(zpp__PRIV__MAP_GET_END test, next)

#define zpp__PRIV__MAP0(f, x, peek, ...) f(x) zpp__PRIV__MAP_NEXT(peek, zpp__PRIV__MAP1)(f, peek, __VA_ARGS__)
#define zpp__PRIV__MAP1(f, x, peek, ...) f(x) zpp__PRIV__MAP_NEXT(peek, zpp__PRIV__MAP0)(f, peek, __VA_ARGS__)

#define zpp__PRIV__MAP_LIST_NEXT1(test, next) zpp__PRIV__MAP_NEXT0(test, zpp__PRIV__MAP_COMMA next, 0)
#define zpp__PRIV__MAP_LIST_NEXT(test, next)  zpp__PRIV__MAP_LIST_NEXT1(zpp__PRIV__MAP_GET_END test, next)

#define zpp__PRIV__MAP_LIST0(f, x, peek, ...) f(x) zpp__PRIV__MAP_LIST_NEXT(peek, zpp__PRIV__MAP_LIST1)(f, peek, __VA_ARGS__)
#define zpp__PRIV__MAP_LIST1(f, x, peek, ...) f(x) zpp__PRIV__MAP_LIST_NEXT(peek, zpp__PRIV__MAP_LIST0)(f, peek, __VA_ARGS__)

/*
 * Repeat function/ macro `f` equivalent to the vardic argument with each 
 * single argument is passed one-by-one at each repitation
 */
#define zpp__PRIV__MAP(f, ...) zpp__PRIV__EVAL(zpp__PRIV__MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Same as MAP but each call is seperated by a comma.
 */
#define zpp__PRIV__MAP_LIST(f, ...) zpp__PRIV__EVAL(zpp__PRIV__MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define zpp__Args_maplist(f, ...) zpp__PRIV__MAP_LIST(f, __VA_ARGS__)
#define zpp__Args_map(f, ...) zpp__PRIV__MAP(f, __VA_ARGS__)


#endif
