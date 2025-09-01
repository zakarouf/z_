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

#ifndef ZAKAROUF__Z__PROC_PT_ATOMIC_H
#define ZAKAROUF__Z__PROC_PT_ATOMIC_H

#define z__Atomic(T) _Atomic T

#if __STDC_VERSION__ < 201112L || __STDC_NO_ATOMICS__ == 1
    typedef z__Atomic(int) z__atomic_int;
#else
    #include <stdatomic.h>
    typedef atomic_int z__atomic_int;
#endif

#endif

