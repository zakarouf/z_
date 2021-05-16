#ifndef ZAKAROUF__ZTYPES_TYPES__GMATH_H
#define ZAKAROUF__ZTYPES_TYPES__GMATH_H

#include "../config_types.h"
#include "base.h"
#include "../prep.h"

#ifdef Z___TYPE_INCLUED_CGLM
    #include "cglm.h"
#endif


#ifdef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_ARR_VECTOR_AND_MATRIX
    #ifndef  Z___TYPE_INCLUED_CGLM
        #error "z_: Types Error: CGLM used but not included\n"
    #endif
    #ifndef  Z___TYPE_USE_CGLM_FOR_TYPES
        #error "z_: Types Error: Use of CGLM Array Vector Alias Enabled But USE_CGLM_FOR_TYPES_IS_NOT\n"
    #endif
#endif
#ifdef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_STRUCT_VECTOR_AND_MATRIX
    #ifndef  Z___TYPE_INCLUED_CGLM
        #error "z_: Types Error: CGLM used but not included\n"
    #endif
    #ifndef  Z___TYPE_USE_CGLM_FOR_TYPES
        #error "z_: Types Error: Use of CGLM Struct Vector Alias Enabled But USE_CGLM_FOR_TYPES_IS_NOT\n"
    #endif
#endif

#ifdef Z___TYPE_CONFIG__USE_TYPE_ARR_VECTOR_AND_MATRIX
    /* |x, y, z, w| -> w is the last */
    #ifndef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_ARR_VECTOR_AND_MATRIX


        typedef z__i32                  z__ivec2[2];
        typedef z__i32                  z__ivec3[3];
        typedef z__i32                  z__ivec4[4];

        typedef z__f32                  z__vec2[2];
        typedef z__f32                  z__vec3[3];
        typedef z__f32                  z__vec4[4];

        typedef z__vec4                 z__versor;

        typedef z__vec2                 z__mat2[2];
        typedef z__vec3                 z__mat3[3];
        typedef z__vec4                 z__mat4[4];

    #endif

    #define z__vec_x(vec) vec[0]
    #define z__vec_y(vec) vec[1]
    #define z__vec_z(vec) vec[2]
    #define z__vec_w(vec) vec[3]


#endif

