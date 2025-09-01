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

#ifndef ZAKAROUF__ZTYPES_TYPES__OPTION_H
#define ZAKAROUF__ZTYPES_TYPES__OPTION_H

#include "enum.h"

typedef z__Enum__PRIV__mapArgGlobal_to_C_Enum((Some), (None)) Option__Tags;
#define z__Option(Name, ...)\
    z__Enum__PRIV__onlytype(\
        Option__##Name,\
        Option__Tags,\
            (Some, __VA_ARGS__),\
            (None)\
        )

#define z__OptionType(Name)      Option__##Name
#define z__Some(Name, ...)  z__Enum_grave(Option__##Name, Some, __VA_ARGS__)
#define z__None(Name)       z__Enum_grave(Option__##Name, None)

#define z__SomeChip(Op, ...) z__Enum_chip(Op, Some, __VA_ARGS__)
#define z__NoneChip(Op, ...) z__Enum_chip(Op, None, __VA_ARGS__)

#define z__Option_unwrap_or(op, or)\
    ({\
        z__typeof(res) _z__unwrap_or__var__R = op;\
        (z__Enum_matches(_z__unwrap_or__var__R, Some)? _z__unwrap_or__var__R.data.Some._0 : or);\
    })

#endif

