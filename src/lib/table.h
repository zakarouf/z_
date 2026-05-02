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
#include "table-old.h"

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

#define z__TablePool_new(self, size) { (self)->capacity = size;				\
									   (self)->used = 0;					\
									   (self)->indicies = z__MALLOC(sizeof( \
												   *(self)->indicies)		\
											   * (self)->capacity);			\
									   memset((self)->indicies, -1, sizeof( \
												   *(self)->indicies)		\
												   *(self)->capacity);}

#define z__TablePool_delete(self) { z__FREE((self)->indicies); }
#define z__TablePool_expand(self, by, keys, keys_len, key_hashfn, key_cmpfn, indexfn)\
	{\
		z__TablePool _old_pool = *self;\
		z__TablePool_new(self, _old_pool.capacity + by);\
		for (size_t i = 0; i < (_old_pool.capacity); i++) {\
			if(_old_pool.indicies[i] < keys_len) {\
				\
			}\
		}\
	}

#define z__TablePool_add_noexpand(self, keys, keys_len, new_key, keyhash, key_cmpfn, indexfn, index)
#define z__TablePool_add_unique_noexpand(self, keys, keys_len, new_key, keyhash, key_cmpfn, indexfn, index)

#define z__TablePool_add(self, keys, keys_len, new_key, keyhash, key_cmpfn, indexfn, index)
#define z__TablePool_add_unique(self, keys, keys_len, new_key, keyhash, key_cmpfn, indexfn, index)
#define z__TablePool_remove(self, keys, keys_len, new_key, keyhash, key_cmpfn, indexfn, success)

#define z__Table_(self)
#define z__Table_(self)
#define z__Table_(self)
#define z__Table_(self)
#define z__Table_(self)
#define z__Table_(self)


#endif
