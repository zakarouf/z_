#ifndef ZAKAROUF__ZTYPES_OFFSETOF_H
#define ZAKAROUF__ZTYPES_OFFSETOF_H

#if defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 5 || __GNUC__ > 3)
#define z__offsetof(T, field) __builtin_offsetof(T, field)
#else /* !(gcc >= 3.5) */
#define z__offsetof(T, field) ((size_t)(&((T *)0)->field))
#endif /* (gcc >= 3.5) */

#endif

