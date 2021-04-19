#ifndef ZAKAROUF_Z__EXP_H
#define ZAKAROUF_Z__EXP_H

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