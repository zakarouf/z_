#ifndef ZAKAROUF__ZTYPES_TYPES__BASE_UTIL_H
#define ZAKAROUF__ZTYPES_TYPES__BASE_UTIL_H


#define z__util_hasOppositeSign(x, y) ((x ^ y) < 0)
#define z__util_isPowOf2(x) !(x & (x - 1))

#define z__util_min(x, y)\
    ({\
        z__typeof(x) tmpx = x; z__typeof(y) tmpy = y;\
        tmpx > tmpy ? tmpy:tmpx;\
     })

#define z__util_max(x, y)\
    ({\
        z__typeof(x) tmpx = x; z__typeof(y) tmpy = y;\
        tmpx < tmpy ? tmpy:tmpx;\
     })




#endif

