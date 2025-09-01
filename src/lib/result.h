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

#ifndef ZAKAROUF__ZTYPES_TYPES__RESULT_H
#define ZAKAROUF__ZTYPES_TYPES__RESULT_H

#include "enum.h"

typedef z__Enum__PRIV__mapArgGlobal_to_C_Enum((Ok), (Err)) Result__Tags;
#define z__Result(Name, T, E)\
    z__Enum__PRIV__onlytype(\
        Result__##Name,\
        Result__Tags,\
            (Ok, T),\
            (Err, E)\
        )



#define z__ResultType(Name) Result__##Name
#define z__Ok(Name, ...) z__Enum_grave(Result__##Name, Ok, __VA_ARGS__)
#define z__Err(Name, ...) z__Enum_grave(Result__##Name, Err, __VA_ARGS__)

#define z__OkChip(Res, ...) z__Enum_chip(Res, Ok, __VA_ARGS__)
#define z__ErrChip(Res, ...) z__Enum_chip(Res, Err, __VA_ARGS__)

#define z__Result_unwrap_or(res, or)\
    ({\
        z__typeof(res) _z__unwrap_or__var__R = res;\
        (z__Enum_matches(_z__unwrap_or__var__R, Ok)? _z__unwrap_or__var__R.data.Ok._0 : or);\
    })


#endif