#ifdef Z___TYPE_CONFIG__USE_TYPE_STRUCT_VECTOR_AND_MATRIX

    /* New type declarator, Vector and Maxtrix */
    #define z__VectorSt(T, ...)\
        struct {\
            T __VA_ARGS__;\
        }
    #define z__Vector(T, ...)\
        union {                                 \
            T raw[zpp__Args_Count(__VA_ARGS__)];\
            z__VectorSt(T, __VA_ARGS__);        \
        }
    #define z__Matrix(T, x, y, ...)         \
        union {                             \
            T raw[y][x];                    \
            T col[y][x];                    \
            z__VectorSt(T, __VA_ARGS__);    \
        }

    #ifndef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_STRUCT_VECTOR_AND_MATRIX

        #ifdef Z___TYPE_CONFIG__USE_f64_FOR_VECTOR_STRUCT
            #define __vecDefType z__f64
        #else
            #define __vecDefType z__f32
        #endif

            typedef z__Vector(__vecDefType, x, y, g) z__Vector2;
            typedef z__Vector(__vecDefType, x, y, z) z__Vector3;
            typedef z__Vector(__vecDefType, x, y, z, w) z__Vector4;
            typedef union {
                z__vec4 raw;
                z__VectorSt(z__f32, x, y, z, w);
                struct {
                    z__vec3 real;
                    z__f32  imag;
                };
            } z__Versor;

        #undef __vecDefType

        typedef z__Matrix(z__f32, 2, 2
            , m00, m01
            , m10, m11 ) z__Matrix2;

        typedef z__Matrix(z__f32, 3, 3
            , m00, m01, m02
            , m10, m11, m12
            , m20, m21, m22 ) z__Matrix3;

        typedef z__Matrix(z__f32, 4, 4
            , m00, m01, m02, m03
            , m10, m11, m12, m13
            , m20, m21, m22, m23
            , m30, m31, m32, m33 ) z__Matrix4;



    #endif


    // Integer Vector Struct and Integer Matrix Struct are not
    // present in cglm (except Vint3).
    #ifdef Z___TYPE_CONFIG__USE_i64_FOR_INT_VECTOR_STRUCT
        #define __vecDefType z__i64
    #else
        #define __vecDefType z__i32
    #endif

        typedef z__Vector(__vecDefType, x, y) z__Vint2;
        typedef z__Vector(__vecDefType, x, y, z, w) z__Vint4;

        #ifndef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_STRUCT_VECTOR_AND_MATRIX
            typedef z__Vector(__vecDefType, x, y, z) z__Vint3;
        #endif

    #undef __vecDefType

    // Integer
    typedef z__Matrix(z__i32, 2, 2
        , m00, m01
        , m10, m11 ) z__Mint2;

    typedef z__Matrix(z__i32, 3, 3
        , m00, m01, m02
        , m10, m11, m12
        , m20, m21, m22 ) z__Mint3;

    typedef z__Matrix(z__i32, 4, 4
        , m00, m01, m02, m03
        , m10, m11, m12, m13
        , m20, m21, m22, m23
        , m30, m31, m32, m33 ) z__Mint4;


    /* Basic Arithmatic Operations For Vectors And Matrix
     **/
    #define z__Vector2_A(a, b, operator, dest)  \
    {                                           \
        (dest)->raw[0] = (a).raw[0] operator (b).raw[0];        \
        (dest)->raw[1] = (a).raw[1] operator (b).raw[1];        \
    }
    #define z__Vector3_A(a, b, operator, dest)  \
    {                                           \
        (dest)->raw[0] = (a).raw[0] operator (b).raw[0];        \
        (dest)->raw[1] = (a).raw[1] operator (b).raw[1];        \
        (dest)->raw[2] = (a).raw[2] operator (b).raw[2];        \
    }
    #define z__Vector4_A(a, b, operator, dest)  \
    {                                           \
        (dest)->raw[0] = (a).raw[0] operator (b).raw[0];        \
        (dest)->raw[1] = (a).raw[1] operator (b).raw[1];        \
        (dest)->raw[2] = (a).raw[2] operator (b).raw[2];        \
        (dest)->raw[3] = (a).raw[3] operator (b).raw[3];        \
    }
    #define z__Vector3_dot(a,b) (((a).x * (b).x)+((a).y * (b).y)+((a).z * (b).z))
    

    #define z__Matrix2_A(a, b, operator, dest)\
    {                                                                                                                               \
        (dest)->raw[0][0] = (a).raw[0][0] operator (b).raw[0][0]; /**/ (dest)->raw[0][1] = (a).raw[0][1] operator (b).raw[0][1];    \
        (dest)->raw[1][0] = (a).raw[1][0] operator (b).raw[1][0]; /**/ (dest)->raw[1][1] = (a).raw[1][1] operator (b).raw[1][1];    \
    }

    #define z__Matrix3_A(a, b, operator, dest)\
    {                                                                                                                                                                                           \
        (dest)->raw[0][0] = (a).raw[0][0] operator (b).raw[0][0]; /**/ (dest)->raw[0][1] = (a).raw[0][1] operator (b).raw[0][1]; /**/ (dest)->raw[0][2] = (a).raw[0][2] operator (b).raw[0][2]; \
        (dest)->raw[1][0] = (a).raw[1][0] operator (b).raw[1][0]; /**/ (dest)->raw[1][1] = (a).raw[1][1] operator (b).raw[1][1]; /**/ (dest)->raw[1][2] = (a).raw[1][2] operator (b).raw[1][2]; \
        (dest)->raw[2][0] = (a).raw[2][0] operator (b).raw[2][0]; /**/ (dest)->raw[2][1] = (a).raw[2][1] operator (b).raw[2][1]; /**/ (dest)->raw[2][2] = (a).raw[2][2] operator (b).raw[2][2]; \
    }
    #define z__Matrix4_A(a, b, operator, dest)\
    {                                                                                                                                                                                                                                                           \
        (dest)->raw[0][0] = (a).raw[0][0] operator (b).raw[0][0]; /**/ (dest)->raw[0][1] = (a).raw[0][1] operator (b).raw[0][1];  /**/ (dest)->raw[0][2] = (a).raw[0][2] operator (b).raw[0][2]; /**/ (dest)->raw[0][3] = (a).raw[0][3] operator (b).raw[0][3]; \
        (dest)->raw[1][0] = (a).raw[1][0] operator (b).raw[1][0]; /**/ (dest)->raw[1][1] = (a).raw[1][1] operator (b).raw[1][1];  /**/ (dest)->raw[1][2] = (a).raw[1][2] operator (b).raw[1][2]; /**/ (dest)->raw[1][3] = (a).raw[1][3] operator (b).raw[1][3]; \
        (dest)->raw[2][0] = (a).raw[2][0] operator (b).raw[2][0]; /**/ (dest)->raw[2][1] = (a).raw[2][1] operator (b).raw[2][1];  /**/ (dest)->raw[2][2] = (a).raw[2][2] operator (b).raw[2][2]; /**/ (dest)->raw[2][3] = (a).raw[2][3] operator (b).raw[2][3]; \
        (dest)->raw[3][0] = (a).raw[3][0] operator (b).raw[3][0]; /**/ (dest)->raw[3][1] = (a).raw[3][1] operator (b).raw[3][1];  /**/ (dest)->raw[3][2] = (a).raw[3][2] operator (b).raw[3][2]; /**/ (dest)->raw[3][3] = (a).raw[3][3] operator (b).raw[3][3]; \
    }

#endif

#endif