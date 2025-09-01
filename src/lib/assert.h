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

