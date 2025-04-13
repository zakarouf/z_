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

#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include <string.h>

void *z__mem_safe_realloc(void * data, size_t size)
{
    void *tmpdata = realloc(data, size);
    if (tmpdata != NULL)
    {
        if (tmpdata != data)
        {
            return tmpdata;
        }
    }
    return data;
}

void *z__mem_mcopy(void const * const p, size_t size)
{
	return z__MCOPY(p, size);
}

void z__mem_copy_right(void *data, z__u32 unit_size, z__u32 len, z__u32 index_from, z__u64 cont)
{
		char *src = data + (index_from * unit_size);
		char *dest = data + ((index_from + cont) * unit_size);
		
		memmove(dest, src, len * unit_size);
}

void z__mem_shift_right(void *data, z__u32 unit_size, z__u32 len, z__u32 index_from, z__u64 cont)
{
		char *src = data + (index_from * unit_size);
		char *dest = data + ((index_from + cont) * unit_size);
		
		memmove(dest, src, len * unit_size);
		memset(src, 0, cont * unit_size);
}

void z__mem_copy_left(void *data, z__u32 unit_size, z__u32 len, z__u32 index_from, z__u64 cont)
{
		char *src = data + (index_from * unit_size);
		char *dest = data + ((index_from - cont) * unit_size);
		
		memmove(dest, src, len * unit_size);
}

void z__mem_shift_left(void *data, z__u32 unit_size, z__u32 len, z__u32 index_from, z__u64 cont)
{
		char *src = data + (index_from * unit_size);
		char *dest = data + ((index_from - cont) * unit_size);
		
		memmove(dest, src, len * unit_size);
		memset(dest + (len * unit_size), 0, unit_size * cont);
}


void z__mem_free(void * ptr)
{
	free(*(void **) ptr);
}

#ifdef Z___TYPE_CONFIG__USE_MEM__TRACK

/* TODO: Create Unique Sorting & Accesing Algorithm For Storing All tracked memory*/
static z__Arr(z__ptr) _z__mem_memlist;

z__u32 z__mem_checkfor_usedMemory(void)
{
		z__Arr(z__ptr) _memused;
		z__Arr_new(&_memused, 32);

		z__ptr* _cur = _z__mem_memlist.data;

		for (int i = 0; i < _z__mem_memlist.lenUsed; ++i)
		{
			if (*_cur != NULL)
			{
				z__Arr_push(&_memused, _cur);
			}
			_cur++;
		}

		z__u32 rv = z__Arr_getUsed(_memused);
		z__Arr_delete(&_memused);

		return rv-1;
}

Z__INLINE z__u32 z__mem_push_memToList(z__ptr mem)
{
		_z__mem_memlist.data[_z__mem_memlist.lenUsed] = mem;
		return (++_z__mem_memlist.lenUsed);
}

Z__INLINE z__u32 z__mem_pop_memFromList(z__ptr mem)
{
		z__ptr *_cur = _z__mem_memlist.data;
		for (int i = 0; i < _z__mem_memlist.lenUsed; ++i)
		{
			if (*_cur == mem)
			{
				*_cur = NULL;
				return i;
			}
			_cur++;
		}
		return -1;
}

void z__mem_tfree(z__ptr mem)
{
		free(mem);
		z__mem_pop_memFromList(mem);
}


z__ptr z__mem_tmalloc(z__size sz)
{
		z__ptr rv = malloc(sz);
		z__mem_push_memToList(rv);
		return rv;
}


z__ptr z__mem_tcalloc(z__size count ,z__size sz)
{
		z__ptr rv = calloc(count, sz);
		z__mem_push_memToList(rv);
		return rv;
}

void z__mem_init(void)
{
		// Had to be initiated manually as `z__Arr_new` calls z__CALLOC/z__MALLOC
		enum { INIT_MEM = 32 };
		_z__mem_memlist.data = calloc(INIT_MEM, sizeof(*_z__mem_memlist.data));
		_z__mem_memlist.len = INIT_MEM;
		_z__mem_memlist.lenUsed = 0;
}

void z__mem_end(void)
{
		free(_z__mem_memlist.data);
		_z__mem_memlist.len = 0;
		_z__mem_memlist.lenUsed = 0;
}

#ifdef Z___TYPE_CONFIG__USE_MEM__VTRACK

#include <stdio.h>
void *_z__mem_log_default(const char *msg ,const char *fl, const char *fn, const int l, void *ptr)
{
		fprintf(stdout, "%s >> %s:%d (%s):: %p\n", msg, fl, l, fn, ptr);
		return ptr;
}


static void * (*_z__mem_log)(char const *, char const *, char const *, int const, void *) = _z__mem_log_default;
void *z__mem_log(const char *msg ,const char *fl, const char *fn, const int l, void *ptr)
{
		return _z__mem_log(msg, fl, fn, l, ptr);
}

void *z__mem_logSet(void * (*newfnptr)(char const *, char const *, char const *, int const, void *))
{
		return (_z__mem_log = newfnptr);
}

#endif

#endif
#endif

#endif
