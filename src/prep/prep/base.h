#ifndef ZAKAROUF__ZPREP_BASE_H
#define ZAKAROUF__ZPREP_BASE_H

#define zpp__PRIMITIVE_CAT(a, b)        a##b
#define zpp__PRIMITIVE_CAT3(a, b, c)    a##b##c
#define zpp__PRIMITIVE_CAT4(a, b, c, d) a##b##c##d

#define zpp__CAT(a, b)          zpp__PRIMITIVE_CAT(a, b) 
#define zpp__CAT3(a, b, c)      zpp__PRIMITIVE_CAT3(a, b, c) 
#define zpp__CAT4(a, b, c, d)   zpp__PRIMITIVE_CAT4(a, b, c, d) 

#define zpp__IGNORE(...)
#define zpp__EXPAND(...) __VA_ARGS__

#define zpp__if_then(cond, x, y) zpp__CAT(zpp__if_then_, cond)(x, y)
#define zpp__if_then_0(x, y) y
#define zpp__if_then_1(x, y) x


#define zpp__NOT(exp) zpp__CAT(zpp__NOT_, exp)
#define zpp__NOT_0 1 
#define zpp__NOT_1 0

#define zpp__V(...) (0zpp__V, __VA_ARGS__)

#define zpp__From(...) ({ __VA_ARGS__  })

#endif
