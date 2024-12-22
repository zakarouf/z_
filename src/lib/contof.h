#ifndef ZAKAROUF__ZTYPES_CONTOF_H
#define ZAKAROUF__ZTYPES_CONTOF_H

#include "typeof.h"
#include "offsetof.h"

#define z__contof(ptr, T, M) ({ \
   	const z__typeof(((T *)0)->M) * __mptr = (ptr); \
   	(T *)((char *)__mptr - z__offsetof(T, M)); })


#endif

