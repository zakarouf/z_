#ifndef ZAKAROUF__ZTYPES_TYPES__MEMl_H
#define ZAKAROUF__ZTYPES_TYPES__MEMl_H

#include "primitives.h"

void z__mem_free(void * ptr);

void *z__mem_safe_realloc(void * data, size_t size);

void z__mem_copy_right(void *data, z__u32 unit_size, z__u32 len, z__u32 index_from, z__u64 cont);
void z__mem_shift_right(void *data, z__u32 unit_size, z__u32 len, z__u32 index_from, z__u64 cont);

void z__mem_copy_left(void *data, z__u32 unit_size, z__u32 len, z__u32 index_from, z__u64 cont);
void z__mem_shift_left(void *data, z__u32 unit_size, z__u32 len, z__u32 index_from, z__u64 cont);

void* z__mem_mcopy(void const * const data, size_t size);

#ifdef Z__CONFIG__MEM_USE_MEM__TRACK

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

    #ifdef Z__CONFIG__MEM_USE_MEM__VTRACK

        void *z__mem_logSet(void * (*newfnptr)(char const *, char const *, char const *, int const, void *));
		    void *z__mem_log(const char *msg ,const char *fl, const char *fn, const int l, void *ptr);

        #define z__tvMALLOC(s)      z__mem_log("Malloc: " ,__FILE__, __func__, __LINE__, z__tMALLOC(s));
        #define z__tvCALLOC(c, s)   z__mem_log("Calloc: " ,__FILE__, __func__, __LINE__, z__tMALLOC(c, s));
        #define z__tvFREE(ptr)      z__mem_log("Free:   " ,__FILE__, __func__, __LINE__, ptr); z__tFREE(ptr)

    #endif

    #ifdef Z__CONFIG__MEM_USE_MEM__TRACK_AS_DEFAULT

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


/* Memory Funtions */

#define z__New(T, n) z__MALLOC(sizeof(T) * n)
#define z__New0(T, n) z__CALLOC(sizeof(T), n)

#define z__AutoFree(F) __attribute__((cleanup(F)))

#define z__autofree __attribute__((cleanup(z__mem_free)))

/**
 */
#define z__MEMCPY(to, from, size) memcpy(to, from, size)
#define z__MCOPY(p, size) z__MEMCPY(z__MALLOC(size), p, size);

/** Bit Arr functions **/

#define z__BIT_SIZE_DETERMINE_FOR_BYTES(x) ((x >> 3) + 1)

#define z__BITMALLOC(x) z__MALLOC(z__BIT_SIZE_DETERMINE_FOR_BYTES(x))
#define z__BITCALLOC(x, y) z__CALLOC(z__BIT_SIZE_DETERMINE_FOR_BYTES(x), y)
#define z__BITREALLOC(ptr, newsize) z__REALLOC(ptr, z__BIT_SIZE_DETERMINE_FOR_BYTES(newsize))

#endif
