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

