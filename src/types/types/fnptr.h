#ifndef ZAKAROUF__ZTYPES_TYPES__FNPTR_H
#define ZAKAROUF__ZTYPES_TYPES__FNPTR_H

#include "typeof.h"

#define z__fnptr_fn(fn) z__typeof(fn)*
#define z__fnptr(Name, T, ...) T(*Name)(__VA_ARGS__)

#endif