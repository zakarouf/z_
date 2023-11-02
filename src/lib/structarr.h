#ifndef ZAKAROUF__Z__STRUCTARR_H
#define ZAKAROUF__Z__STRUCTARR_H

#include "prep/args.h"
#include "prep/map.h"
#include "std/primitives.h"

#define z__PRIV__Srr_apply_fields(x) zpp__PRIV__Args_get_1 x * zpp__PRIV__Args_get_2 x;
#define z__Srr(...)\
	struct {											\
		union {											\
			void *_raw[zpp__Args_Count(__VA_ARGS__)];	\
			struct {									\
				 zpp__Args_map(							\
					z__PRIV__Srr_apply_fields			\
				  , __VA_ARGS__);						\
			};											\
		};												\
		z__size len;									\
		z__size lenUsed;								\
	}

#define z__Srr_r(...)\
	struct {											\
		union {											\
			void *_raw[zpp__Args_Count(__VA_ARGS__)];	\
			struct {									\
				__VA_ARGS__;							\
			};											\
		};												\
		z__size len;									\
		z__size lenUsed;								\
	}

#endif
