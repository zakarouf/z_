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

#ifndef ZAKAROUF_Z__EXPORT_H
#define ZAKAROUF_Z__EXPORT_H

#define Z__VERSION_STR "2.0.0"
#define Z__VERSION_MAJOR 2
#define Z__VERSION_MINOR 0
#define Z__VERSION_PATCH 0

#if defined(_MSC_VER)
#  ifdef Z__STATIC
#    define Z__EXPORT
#  elif defined(Z__EXPORTS)
#    define Z__EXPORT __declspec(dllexport)
#  else
#    define Z__EXPORT __declspec(dllimport)
#  endif
#  define Z__INLINE __forceinline
#else
#  define Z__EXPORT __attribute__((visibility("default")))
#  define Z__INLINE static inline __attribute((always_inline))
#endif

#endif

