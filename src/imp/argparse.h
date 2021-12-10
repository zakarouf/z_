#ifndef ZAKAROUF_Z_IMP__ARGPARSE_H
#define ZAKAROUF_Z_IMP__ARGPARSE_H


#include "../z__exp.h"
#include "../types/typeof.h"
#include "../types/type.h"
#include "../types/mem.h"
#include "../prep/base.h"

#define z__argp_start(argc, argv, argt)\
    { const char ** priv__argp_argv = argv; z__typeof((*argt)) *priv__argp_argt = argt; char *priv__argp_buff = z__MALLOC(2048); int priv__argp_count = argc;\
    for(int priv__argp_i = 1; priv__argp_i < argc; priv__argp_i++)\

#define z__argp_end() z__FREE(priv__argp_buff); }

#define z__args_typeID(T) \
		__builtin_choose_expr(z__type_isequal(T, z__i16), 1, \
		__builtin_choose_expr(z__type_isequal(T, z__u16), 2, \
		__builtin_choose_expr(z__type_isequal(T, z__i32), 3, \
		__builtin_choose_expr(z__type_isequal(T, z__u32), 4, \
		__builtin_choose_expr(z__type_isequal(T, z__i64), 5, \
		__builtin_choose_expr(z__type_isequal(T, z__u64), 6, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__f32), 7, \
		__builtin_choose_expr(z__type_isequal(T, z__f64), 8, \
            \
		__builtin_choose_expr(z__type_isequal(T, z__char), 9, \
        __builtin_choose_expr(z__type_isequal(T, z__char *), 10, \
			(0) ))))))))))


const char * const z__argp__PRIV__prnextfmt[]= {
    [0] = "",
    [1] = "%hi",
    [2] = "%hu",
    [3] = "%i",
    [4] = "%u",
    [5] = "%lli",
    [6] = "%llu",

    [7] = "%f",
    [8] = "%lf",
    
    [9] = "%c",
    [10] = "%s"
};

Z__INLINE void z__argp__PRIV__assign(char *argof, void *dest)
{
    char ** tmp = dest;
    *tmp = argof;
}

#define z__argp__PRIV__check_store_next(i, argv, dest, fmt)\
    { i++; if(i >= priv__argp_count) {fputs("Not Enough arguments For : " #dest, stderr);exit(EXIT_FAILURE);}\
    snprintf(priv__argp_buff, 2048,"%s%s", fmt, z__argp__PRIV__prnextfmt[ z__args_typeID( (priv__argp_argt)->dest)]);\
    __builtin_choose_expr(z__args_typeID((priv__argp_argt)->dest) != 10,\
       sscanf(argv[i], priv__argp_buff, &(priv__argp_argt)->dest),\
       z__argp__PRIV__assign((char *)argv[i], &(priv__argp_argt)->dest));\
   

#define z__argp__PRIV__check_store_togg(i, argv, dest, fmt) { (priv__argp_argt)->dest ^= 1;
#define z__argp__PRIV__check_store_cust(i, argv, dest, fmt)

#define z__argp_counter() priv__argp_i
#define z__argp_next(next)\
    priv__argp_i += next;\
    if(priv__argp_i >= priv__argp_count) {fprintf(stderr, "Not Enough Arguments\n");exit(EXIT_FAILURE);}
#define z__argp_buff() priv__argp_buff
#define z__argp_arg() priv__argp_argv[priv__argp_i]
#define z__argp_argi(counter) priv__argp_argv[counter]
#define z__argp_count() priv__argp_count

#define z__argp_check(pre_1, pre_2, name_1, name_2, store, storefmt)\
    if (!strcmp(#pre_1 #name_1, priv__argp_argv[priv__argp_i])\
    ||  !strcmp(#pre_2 #name_2, priv__argp_argv[priv__argp_i]))\
        for(int keep = 1; keep; keep = 0)\
        zpp__CAT(z__argp__PRIV__check_store_, store)(priv__argp_i, priv__argp_argv, name_2, storefmt)\
     

 
#endif

