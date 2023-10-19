#ifndef ZAKAROUF__ZTYPES_TYPES__FNPTR_H
#define ZAKAROUF__ZTYPES_TYPES__FNPTR_H

#include "typeof.h"

#define z__fnptr_fn(fn) z__typeof(fn)*
#define z__fnptr(Name, T, ...) T(*Name)(__VA_ARGS__)
#define z__fnptr_call(fptr, defrval, ...) (fptr != NULL? (*fptr)(__VA_ARGS__) : defrval)

#endif

