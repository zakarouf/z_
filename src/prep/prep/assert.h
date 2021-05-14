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


// Condtionals
#define zpp__doif_construct_pre(condition, method, ...)\
    if(condition)\
        for(int keep = 1 ; keep?({ method(__VA_ARGS__); 1; }):0 ; keep ^= 1)

#define zpp__doif_construct_post(condition, method, ...)\
    if(condition)\
        for(int keep = 1; keep; keep ^= 1, method(__VA_ARGS__) )

#define zpp__ter__if(exp)   (exp)?
#define zpp__ter__elif(exp) :(exp)?
#define zpp__ter__else      :

#define zpp__ter__op_if(exp)          zpp__ter__if(exp)   (
#define zpp__ter__op_elif(exp)      ) zpp__ter__elif(exp) (
#define zpp__ter__op_else           ) zpp__ter__else      (
#define zpp__ter__op_endif          )
          
// Panic

#define zpp__panicif(condition)\
        if(condition)\


#endif
