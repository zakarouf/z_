#ifndef ZAKAROUF__ZTYPES_TYPES__CGLM_H
#define ZAKAROUF__ZTYPES_TYPES__CGLM_H

#include "../config.h"

#include "base.h"
#include <cglm/cglm.h>

#ifdef Z___TYPE_USE_CGLM_FOR_TYPES

    #ifdef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_ARR_VECTOR_AND_MATRIX

        typedef int                  z__ivec2[2];
        typedef ivec3                   z__ivec3;
        typedef int                 z__ivec4[4];

        typedef vec2                    z__vec2;
        typedef vec3                    z__vec3;
        typedef vec4                    z__vec4;

        typedef versor                  z__versor;

        typedef mat2                    z__mat2;
        typedef mat3                    z__mat3;
        typedef mat4                    z__mat4;

    #endif

    #ifdef Z___TYPE_CONFIG__CGLM_ALIAS_TYPE_STRUCT_VECTOR_AND_MATRIX

        #include <cglm/struct.h>

        typedef vec2s z__Vector2;
        typedef vec3s z__Vector3;
        typedef vec4s z__Vector4;

        typedef ivec3s z__Vint3;

        typedef versors z__Versor;

        typedef mat2s z__Matrix2;
        typedef mat3s z__Matrix3;
        typedef mat4s z__Matrix4;

    #endif

#endif

#endif