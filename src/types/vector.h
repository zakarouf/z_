#ifndef ZAKAROUF__ZTYPES_TYPES__GMATH_VECTOR_H
#define ZAKAROUF__ZTYPES_TYPES__GMATH_VECTOR_H

#include "../config_types.h"
#include "base.h"
#include "../prep.h"

// Start

#define z__vec_x(vec) vec[0]
#define z__vec_y(vec) vec[1]
#define z__vec_z(vec) vec[2]
#define z__vec_w(vec) vec[3]

/* New type declarator, Vector and Maxtrix */
#define z__VectorSt(T, ...)\
    struct {            \
        z__typeof(T) __VA_ARGS__;  \
    }

#define z__Vector(T, ...)\
    union {                                 \
        z__typeof(T) raw[zpp__Args_Count(__VA_ARGS__)];\
        z__VectorSt(T, __VA_ARGS__);        \
    }

/* |x, y, z, w| -> w is the last */
#ifndef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_VECTOR
        typedef z__i32                  z__ivec2[2];
        typedef z__i32                  z__ivec3[3];
        typedef z__i32                  z__ivec4[4];

        typedef z__f32                  z__vec2[2];
        typedef z__f32                  z__vec3[3];
        typedef z__f32                  z__vec4[4];

        typedef z__vec4                 z__versor;

        #ifdef Z___TYPE_CONFIG__USE_f64_FOR_VECTOR_STRUCT
            #define __vecDefType z__f64
        #else
            #define __vecDefType z__f32
        #endif

            typedef z__Vector(__vecDefType, x, y) z__Vector2;
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


#else
        #include "cglm.h"

        typedef int                 z__ivec2[2];
        typedef ivec3               z__ivec3;
        typedef int                 z__ivec4[4];

        typedef vec2                    z__vec2;
        typedef vec3                    z__vec3;
        typedef vec4                    z__vec4;

        typedef versor                  z__versor;

        typedef vec2s z__Vector2;
        typedef vec3s z__Vector3;
        typedef vec4s z__Vector4;

        typedef ivec3s z__Vint3;

        typedef versors z__Versor;


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

#ifndef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_VECTOR
        typedef z__Vector(__vecDefType, x, y, z) z__Vint3;
#endif

#undef __vecDefType


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
    


#endif

