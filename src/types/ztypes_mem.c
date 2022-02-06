#include <stdlib.h>
#include <string.h>
#include "mem.h"


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

z__size z__mem_memshift_right_nocheck(void *ori, z__u32 unit_size, z__u32 how_much, z__size from, z__u32 upto)
{
    char *dest = ori+ ((from + how_much) * unit_size);
    char *src = ori+ (from * unit_size);

    z__size diff = upto - from;
    memmove(dest, src, unit_size * diff);
    memset(src, 0, unit_size * unit_size);

    return diff;
}

z__size z__mem_memcopy_right_nocheck(void *ori, z__u32 unit_size, z__u32 how_much, z__size from, z__u32 upto)
{
    char *dest = ori+ ((from + how_much) * unit_size);
    char *src = ori+ (from * unit_size);

    z__size diff = upto - from;
    memmove(dest, src, unit_size * diff);

    return diff;
}


#include "arr.h"
void z__mem_Arr_clean(void * arr)
{
    z__voidArr *temp = arr;
    //printf("%d, %p\n", temp->len, temp->data); // for Debug
    z__Arr_delete(temp);
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
