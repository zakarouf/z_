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

#ifndef ZAKAROUF_SERIALIZE_H
#define ZAKAROUF_SERIALIZE_H

#include "arr.h"
#include "std/primitives.h"

z__size z__serialize(z__byteArr *bytes, void *data
				   , z__u32 unitsize, z__u32 len
				   , z__size (objserial)(z__byteArr *, void *objdata));

#ifdef Z__IMPLEMENTATION
z__size z__serialize(z__byteArr *bytes, void *data
				   , z__u32 unitsize, z__u32 len
				   , z__size (objserial)(z__byteArr *, void *objdata)) {
	z__size at = bytes->lenUsed;
	if(objserial) {
		for (size_t i = 0; i < len; i++) {
			objserial(bytes, data + (unitsize * len));
		}
	} else {
		z__Arr_pushStream(bytes, data, (unitsize * len));
	}

	return bytes->lenUsed - at;
}


#endif // Z__IMPLEMENTATION
#endif
