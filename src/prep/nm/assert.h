#ifndef ZAKAROUF__ZPREP_NM_ASSERT_H
#define ZAKAROUF__ZPREP_NM_ASSERT_H

#define zpp__assert_exp(exp)\
    ((void) ((exp) ? 1 : 0)

#define zpp__assert_construct(exp, exception_method_fn, ...)\
    ( (void)( (exp) ? ((void)0) : exception_method_fn(__VA_ARGS__) ))

#define zpp__assert_not_construct(exp, exception_method_fn, ...)\
    ( (void)( (exp) ? exception_method_fn(__VA_ARGS__) : ((void)0) ))

#define zpp__assert_eq_ptr(x, y) ( x==y )
#define zpp__assert_nullptr(x) (x==NULL)
          
// Panic

#define zpp__panicif_construct(condition, panic_call, ...) zpp__assert_not_construct(condition, panic_call, __VA_ARGS__)

#define zpp__static_assert(exp) _Static_assert(exp, #exp)
#define zpp__static_assert_msg(exp, msg) _Static_assert(exp, #exp ":" msg)

#endif

