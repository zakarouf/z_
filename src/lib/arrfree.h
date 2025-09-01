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

#ifndef ZAKAROUF__ZTYPES_TYPES__ARRFREE_H
#define ZAKAROUF__ZTYPES_TYPES__ARRFREE_H

void z__mem_Arr_clean(void * arr);
#define z__Arrfree __attribute__((cleanup(z__mem_Arr_clean)))

#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include "std/mem.h"
#include "arr.h"

void z__mem_Arr_clean(void * arr)
{
    z__voidArr *temp = arr;
    //printf("%d, %p\n", temp->len, temp->data); // for Debug
    z__Arr_delete(temp);
}
#endif //Z__IMPLEMENTATION

#endif
