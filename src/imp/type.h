#ifndef ZAKAROUF_Z_IMP__TYPE_H
#define ZAKAROUF_Z_IMP__TYPE_H

#include "../types/type.h"
#include "../types/typeid.h"
#include "../types/typegen.h"
#include "../types/typeof.h"

enum {
    _Z__PRIV__TYPE_M_ATOM_INT = 0x01,
    _Z__PRIV__TYPE_M_ATOM_FLOAT,
    _Z__PRIV__TYPE_M_VECTOR,
    _Z__PRIV__TYPE_M_MATRIX,
    _Z__PRIV__TYPE_M_PRIM_ARR,
    _Z__PRIV__TYPE_M_PRIM_ARR_FLOAT,
    _Z__PRIV__TYPE_M_ARR,
    _Z__PRIV__TYPE_M_ARR_FLOAT,
    _Z__PRIV__TYPE_M_OBJ,
};

typedef union {
    struct {
        z__u8 minor, major;
    };
    z__u16 raw;
} z__typeid;

#define z__typeid_getmajor_raw(raw) (raw >> 4 * 2)
#define z__typeid_getminor_raw(raw) (raw & (0x00ff))

#define z__typeid_make_id(major, minor) ((major << 4 * 2) | (minor & 0x00ff))

#define z__type_id_lit(n) zpp__CAT(_Z__PRIV__TYPE_ID__, n)
#define t(n) z__type_id_lit(n)
enum {
    t(u8) = z__typeid_make_id(_Z__PRIV__TYPE_M_ATOM_INT, 1),
    t(byte),
    t(i16),
    t(u16),
    t(i32),
    t(u32),
    t(i64),
    t(u64),

    t(char) ,//= z__typeid_make_id(_Z__PRIV__TYPE_M_ATOM_CHAR, 1),
    t(ptr) ,//= z__typeid_make_id(_Z__PRIV__TYPE_M_ATOM_PTR, 1),


    t(f32) = z__typeid_make_id(_Z__PRIV__TYPE_M_ATOM_FLOAT, 1),
    t(f64),

    /**/
    t(Vint2) = z__typeid_make_id(_Z__PRIV__TYPE_M_VECTOR, 1),
    t(Vint3),
    t(Vint4),

    t(Vector2),
    t(Vector3),
    t(Vector4),

    t(Matrix2) = z__typeid_make_id(_Z__PRIV__TYPE_M_MATRIX, 1),
    t(Matrix3),
    t(Matrix4),

    /**/
    t(prim_arr_u8) = z__typeid_make_id(_Z__PRIV__TYPE_M_PRIM_ARR, 1),
    t(prim_arr_byte),
    t(prim_arr_i16),
    t(prim_arr_u16),
    t(prim_arr_i32),
    t(prim_arr_u32),
    t(prim_arr_i64),
    t(prim_arr_u64),
    
    t(prim_arr_char),
    t(prim_arr_ptr),

    t(prim_arr_f32) = z__typeid_make_id(_Z__PRIV__TYPE_M_PRIM_ARR_FLOAT, 1),
    t(prim_arr_f64),

    /**/
    t(arr_u8) = z__typeid_make_id(_Z__PRIV__TYPE_M_ARR, 1),
    t(arr_byte),
    t(arr_i16),
    t(arr_u16),
    t(arr_i32),
    t(arr_u32),
    t(arr_i64),
    t(arr_u64),
    
    t(arr_char),
    t(arr_ptr),

    t(arr_f32) = z__typeid_make_id(_Z__PRIV__TYPE_M_ARR_FLOAT, 1),
    t(arr_f64),

    /**/
    t(dynt) = z__typeid_make_id(_Z__PRIV__TYPE_M_OBJ, 1),
    t(cstr),
    t(string),
    t(stringlist),
};
#undef t

#define z__PRIV__type_eval(T)\
    z__typeset_def(z__typeof(T), 0 \
        , (z__u8 , z__type_id_lit(u8))\
        , (z__byte ,z__type_id_lit(byte))\
        , (z__i16, z__type_id_lit(i16))\
        , (z__u16, z__type_id_lit(u16))\
        , (z__i32, z__type_id_lit(i32))\
        , (z__u32, z__type_id_lit(u32))\
        , (z__i64, z__type_id_lit(i64))\
        , (z__u64, z__type_id_lit(u64))\
        \
        , (char  , z__type_id_lit(char))\
        , (void *, z__type_id_lit(ptr))\
        \
        , (z__f32, z__type_id_lit(f32))\
        , (z__f64, z__type_id_lit(f64))\
        \
        , (char const *, z__type_id_lit(cstr))\
        , (char const [], z__type_id_lit(cstr))\
        \
        , (z__Vint2, z__type_id_lit(Vint2))\
        , (z__Vint3, z__type_id_lit(Vint3))\
        , (z__Vint4, z__type_id_lit(Vint4))\
        \
        , (z__Vector2, z__type_id_lit(Vector2))\
        , (z__Vector3, z__type_id_lit(Vector3))\
        , (z__Vector4, z__type_id_lit(Vector4))\
        \
        \
        , (z__Matrix2, z__type_id_lit(Matrix2))\
        , (z__Matrix3, z__type_id_lit(Matrix3))\
        , (z__Matrix4, z__type_id_lit(Matrix4))\
        \
        \
        , (z__u8[] , z__type_id_lit(prim_arr_u8))\
        , (z__byte[] , z__type_id_lit(prim_arr_byte))\
        , (z__i16[], z__type_id_lit(prim_arr_i16))\
        , (z__u16[], z__type_id_lit(prim_arr_u16))\
        , (z__i32[], z__type_id_lit(prim_arr_i32))\
        , (z__u32[], z__type_id_lit(prim_arr_u32))\
        , (z__i64[], z__type_id_lit(prim_arr_i64))\
        , (z__u64[], z__type_id_lit(prim_arr_u64))\
        \
        , (char[]  , z__type_id_lit(prim_arr_char))\
        , (void*[], z__type_id_lit(prim_arr_ptr))\
        \
        , (z__f32[], z__type_id_lit(prim_arr_f32))\
        , (z__f64[], z__type_id_lit(prim_arr_f64))\
        \
        \
        , (z__u8Arr , z__type_id_lit(arr_u8))\
        , (z__byteArr , z__type_id_lit(arr_byte))\
        , (z__i16Arr, z__type_id_lit(arr_i16))\
        , (z__u16Arr, z__type_id_lit(arr_u16))\
        , (z__i32Arr, z__type_id_lit(arr_i32))\
        , (z__u32Arr, z__type_id_lit(arr_u32))\
        , (z__i64Arr, z__type_id_lit(arr_i64))\
        , (z__u64Arr, z__type_id_lit(arr_u64))\
        \
        , (z__i8Arr , z__type_id_lit(arr_char))\
        , (z__ptrArr, z__type_id_lit(arr_ptr))\
        \
        , (z__f32Arr, z__type_id_lit(arr_f32))\
        , (z__f64Arr, z__type_id_lit(arr_f64))\
        \
        \
        , (z__Dynt, z__type_id_lit(dynt))\
        , (z__String, z__type_id_lit(string))\
        , (z__StringList, z__type_id_lit(stringlist))\
    )

#define z__typeid_raw(T) z__PRIV__type_eval(T)
#define z__typeid(T) ((z__typeid){.raw = z__typeid_raw(T)})

#endif

