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

#ifndef ZAKAROUF_Z_IMP__STRTO_H
#define ZAKAROUF_Z_IMP__STRTO_H

#include "typegen.h"

#define z__PRIV__strto_scan_typegen(v)\
        z__typegen_def(*(v), "",\
                , (z__i16, "%" PRIi16)    \
                , (z__u16, "%" PRIu16)    \
                , (z__i32, "%" PRIi32)     \
                , (z__u32, "%" PRIu32)     \
                , (z__i64, "%" PRIi64)   \
                , (z__u64, "%" PRIu64)   \
                \
                , (z__f32, "%f")    \
                , (z__f64, "%lF")   \
                \
                , (char, "%c")   \
                , (char *, "%s")   \
              )

#define z__strto(str, v)\
    sscanf(str, z__PRIV__strto_scan_typegen(v), v)


#define z__String_to(str, v)\
    {\
        if(str.len)\
            z__strto(str.data, v);\
    }


#endif

