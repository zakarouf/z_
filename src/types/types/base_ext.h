#ifndef ZAKAROUF__ZTYPES_EXTENDED_H
#define ZAKAROUF__ZTYPES_EXTENDED_H

#include "../config.h"
#include "ztypes.h"
	
#define z__offsetof(T, M) ((size_t) &((T *)0)->M)

#define z__contof(ptr, T, M) ({ \
   	const z__typeof(((T *)0)->M) * __mptr = (ptr); \
   	(T *)((char *)__mptr - offsetof(T, M)); })

#define z__type_isequal(val, T) __builtin_types_compatible_p(z__typeof(val), T)
#define z__type_issame(T1, T2) 	__builtin_types_compatible_p(T1, T2)

#ifdef Z___TYPE_CONFIG__USE_TYPE_IDENTIFIER
	#define __builtin_choose_expr __builtin_choose_expr
	#define z__typeID(T) \
		__builtin_choose_expr(z__type_isequal(T, z__i16), 1, \
		__builtin_choose_expr(z__type_isequal(T, z__u16), 2, \
		__builtin_choose_expr(z__type_isequal(T, z__i32), 3, \
		__builtin_choose_expr(z__type_isequal(T, z__u32), 4, \
		__builtin_choose_expr(z__type_isequal(T, z__i64), 5, \
		__builtin_choose_expr(z__type_isequal(T, z__u64), 6, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__f32), 7, \
		__builtin_choose_expr(z__type_isequal(T, z__f64), 8, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__i8Arr), 9, \
		__builtin_choose_expr(z__type_isequal(T, z__u8Arr), 10, \
		__builtin_choose_expr(z__type_isequal(T, z__i16Arr), 11, \
		__builtin_choose_expr(z__type_isequal(T, z__u16Arr), 12, \
		__builtin_choose_expr(z__type_isequal(T, z__i32Arr), 13, \
		__builtin_choose_expr(z__type_isequal(T, z__u32Arr), 14, \
		__builtin_choose_expr(z__type_isequal(T, z__i64Arr), 15, \
		__builtin_choose_expr(z__type_isequal(T, z__u64Arr), 16, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__f32Arr), 17, \
		__builtin_choose_expr(z__type_isequal(T, z__f64Arr), 18, \
			\
			\
		__builtin_choose_expr(z__type_isequal(T, z__char), 19, \
		__builtin_choose_expr(z__type_isequal(T, z__String), 20, \
		__builtin_choose_expr(z__type_isequal(T, z__StringLines), 21, \
		__builtin_choose_expr(z__type_isequal(T, z__StringLinesArr), 22, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__ptr), 23, \
		__builtin_choose_expr(z__type_isequal(T, z__Dynt), 24, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__Vector2), 25, \
		__builtin_choose_expr(z__type_isequal(T, z__Vector3), 26, \
		__builtin_choose_expr(z__type_isequal(T, z__Vector4), 27, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__Vint2), 28, \
		__builtin_choose_expr(z__type_isequal(T, z__Vint3), 29, \
		__builtin_choose_expr(z__type_isequal(T, z__Vint4), 30, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__Matrix2), 31, \
		__builtin_choose_expr(z__type_isequal(T, z__Matrix3), 32, \
		__builtin_choose_expr(z__type_isequal(T, z__Matrix4), 33, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__Mint2), 33, \
		__builtin_choose_expr(z__type_isequal(T, z__Mint3), 34, \
		__builtin_choose_expr(z__type_isequal(T, z__Mint4), 35, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__ivec2), 	41, \
		__builtin_choose_expr(z__type_isequal(T, z__ivec3), 	42, \
		__builtin_choose_expr(z__type_isequal(T, z__ivec4), 	43, \
		__builtin_choose_expr(z__type_isequal(T, z__vec2), 		44, \
		__builtin_choose_expr(z__type_isequal(T, z__vec3), 		45, \
		__builtin_choose_expr(z__type_isequal(T, z__vec4), 		46, \
		__builtin_choose_expr(z__type_isequal(T, z__versor), 	47, \
		__builtin_choose_expr(z__type_isequal(T, z__mat2), 		48, \
		__builtin_choose_expr(z__type_isequal(T, z__mat3), 		49, \
		__builtin_choose_expr(z__type_isequal(T, z__mat4), 		50, \
		__builtin_choose_expr(sizeof(T) == 1, 19, \
		__builtin_choose_expr(sizeof(T) == 2, 1, \
		(0)  )))))))))))))))))))))))))))))))))))))))))))))))) // wtf? just no

#endif

#endif