#include <stdlib.h>
#include "base.h"

#ifdef Z___TYPE_CONFIG__USE_MEM

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

	#ifdef Z___TYPE_CONFIG__USE_MEM__TRACK
		/* TODO: Create Unique Sorting & Accesing Algorithm For Storing All tracked memory*/
		z__Arr(z__ptr) _z__mem_memlist;

		z__u32 z__mem_checkfor_usedMemory(void)
		{
			z__Arr(z__ptr) _memused;
			z__Arr_create(&_memused, 32);

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

			return rv;
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
			// Had to be initiated manually as `z__Arr_create` calls z__CALLOC/z__MALLOC
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
			void *_Z__MEM_LOG_FN_PTR_DEFAULT(const char *msg ,const char *fl, const char *fn, const int l, void *ptr)
			{
				fprintf(stdout, "%s >> %s:%d (%s):: %p\n", msg, fl, l, fn, ptr);
				return ptr;
			}

			void * (*_Z__MEM_LOG_FN_PTR_)(char const *, char const *, char const *, int const, void *) = _Z__MEM_LOG_FN_PTR_DEFAULT;
			void *z__mem_logSet(void * (*newfnptr)(char const *, char const *, char const *, int const, void *))
			{
			 	return (_Z__MEM_LOG_FN_PTR_ = newfnptr);
			}

		#endif

	#endif



#endif
