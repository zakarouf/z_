#ifndef ZAKAROUF_Z_IMP__ARGPARSE_H
#define ZAKAROUF_Z_IMP__ARGPARSE_H

#include "strto.h"

#define z__argp_next() {_priv_argp_chptr += 1; if (_priv_argp_chptr >= _priv_argp_chptrEnd)break;}
#define z__argp_get() ({*_priv_argp_chptr;})
#define z__argp_breakcheck

#define z__argp_start(argv, from, upto)\
    for(char const **_priv_argp_chptr = &argv[from]\
           , **_priv_argp_chptrEnd = &argv[upto];\
        _priv_argp_chptr < _priv_argp_chptrEnd;\
        _priv_argp_chptr += 1)

#define z__PRIV__argp_arg_check_empty_1(a)
#define z__PRIV__argp_arg_check_empty_0(a)\
    || (strcmp(a, *_priv_argp_chptr) == 0)

#define z__PRIV__argp_arg_check(a)\
    zpp__CAT(z__PRIV__argp_arg_check_empty_, zpp__Args_IS_EMPTY(a))(a)

#define z__argp_ifarg(v, ...)\
        if(strcmp(zpp__PRIV__Args_get_1(__VA_ARGS__), *_priv_argp_chptr) == 0           \
            zpp__Args_map(z__PRIV__argp_arg_check, zpp__Args_skip_1(__VA_ARGS__)) ){    \
            z__argp_next();                                                             \
            _Static_assert(sizeof(z__PRIV__strto_scan_typegen(v)) > 1, "Argparse: Strto Doesn't Support this type");\
            z__strto(*_priv_argp_chptr, v);                                             \
        }

#define z__argp_elifarg(v, ...)\
       else if(strcmp(zpp__PRIV__Args_get_1(__VA_ARGS__), *_priv_argp_chptr) == 0       \
            zpp__Args_map(z__PRIV__argp_arg_check, zpp__Args_skip_1(__VA_ARGS__)) ){    \
            z__argp_next();                                                             \
            z__strto(*_priv_argp_chptr, v);                                             \
        }


#define z__argp_ifarg_custom(...)\
        if(strcmp(zpp__PRIV__Args_get_1(__VA_ARGS__), *_priv_argp_chptr) == 0 \
            zpp__Args_map(z__PRIV__argp_arg_check, zpp__Args_skip_1(__VA_ARGS__)) )
 
#define z__argp_elifarg_custom(...)\
        else if(strcmp(zpp__PRIV__Args_get_1(__VA_ARGS__), *_priv_argp_chptr) == 0 \
            zpp__Args_map(z__PRIV__argp_arg_check, zpp__Args_skip_1(__VA_ARGS__)) )
 


#endif

