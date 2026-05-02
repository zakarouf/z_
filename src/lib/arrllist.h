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

#ifndef ZAKAROUF__Z__ARRLLIST_H
#define ZAKAROUF__Z__ARRLLIST_H

#include "std/primitives.h"
#include "std/mem.h"
#include "llist.h"
#include "arr.h"

#define z__ArrLList(TAG)\
	struct {								\
		z__LinkType(TAG) *head;				\
		z__LinkType(TAG) *tail;				\
		z__LinkType(TAG) *cursor;			\
		z__Arr(z__LinkType(TAG)) buffer;	\
		z__u64Arr unused;					\
	}


#define z__ArrLList_new(self){\
		z__Arr_new(&(self)->buffer, 16);\
		z__Arr_new(&(self)->unused, 16);\
		(self)->head = &z__Arr_getTop((self)->buffer);\
		(self)->tail = &z__Arr_getTop((self)->buffer);\
		(self)->cursor = &z__Arr_getTop((self)->buffer);\
												\
		(self)->head->_next = NULL;				\
		(self)->head->_prev = (self)->tail;		\
												\
		(self)->tail->_prev = NULL;				\
		(self)->tail->_next = (self)->head;		\
	}

#define z__ArrLList_delete(self){\
		z__Arr_delete(&(self)->buffer);\
		z__Arr_delete(&(self)->unused);\
		(self)->tail = NULL;\
		(self)->head = NULL;\
		(self)->cursor = NULL;\
	}

#define z__ArrLList_push_head(self, ...){\
		void *_arrllist_marcro_var_prev = &z__Arr_getTop((self)->buffer);\
		if(z__Arr_getUsed((self)->unused)) {					\
			(self)->head = (self)->buffer.data + z__Arr_getTop((self)->unused);	\
			z__Arr_pop(&(self)->unused);						\
		} else {												\
			z__Arr_pushInc(&(self)->buffer);					\
			(self)->head = &z__Arr_getTop((self)->buffer);		\
		}														\
		(self)->head->data = __VA_ARGS__;					\
		(self)->head->_next = NULL;							\
		(self)->head->_prev = _arrllist_marcro_var_prev;	\
		(self)->head->_prev->next = (self)->head;			\
	}

#define z__ArrLList_pop_head(self) {\
		if(z__Arr_getUsed((self)->buffer) != 0) {					\
			if(z__Arr_getUsed((self)->unused) != 0) {				\
				z__size index = (self)->head - (self)->buffer.data;	\
				if(index + 1 == z__Arr_getUsed((self)->buffer)) {	\
					(self)->buffer.lenUsed -= 1;					\
				}													\
			} else {												\
				(self)->buffer.lenUsed -= 1;						\
			}														\
		}															\
	}

#endif
