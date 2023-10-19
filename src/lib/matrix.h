#ifndef ZAKAROUF__ZTYPES_TYPES__GMATH_MATRIX_H
#define ZAKAROUF__ZTYPES_TYPES__GMATH_MATRIX_H

#include "std/primitives.h"

    #define z__Matrix(T, x, y, ...)         \
        union {                             \
            T raw[y][x];                    \
            T col[y][x];                    \
            struct { T __VA_ARGS__;};       \
        }

#ifndef Z__CONFIG_VECTOR_CGLM_ALIAS_TYPE_MATRIX

        typedef z__f32                 z__mat2[2][2];
        typedef z__f32                 z__mat3[3][3];
        typedef z__f32                 z__mat4[4][4];

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

#else
        #include "cglm.h"
      
        typedef mat2 z__mat2;
        typedef mat3 z__mat3;
        typedef mat4 z__mat4;


        typedef mat2s z__Matrix2;
        typedef mat3s z__Matrix3;
        typedef mat4s z__Matrix4;
#endif

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



    #define z__Matrix2_A(a, b, operator, dest)\
    {                                                                                                                               \
        (dest)->raw[0][0] = (a).raw[0][0] operator (b).raw[0][0]; /**/ (dest)->raw[0][1] = (a).raw[0][1] operator (b).raw[0][1];    \
        (dest)->raw[1][0] = (a).raw[1][0] operator (b).raw[1][0]; /**/ (dest)->raw[1][1] = (a).raw[1][1] operator (b).raw[1][1];    \
    }

    #define z__Matrix3_A(a, b, operator, dest)\
    {                                                                                                                                                                                           \
        (dest)->raw[0][0] = (a).raw[0][0] operator (b).raw[0][0]; /**/ (dest)->raw[0][1] = (a).raw[0][1] operator (b).raw[0][1]; /**/ (dest)->raw[0][2] = (a).raw[0][2] operator (b).raw[0][2]; \
        (dest)->raw[1][0] = (a).raw[1][0] operator (b).raw[1][0]; /**/ (dest)->raw[1][1] = (a).raw[1][1] operator (b).raw1][1]; /**/ (dest)->raw[1][2] = (a).raw[1][2] operator (b).raw[1][2]; \
        (dest)->raw[2][0] = (a).raw[2][0] operator (b).raw[2][0]; /**/ (dest)->raw[2][1] = (a).raw[2][1] operator (b).raw[2][1]; /**/ (dest)->raw[2][2] = (a).raw[2][2] operator (b).raw[2][2]; \
    }
    #define z__Matrix4_A(a, b, operator, dest)\
    {                                                                                                                                                                                                                                                           \
        (dest)->raw[0][0] = (a).raw[0][0] operator (b).raw[0][0]; /**/ (dest)->raw[0][1] = (a).raw[0][1] operator (b).raw[0][1];  /**/ (dest)->raw[0][2] = (a).raw[0][2] operator (b).raw[0][2]; /**/ (dest)->raw[0][3] = (a).raw[0][3] operator (b).raw[0][3]; \
        (dest)->raw[1][0] = (a).raw[1][0] operator (b).raw[1][0]; /**/ (dest)->raw[1][1] = (a).raw[1][1] operator (b).raw[1][1];  /**/ (dest)->raw[1][2] = (a).raw[1][2] operator (b).raw[1][2]; /**/ (dest)->raw[1][3] = (a).raw[1][3] operator (b).raw[1][3]; \
        (dest)->raw[2][0] = (a).raw[2][0] operator (b).raw[2][0]; /**/ (dest)->raw[2][1] = (a).raw[2][1] operator (b).raw[2][1];  /**/ (dest)->raw[2][2] = (a).raw[2][2] operator (b).raw[2][2]; /**/ (dest)->raw[2][3] = (a).raw[2][3] operator (b).raw[2][3]; \
        (dest)->raw[3][0] = (a).raw[3][0] operator (b).raw[3][0]; /**/ (dest)->raw[3][1] = (a).raw[3][1] operator (b).raw[3][1];  /**/ (dest)->raw[3][2] = (a).raw[3][2] operator (b).raw[3][2]; /**/ (dest)->raw[3][3] = (a).raw[3][3] operator (b).raw[3][3]; \
    }

    #define z__Matrix2_det(A)\
        ( ((A).raw[0][0] * (A).raw[1][1]) - ((A).raw[0][1] * (A).raw[1][0]) )

#endif
