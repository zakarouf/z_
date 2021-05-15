#ifndef ZAKAROUF__ZPREP_NM_CONDITIONAL_H
#define ZAKAROUF__ZPREP_NM_CONDITIONAL_H

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



#endif
