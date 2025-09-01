/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZAKAROUF_Z_IMP__ARGPARSE_H
#define ZAKAROUF_Z_IMP__ARGPARSE_H

#include "strto.h"

#define z__argp_next() {_priv_argp_chptr += 1; if (_priv_argp_chptr >= _priv_argp_chptrEnd)break;}
#define z__argp_get() ({*_priv_argp_chptr;})
#define z__argp_breakcheck
#define z__argp_isatend() ((_priv_argp_chptr + 1) >= _priv_argp_chptrEnd)

#define z__argp_start(argv, from, upto)\
    for(char const **_priv_argp_chptr = &argv[from]\
           , **_priv_argp_chptrEnd = &argv[upto];\
        _priv_argp_chptr < _priv_argp_chptrEnd;\
        _priv_argp_chptr += 1)

#ifdef Z__ARGPARSE_USE_STRCMP
# define z__PRIV__argp_arg_cmp(x) (strcmp(x, *_priv_argp_chptr) == 0)
#else
# define z__PRIV__argp_arg_cmp(x)\
    (strncmp(zpp__PRIV__Args_get_1 x\
           , *_priv_argp_chptr\
           , zpp__PRIV__Args_get_2 x) == 0)
#endif

#define z__PRIV__argp_arg_check_empty_1(a)
#define z__PRIV__argp_arg_check_empty_0(a)\
    || z__PRIV__argp_arg_cmp(a)

#define z__PRIV__argp_arg_check(a)\
    zpp__CAT(z__PRIV__argp_arg_check_empty_, zpp__Args_IS_EMPTY(a))(a)

#define z__argp_ifarg_custom(...)\
        if(z__PRIV__argp_arg_cmp(zpp__PRIV__Args_get_1(__VA_ARGS__))                    \
            zpp__Args_map(z__PRIV__argp_arg_check, zpp__Args_skip_1(__VA_ARGS__)) )
 
#define z__argp_elifarg_custom(...)\
        else if(z__PRIV__argp_arg_cmp(zpp__PRIV__Args_get_1(__VA_ARGS__))               \
            zpp__Args_map(z__PRIV__argp_arg_check, zpp__Args_skip_1(__VA_ARGS__)) )
 
#define z__argp_ifarg(v, ...)\
        z__argp_ifarg_custom(__VA_ARGS__) {                                             \
            z__argp_next();                                                             \
            _Static_assert(sizeof(z__PRIV__strto_scan_typegen(v)) > 1                   \
                    , "Argparse: Strto Doesn't Support this type");                     \
            z__strto(*_priv_argp_chptr, v);                                             \
        }

#define z__argp_elifarg(v, ...)\
        z__argp_elifarg_custom(__VA_ARGS__)                                             \
            z__argp_next();                                                             \
            _Static_assert(sizeof(z__PRIV__strto_scan_typegen(v)) > 1                   \
                    , "Argparse: Strto Doesn't Support this type");                     \
            z__strto(*_priv_argp_chptr, v);                                             \
        }

#endif

