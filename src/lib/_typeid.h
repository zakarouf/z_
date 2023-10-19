#ifndef ZAKAROUF__ZTYPES_TYPEID_H
#define ZAKAROUF__ZTYPES_TYPEID_H

#include "std/primitives.h"
#include "vector.h"
#include "matrix.h"
#include "arr.h"
#include "string.h"
#include "dynt.h"
#include "irrg.h"

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
		__builtin_choose_expr(z__type_isequal(T, z__StringList), 21, \
		__builtin_choose_expr(z__type_isequal(T, z__StringListArr), 22, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__ptr), 23, \
		__builtin_choose_expr(z__type_isequal(T, z__Dynt), 24, \
			\
		__builtin_choose_expr(z__type_isequal(T, char[]),    25, \
		__builtin_choose_expr(z__type_isequal(T, const char*),   26,  \
			\
		__builtin_choose_expr(z__type_isequal(T, z__Vector2), 31, \
		__builtin_choose_expr(z__type_isequal(T, z__Vector3), 32, \
		__builtin_choose_expr(z__type_isequal(T, z__Vector4), 33, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__Vint2), 34, \
		__builtin_choose_expr(z__type_isequal(T, z__Vint3), 35, \
		__builtin_choose_expr(z__type_isequal(T, z__Vint4), 36, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__Matrix2), 37, \
		__builtin_choose_expr(z__type_isequal(T, z__Matrix3), 38, \
		__builtin_choose_expr(z__type_isequal(T, z__Matrix4), 39, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__Mint2), 40, \
		__builtin_choose_expr(z__type_isequal(T, z__Mint3), 41, \
		__builtin_choose_expr(z__type_isequal(T, z__Mint4), 42, \
			\
		__builtin_choose_expr(z__type_isequal(T, z__ivec2), 	51, \
		__builtin_choose_expr(z__type_isequal(T, z__ivec3), 	52, \
		__builtin_choose_expr(z__type_isequal(T, z__ivec4), 	53, \
		__builtin_choose_expr(z__type_isequal(T, z__vec2), 		54, \
		__builtin_choose_expr(z__type_isequal(T, z__vec3), 		55, \
		__builtin_choose_expr(z__type_isequal(T, z__vec4), 		56, \
		__builtin_choose_expr(z__type_isequal(T, z__versor), 	57, \
		__builtin_choose_expr(z__type_isequal(T, z__mat2), 		58, \
		__builtin_choose_expr(z__type_isequal(T, z__mat3), 		59, \
		__builtin_choose_expr(z__type_isequal(T, z__mat4), 		60, \
		\
		__builtin_choose_expr(sizeof(T) == 1, 19, \
		__builtin_choose_expr(sizeof(T) == 2, 1, \
		(0)  )))))))))))))))))))))))))))))))))))))))))))))))))) // wtf? just no


#endif

