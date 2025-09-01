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

#ifndef ZAKAROUF__Z__UTF_H
#define ZAKAROUF__Z__UTF_H

#include "std/primitives.h"

z__bool z__utf8_is_valid(z__u8 const *str
					   , z__size size);
z__bool z__utf8_is_ascii(z__u8 const *str
					   , z__size size);
z__size z__utf8_get_len(z__u8 const *str
					  , z__size size);


#ifdef Z__IMPLEMENTATION
inline static z__u8 _utf8_eval_codepoint(z__byte const c)
{
    z__u8 num_bytes = 1;
    if      ((c & 0xE0) == 0xC0) num_bytes = 2; // 2-byte UTF-8
    else if ((c & 0xF0) == 0xE0) num_bytes = 3; // 3-byte UTF-8
    else if ((c & 0xF8) == 0xF0) num_bytes = 4; // 4-byte UTF-8
    return num_bytes; 
}

inline static z__u8 _utf8_char_is_valid(z__byte const c)
{
    if      ((c & 0x80) == 0)    return 1; // 1-byte ASCII
    else if ((c & 0xE0) == 0xC0) return 2; // 2-byte UTF-8
    else if ((c & 0xF0) == 0xE0) return 3; // 3-byte UTF-8
    else if ((c & 0xF8) == 0xF0) return 4; // 4-byte UTF-8
    return 0; // Invalid
}

z__bool z__utf8_is_valid(z__u8 const *str
					   , z__size size)
{
    z__u8 const *str_end = str + size;
    while(_utf8_char_is_valid(*str)) { str+=1; }
    return str == str_end;
}

z__bool z__utf8_is_ascii(z__u8 const *str
					   , z__size size)
{
    z__u8 const *str_end = str + size;
    while (_utf8_char_is_valid(*str) == 1) { str+=1; }
    return str == str_end;
}

z__size z__utf8_get_len(z__u8 const *str
					  , z__size size)
{
    z__u8 const *str_end = str + size;
    z__size len = 0;
    while(str < str_end) { str += _utf8_eval_codepoint(*str); 
                           len += 1; }
    return len;
}

#endif //Z__IMPLEMENTATION
	   
#endif
