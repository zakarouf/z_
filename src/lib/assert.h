#ifndef ZAKAROUF__Z__ASSERT_H
#define ZAKAROUF__Z__ASSERT_H

#include "prep/nm/assert.h"
#include "sys.h"

#define z__assert(exp)\
	(zpp__assert_construct(exp \
		, z__exit, -1, __FILE__":%d:%s\n" \
			"Assersion Failed: '%s'\n", __LINE__, __func__, #exp))

#define z__assert_eq(a, b) z__assert(a == b)
#define z__assert_noteq(a, b) z__assert(!(a == b))
#define z__assert_nullptr(a) z__assert((a == NULL))

#endif

