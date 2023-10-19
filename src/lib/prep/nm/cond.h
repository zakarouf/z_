#ifndef ZAKAROUF__ZPREP_NM_CONDITIONAL_H
#define ZAKAROUF__ZPREP_NM_CONDITIONAL_H

#include "../call.h"
#include "ident.h"
// Condtionals

#define zpp__do_construct(method1, method2)                 \
  for(int zpp__macIdent(keep) = 1;                          \
      zpp__macIdent(keep) && ({ zpp__call_raw method1; 1;});\
      zpp__macIdent(keep) = 0, zpp__call_raw method2)

#define zpp__doif_construct_onlypre(condition, method, ...)\
    if(condition)\
        for(int keep = 1 ; keep?({ method(__VA_ARGS__); 1; }):0 ; keep ^= 1)

#define zpp__doif_construct_onlypost(condition, method, ...)\
    if(condition)\
        for(int keep = 1; keep; keep ^= 1, method(__VA_ARGS__) )

#define zpp__doif_construct(condition, methodandArgs1, methodandArgs2)\
    if(condition)\
        zpp__do_construct(methodandArgs1, methodandArgs2)

#define zpp__ter__if(exp)   (exp)?
#define zpp__ter__elif(exp) :(exp)?
#define zpp__ter__else      :

#define zpp__ter__op_if(exp)          zpp__ter__if(exp)   (
#define zpp__ter__op_elif(exp)      ) zpp__ter__elif(exp) (
#define zpp__ter__op_else           ) zpp__ter__else      (
#define zpp__ter__op_endif          )



#endif
