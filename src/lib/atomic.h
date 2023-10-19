#ifndef ZAKAROUF__Z__PROC_PT_ATOMIC_H
#define ZAKAROUF__Z__PROC_PT_ATOMIC_H

#define z__Atomic(T) _Atomic T

#if __STDC_VERSION__ < 201112L || __STDC_NO_ATOMICS__ == 1
    typedef z__Atomic(int) z__atomic_int;
#else
    #include <stdatomic.h>
    typedef atomic_int z__atomic_int;
#endif

#endif

