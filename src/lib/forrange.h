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

#ifndef ZAKAROUF_Z_IMP__FORRANGE_H
#define ZAKAROUF_Z_IMP__FORRANGE_H

#include "typeof.h"
#include "prep/args.h"

#define z__PRIV__forrange_5(iterator, init, upto, step, T)\
    for (T iterator = (init); iterator < (upto); iterator = step)
    
#define z__PRIV__forrange_4(iterator, init, upto, step)\
    z__PRIV__forrange_5(iterator, init, upto, step, size_t)

#define z__PRIV__forrange_3(iterator, init, upto)\
    z__PRIV__forrange_4(iterator, init, upto, (iterator + 1))

#define z__PRIV__forrange_2(iterator, upto)\
    z__PRIV__forrange_3(iterator, 0, upto)

/* Reverse */
#define z__PRIV__forrange_r_4(iterator, from, upto, step)\
    for (size_t iterator = from; iterator >= upto; iterator -= step)

#define z__PRIV__forrange_r_3(iterator, from, upto)\
    z__PRIV__forrange_r_4(iterator, from, upto, -1)


#define z__forrange(iterator, upto, ...)\
    zpp__Args_Overload(z__PRIV__forrange_, iterator, upto ,##__VA_ARGS__)

#define z__forrange_r(...)  zpp__Args_Overload(z__PRIV__forrange_r_, __VA_ARGS__)
#define z__forrange_t(iterator, init, upto)\
    z__forrange(iterator, init, upto, (iterator + 1), z__typeof(init))

#endif
