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

#ifndef ZAKAROUF_Z_IMP__RETURN_H
#define ZAKAROUF_Z_IMP__RETURN_H

#include <stdnoreturn.h>
#include "prep/base.h"

#define z__return_def(name, retval, ...)\
    goto zpp__CAT(_L_returnsk_, name);  \
    zpp__CAT(_L_return_, name): {       \
        __VA_ARGS__;                    \
        return retval;                  \
    } zpp__CAT2(_L_returnsk_, name):;

#define z__return_with(name) { goto zpp__CAT(_L_return_, name); }

#endif

