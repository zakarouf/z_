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

#ifndef ZAKAROUF__ZTYPES_TYPES__TYPEGEN_H
#define ZAKAROUF__ZTYPES_TYPES__TYPEGEN_H

#include "prep/map.h"
#include "prep/args.h"

#define z__PRIV__typegen_def_map(V) zpp__PRIV__Args_get_1 V: zpp__Args_skip_1 V,
#define z__typegen_def(A, defaultVal, P, ...)\
    _Generic(A,                     \
        zpp__Args_map(z__PRIV__typegen_def_map, __VA_ARGS__)  \
        default: defaultVal) P

#endif

