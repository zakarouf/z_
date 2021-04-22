#ifndef ZAKAROUF__ZPREP_BASE_H
#define ZAKAROUF__ZPREP_BASE_H

#define zpp__PRIMITIVE_CAT(a, b)        a##b
#define zpp__PRIMITIVE_CAT3(a, b, c)    a##b##c
#define zpp__PRIMITIVE_CAT4(a, b, c, d) a##b##c##d

#define zpp__CAT(a, b)          zpp__PRIMITIVE_CAT(a, b) 
#define zpp__CAT3(a, b, c)      zpp__PRIMITIVE_CAT3(a, b, c) 
#define zpp__CAT4(a, b, c, d)   zpp__PRIMITIVE_CAT4(a, b, c, d) 


#define zpp__V(...) (0zpp__V, __VA_ARGS__)

#endif
