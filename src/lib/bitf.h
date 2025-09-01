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

#ifndef ZAKAROUF__ZTYPES_TYPES__BITF_H
#define ZAKAROUF__ZTYPES_TYPES__BITF_H

#include "std/primitives.h"

/**
 * Set the corresponding bit as 1 or True.
 * If the bit was already set as 1 or True, nothing happens.
 */
#define z__bit_set(b, offset)       b |= 1 << (offset)

/**
 * Set the corresponding bit as 0 or False.
 * If the bit was already set as 0 or False, nothing happens.
 */
#define z__bit_clear(b, offset)     b &= ~(1 << (offset))

/**
 * Toggle the corresponding bit value;
 * If the value is True, set it to False and vice versa.
 */
#define z__bit_toggle(b, offset)    b ^= 1 << (offset)

/**
 * Get the value of the number as a whole with only the offset bit set to 1,
 * if the corresponding bit is set to True.
 */
#define z__bit_is(b, offset)        b & (1 << (offset))

/**
 * Check if the corresponding bit is set to True.
 */
#define z__bit_has(b, offset)       (((b) >> (offset)) & 1)

/**
 * Check if value of bit in a given offset is that of the offset itself.
 */
#define z__bit_iseq(b, offset)      ((b)&(offset) == offset)


/** Bitf Interface **/


/**
 * Set the corresponding bit as 1 or True.
 * If the bit was already set as 1 or True, nothing happens.
 */
#define z__bitf_set(x, bit_num)\
    z__bit_set(z__PRIV__BITMAKE_U8IDX(x, bit_num), bit_num & 7)

/**
 * Toggle the corresponding bit value;
 * If the value is True, set it to False and vice versa.
 */
#define z__bitf_toggle(x, bit_num)\
    z__bit_toggle(z__PRIV__BITMAKE_U8IDX(x, bit_num), bit_num & 7)
/**
 * Set the corresponding bit as 0 or False.
 * If the bit was already set as 0 or False, nothing happens.
 */
#define z__bitf_clear(x, bit_num)\
    z__bit_clear(z__PRIV__BITMAKE_U8IDX(x, bit_num), bit_num & 7)
#define z__bitf_unset(x, bit_num) z__bitf_clear(x, bit_num)

/**
 * Check if the corresponding bit is set to True.
 */
#define z__bitf_has(x, bit_num)\
    z__bit_has(z__PRIV__BITMAKE_U8IDX(x, bit_num), bit_num & 7)

#define z__PRIV__BITMAKE_U8IDX(x, bit_num) *(z__cast(z__u8 *, x) + (bit_num >> 3))

/*  */

#define z__BitFieldIndex__PRIV__gen(x) x

#define z__BitField_idTagIn(Tag, in) zpp__CAT(z__BitField_idTag(Tag), in)
#define z__BitField_idTag(Tag) BF_##Tag##_

#define z__BitField_id(Tag, ...)\
        enum{ zpp__Args_maplist_fn_Pattern(z__BitFieldIndex__PRIV__gen, z__BitField_idTag(Tag),, __VA_ARGS__) }

#define z__BitField_set(of, tag, bitIndex)      z__bitf_set(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_clear(of, tag, bitIndex)    z__bitf_clear(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_toggle(of, tag, bitIndex)   z__bitf_toggle(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_is(of, tag, bitIndex)       z__bitf_is(of, z__BitField_idTagIn(tag, bitIndex))
#define z__BitField_iseq(of, tag, bitIndex)     z__bitf_iseq(of, z__BitField_idTagIn(tag, bitIndex))



#endif

