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

#ifndef ZAKAROUF_DYLIB_H
#define ZAKAROUF_DYLIB_H

#if defined(_WIN32) || defined(_WIN64)
    #define Z__DYLIB_USE_WINDOWS
#elif defined(__linux__)
    #define Z__DYLIB_USE_DLFNC
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
        #error "dylib.h does not support _"
    #else
        #error "dylib.h does not support _"
    #endif
#elif defined(__unix__)
    #define Z__DYLIB_USE_DLFNC
#else
    #error "dylib.h does not support this system (Unknown)"
#endif

void *z__dylib_load(const char *_path, int MODE);
void *z__dylib_fn(void *lib, const char *_name);
void  z__dylib_close(void *lib);

#ifdef Z__IMPLEMENTATION

#if defined (Z__DYLIB_USE_DLFNC)
#include <dlfcn.h>

void *z__dylib_load(const char *_path, int MODE) { 
    return dlopen(_path, MODE); }

void z__dylib_close(void *lib) { dlclose(lib); }

void *z__dylib_fn(void *lib, const char *restrict fn) { 
    return dlsym(lib, fn); }

#elif defined(Z__DYLIB_USE_WINDOWS)
#include <windows.h>
void *z__dylib_load(const char *_path, int MODE) { 
    return LoadLibrary(_path); }

void z__dylib_close(void *lib) { FreeLibrary(lib); }

void *z__dylib_fn(void *lib, const char *restrict fn) { 
    return GetProcAddress(lib, fn); }

#endif // System Specific

#endif // Z__IMPLEMENTATION
#endif

