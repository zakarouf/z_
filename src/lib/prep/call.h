#ifndef ZAKAROUF__ZPREP_CALL_H
#define ZAKAROUF__ZPREP_CALL_H

#include "args.h"

#define zpp__call_raw(x, ...) x(__VA_ARGS__)
#define zpp__call_rawalt(f, x) f x
#define zpp__call_name(x1, x, x2) zpp__CAT3(x1 ,x, x2)

#ifndef ZPP__CONFIG__NO_DOLLAR_SIGN
        #define $raw(...) zpp__call_raw(__VA_ARGS__)
        #define $rawt(f, x) zpp__call_rawalt(f, x)
        #define $name(x1, x, x2) zpp__call_name(x1, x, x2)
#endif

#endif

