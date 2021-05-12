#ifndef ZAKAROUF__ZPREP_ASSERT_H
#define ZAKAROUF__ZPREP_ASSERT_H

#define zpp__assert_exp(exp)\
    ((void) ((exp) ? 1 : 0)

#define zpp__assert_exp_method(exp, exception_method_fn, ...)\
    ((void) ((exp) ? ((void)0) : exception_method_fn (__VA_ARGS__)))

#define zpp__assert_not_exp_method(exp, exception_method_fn, ...)\
    ((void) ((exp) ? exception_method_fn (__VA_ARGS__)) : ((void)0) )

#define zpp__assert_eq_ptr(x, y) ( x==y?true:false )
#define zpp__assert_ptr_checkNULL(x) (x==NULL?true:false)

// Panic

#define zpp__panicif(condition)\
        if(condition)\



#endif
