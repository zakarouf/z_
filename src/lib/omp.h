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

#ifndef ZAKAROUF__Z__PROC_OMP_H
#define ZAKAROUF__Z__PROC_OMP_H

#include "prep/nm/pragma.h"
#include <omp.h>

#define z__omp(...) zpp__pragma(omp __VA_ARGS__)

#define z__omp_parallel(...) z__omp(parallel __VA_ARGS__)
#define z__omp_for(...) z__omp(for __VA_ARGS__)



#endif
