#ifndef ZAKAROUF__ZTYPES_TYPES__MEMl_H
#define ZAKAROUF__ZTYPES_TYPES__MEMl_H

#include "../config.h"
#include "base.h"

void *z__mem_safe_realloc(void * data, size_t size);

#ifdef Z___TYPE_CONFIG__USE_MEM__TRACK

    void z__mem_init(void);
    void z__mem_end(void);
    z__ptr z__mem_tmalloc(z__size sz);
    z__ptr z__mem_tcalloc(z__size count ,z__size sz);
    void z__mem_tfree(z__ptr mem);
    z__u32 z__mem_checkfor_usedMemory(void);

    #define z__tMALLOC   z__mem_tmalloc
    #define z__tREALLOC  realloc
    #define z__tCALLOC   z__mem_tcalloc
    #define z__tFREE     z__mem_tfree

    #ifdef Z___TYPE_CONFIG__USE_MEM__VTRACK

        extern void * (*_Z__MEM_LOG_FN_PTR_)(char const *, char const *, char const *, int const, void *);
        void *z__mem_logSet(void * (*newfnptr)(char const *, char const *, char const *, int const, void *));

        #define z__tvMALLOC(s)      _Z__MEM_LOG_FN_PTR_("Malloc: " ,__FILE__, __func__, __LINE__, z__tMALLOC(s));
        #define z__tvCALLOC(c, s)   _Z__MEM_LOG_FN_PTR_("Calloc: " ,__FILE__, __func__, __LINE__, z__tMALLOC(c, s));
        #define z__tvFREE(ptr)      _Z__MEM_LOG_FN_PTR_("Free:   " ,__FILE__, __func__, __LINE__, ptr); z__tFREE(ptr)

    #endif

    #ifdef Z___TYPE_CONFIG__USE_MEM__TRACK_AS_DEFAULT

        #define z__MALLOC    z__tMALLOC   
        #define z__REALLOC   z__tREALLOC  
        #define z__CALLOC    z__tCALLOC   
        #define z__FREE      z__tFREE     

    #endif
#endif



/* fallback */
#ifndef z__MALLOC
    #define z__MALLOC   malloc
#endif
#ifndef z__REALLOC
    #define z__REALLOC  realloc
#endif
#ifndef z__CALLOC
    #define z__CALLOC   calloc
#endif
#ifndef z__FREE
    #define z__FREE     free
#endif
#ifndef z__REALLOC_SAFE
    #define z__REALLOC_SAFE z__mem_safe_realloc
#endif

#endif