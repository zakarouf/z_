/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZAKAROUF_Z__HASHSET_ORD_H
#define ZAKAROUF_Z__HASHSET_ORD_H

#include "pairarr.h"
#include "std/mem.h"

typedef struct z__TablePool z__TablePool;
struct z__TablePool {
	z__u32 *indicies;
	z__u32 capacity, used;
};

#define z__Table(K, V)\
	struct {\
		z__TablePool pool;\
		z__PairArr(K, V) array;\
	}

void z__TablePool_new(z__TablePool *self, z__u32);
void z__TablePool_delete(z__TablePool *self);


#define z__Table_new(self, pool_length, array_length)\
	{																	\
		z__TablePool_new(&(self)->pool, pool_length);					\
		z__PairArr_new(&(self)->array, array_length);					\
	}

#define z__Table_delete(self)\
	{										\
		z__PairArr_delete(&(self)->array);	\
		z__TablePool_delete(&(self)->pool); \
	}

#define z__Table_expand_array(self, by)\
	{\
		z__PairArr_expand(&(self)->array, by);\
	}

#define z__Table_indexfn(indicies, keyarray, keyarray_len, indicies_size, key, keyhash, cmpfn, index)\
	{\
		z__u32 i = keyhash % indicies_size;\
		while(indicies[i] > keyarray_len) {\
			if(cmpfn(keyarray[indicies[i]], key) == 0){break;}\
			i += 1; if(i >= indicies_size) i = 0;\
		}\
		*(index) = i;\
	}

#define z__Table_addtopool_noexpand(self, indexfn, hashfn, cmpfn, overide, n)\
	{\
		z__u32 _index = 0;						\
		indexfn((self)->pool.indicies			\
			  , (self)->array.data_a			\
			  , (self)->array.lenUsed			\
			  , (self)->pool.indicies_size, (self)->array.data_a[n]\
			  , hashfn((self)->array.data_a[n])		\
			  , cmpfn, &_index);					\
		if((self)->indicies[_index] > (self)->array.lenUsed || overide) {\
			(self)->indicies[_index] = n;	\
		}									\
		(self)->pool.used += 1;				\
	}

#define z__Table_expand_pool(self, by, indexfn, hashfn, cmpfn)\
	{\
		z__u32 new_cap = (self)->pool.capacity + by;\
		z__TablePool _old_pool = (self)->pool;\
		z__TablePool_new(&(self)->pool, new_cap);\
		for (size_t _i = 0; _i < _old_pool.capacity; _i++) {\
			if(_old_pool.indicies[i] < (self)->array.lenUsed) {\
				z__Table_addtopool_noexpand(\
					self, indexfn, hashfn, cmpfn, _old_pool.indicies[i]);\
			}\
		}\
		z__TablePool_delete(&_old_pool);\
	}


#define z__Table_addtopool(self, indexfn, hashfn, cmpfn, n)\
	{\
		if((self)->)}

#define z__Table_push_nohash(self, K, V)
#define z__Table_push_unique(self, K, V)
#define z__Table_set(self, K, V)
#define z__Table_pop(self, K, V)

#include "prep/base.h"
#define z__Table_IMPLEXT(TN, TB, K, V)\
	void	zpp__CAT3(TN, _, new)(TN *self);\
	void	zpp__CAT3(TN, _, delete)(TN *self);\
	void	zpp__CAT3(TN, _, assign_hash)(TN *self, z__u32 n);\
	void	zpp__CAT3(TN, _, push_nohash)(TN *self, K key, V value);\
	z__bool zpp__CAT3(TN, _, push)(TN *self, K key, V value);\
	void	zpp__CAT3(TN, _, set)(TN *self, K key, V, value);\
	void	zpp__CAT3(TN, _, pop)(TN *self);\

#define z__Table_IMPL(TN, TB, K, V, indexfn, hashfn, cmpfn)\
	void	zpp__CAT3(TN, _, new)(TB *self) z__Table_new(self, 8, 4)\
	void	zpp__CAT3(TN, _, delete)(TN *self) z__Table_delete(self)\
	


#ifdef Z__IMPLEMENTATION

typedef z__Table(z__u64, int) MapInt;
z__Table_IMPL(MapInt, MapInt, z__u64, int, inde, hashfn, cmpfn);

void z__TablePool_new(z__TablePool *self, z__u32 len)
{
	(self)->capacity = len;
	(self)->used = 0;
	(self)->indicies = z__MALLOC(sizeof(*(self)->indicies)
									  * (self)->capacity);
	memset((self)->indicies, -1, sizeof(*(self)->indicies)
									  * (self)->capacity);
}

void z__TablePool_delete(z__TablePool *self)
{
	z__FREE(self->indicies);
}

#endif
#endif
