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

#ifndef ZAKAROUF__ZTYPES_TYPES__FNPTR_H
#define ZAKAROUF__ZTYPES_TYPES__FNPTR_H

#include "typeof.h"

#define z__fnptr_fn(fn) z__typeof(fn)*
#define z__fnptr(Name, T, ...) T(*Name)(__VA_ARGS__)
#define z__fnptr_call(fptr, defrval, ...) (fptr != NULL? (*fptr)(__VA_ARGS__) : defrval)

#endif

