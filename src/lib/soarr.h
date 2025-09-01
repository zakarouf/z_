/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZAKAROUF__Z__SOARR_H
#define ZAKAROUF__Z__SOARR_H

#include "std/mem.h"
#include "prep/args.h"

#define z__SoArr(N, ...)\
            z__SoArrDef(N, __VA_ARGS__);\
            z__SoArrImpl(N, __VA_ARGS__)

#define z__SoArrDef(N, ...)\
    struct N {                                          \
        union {                                         \
            void *data[zpp__Args_Count(__VA_ARGS__)];   \
            struct {                                    \
                zpp__Args_map(\
                    z__PRIV__SoArr_STRUCT_ELEMENT_UNWRAP, __VA_ARGS__)\
            } item;                                     \
        };                                              \
        z__u32 len, lenUsed;                            \
    }

#define z__SoArrExt(N, ...)\
    void N##_new(struct N* self, z__u32 len);                   \
    void N##_delete(struct N *self);                            \
    void N##_expand(struct N *self, z__u32 by);                 \
    void N##_push(struct N *self, zpp__Args_maplist(            \
                z__PRIV__SoArr_PUSH_ARG_UNWRAP, __VA_ARGS__));  \

#define z__SoArrImpl(N, ...)\
    void N##_new(struct N* self, z__u32 len) {              \
        z__PRIV__SoArr_STRUCT_FN_CALC_ELEM(__VA_ARGS__);    \
        self->data[0] = z__MALLOC(total_size);              \
        z__PRIV__SoArr_STRUCT_ELEM_UPDATE()                 \
        self->len = len;                                    \
        self->lenUsed = 0;                                  \
    }                                                       \
    \
    void N##_delete(struct N *self){                        \
        z__FREE(self->data[0]);                             \
    }                                                       \
    \
    void N##_expand(struct N *self, z__u32 by){                             \
        z__u32 const len = by + self->len;                                  \
        z__PRIV__SoArr_STRUCT_FN_CALC_ELEM(__VA_ARGS__);                    \
        self->data[0] = z__REALLOC(self->data[0], total_size);              \
        self->len = len;                                                    \
    }                                                                       \
    void N##_push(struct N *self, zpp__Args_maplist(z__PRIV__SoArr_PUSH_ARG_UNWRAP, __VA_ARGS__)) {\
        if(self->lenUsed >= self->len) { N##_expand(self, self->len); }\
        zpp__Args_map(z__PRIV__SoArr_PUSH_ASSIGN_UNWRAP, __VA_ARGS__)\
        self->lenUsed += 1;\
    }


/** -------- PRIV --------- **/

#define z__PRIV__SoArr_STRUCT_ELEMENT(T, N) T* N;
#define z__PRIV__SoArr_STRUCT_ELEMENT_UNWRAP(x)\
            z__PRIV__SoArr_STRUCT_ELEMENT x

#define z__PRIV__SoArr_STRUCT_SIZE(T, N) (sizeof(*(self)->item.N) * len )
#define z__PRIV__SoArr_STRUCT_SIZE_UNWRAP(x)\
            z__PRIV__SoArr_STRUCT_SIZE x
            
#define z__PRIV__SoArr_PUSH_ARG(T, N) T N
#define z__PRIV__SoArr_PUSH_ARG_UNWRAP(x)\
            z__PRIV__SoArr_PUSH_ARG x

#define z__PRIV__SoArr_PUSH_ASSIGN(T, N) self->item.N[self->lenUsed] = N;
#define z__PRIV__SoArr_PUSH_ASSIGN_UNWRAP(x)\
            z__PRIV__SoArr_PUSH_ASSIGN x


#define z__PRIV__SoArr_STRUCT_FN_CALC_ELEM(...)\
        z__u32 const elements = sizeof(self->data)/sizeof(self->data[0]);   \
        z__u32 const element_sizes[sizeof(self->data)/sizeof(self->data[0])]\
                = { zpp__Args_maplist(z__PRIV__SoArr_STRUCT_SIZE_UNWRAP     \
                        , __VA_ARGS__)                                      \
                };                                                          \
        z__size total_size = element_sizes[0] * len;                        \
        for (size_t i = 1; i < elements; i++) {         \
            total_size += element_sizes[i] * len;       \
        }                                               \

#define z__PRIV__SoArr_STRUCT_ELEM_UPDATE()\
        z__byte* ptr = self->data[0];                       \
        ptr += (element_sizes[0] * len);                    \
        for (size_t i = 1; i < elements; i++) {             \
            self->data[i] = ptr;                            \
            ptr += (element_sizes[i] * len);                \
        }                                                   \


#endif

