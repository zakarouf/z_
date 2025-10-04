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

#ifndef ZAKAROUF__ZTYPES_TYPES__OBJ_H
#define ZAKAROUF__ZTYPES_TYPES__OBJ_H

#include "prep/args.h"
#include "record.h"
#include "fnptr.h"

/**
    Usage:
    --------

    Example:
    ---------
    ```c
        typedef
            struct {
                int x, y;
                // Data Related to player
        } Player;

        typedef
            struct {
                int x, y;
                // Data Related to enemy
        } Enemy;

        static
        z__objfn_defcl(Enemy, Actor, Move, void, int x, int y)
        {
            z__objfn_clself(Enemy);
            self->x += x;
            self->y += y;
        }

        static
        z__objfn_defcl(Player, Actor, Move, void, int x, int y)
        {
            z__objfn_clself(Player);
            self->x += x;
            self->y += y;
        }

        z__objcl(Actor, (), (Move, void, int, int));
        z__objcl_impl(Actor, Player, Move);
        z__objcl_impl(Actor, Enemy, Move);

        int main(void) {
            Player p = { .x = 10, .y = 50 };
            Enemy e = { .x = 10, .y = 50 };

            Actor actor[2];
            z__objcl_set(&actor[0], Actor, &p, Player);
            z__objcl_set(&actor[1], Actor, &e, Enemy);

            z__objcl_call(&actor[0], Move, 10, 23);
            z__objcl_call(&actor[1], Move, -3, 20);

            assert((p.x == 20 && p.y == 73));
            assert((e.x == 7 && e.y == 70));

            return 0;
        }
    ```
 */

#define z__objfn_clself(T) T* self = (_self_)

/* Object Function Namespace */
#define z__objfn(T, name)\
    zpp__CAT(zpp__CAT(T, _), name)

#define z__objfn_cl(_A, name)\
    z__objfn(zpp__PRIV__Args_get_1 _A, zpp__CAT(name, zpp__CAT(__FOR_, zpp__PRIV__Args_get_2 _A)))

/* Definations */
#define z__objfn_def(T, name, ret, ...)\
    ret z__objfn(T, name) (T* _self_,##__VA_ARGS__)

#define z__objfn_defcl(T, for, name, ret, ...)\
    ret z__objfn_cl((T, for), name)(void *_self_, ##__VA_ARGS__)

/* Vtables */
#define z__objvt_type(T, alias) zpp__CAT4(T, _, alias, __vt_)
#define z__objvt(T, alias, ...) /* x E __VA_ARGS__ : where x => (fn_name, ret, ...) */\
     typedef struct z__objvt_type(T, alias)  {\
        zpp__Args_applyfxy(z__PRIV__objvt_sinfxy, T, __VA_ARGS__);\
    } z__objvt_type(T, alias)


/* Hooking Vtables */
#define z__objvt_bind(vt, T, ...)\
    {\
        zpp__Args_applyfxy(z__PRIV__objvt_bind_sinfxy, (vt, T), __VA_ARGS__);\
    } 

#define z__objvt_impl(T, alias, ...)\
    void z__PRIV__objvt_impl_proto(T, alias) (z__objvt_type(T, alias) *_self_)\
        z__objvt_bind(_self_, T, __VA_ARGS__)

#define z__objvt_get(T, alias)\
    z__PRIV__objvt_impl_proto(T, alias)

/**
 * Closure Implementation
 */
#define z__objcl(T, cnt, ...)\
    typedef struct T {                                                      \
        void *_obj_;                                                        \
        zpp__Args_applyfxy(z__PRIV__objvt_sinfxy, void, __VA_ARGS__); \
        zpp__EXPAND cnt;                                                    \
    } T

#define z__objcl_bind_raw(cl, cl_T, obj_T, obj, ...)\
    {\
        (cl)->_obj_ = obj;\
        zpp__Args_applyfxy(z__PRIV__objcl_bind_sinfn, (cl, obj_T, cl_T), __VA_ARGS__);\
    }

#define z__objcl_proto(cl_T, obj_T)\
    zpp__CAT(cl_T, zpp__CAT(__FOR__, obj_T))

#define z__objcl_impl(cl_T, obj_T, ...)\
    void z__objcl_proto(cl_T, obj_T) (cl_T *cl, obj_T *obj)\
        z__objcl_bind_raw(cl, cl_T, obj_T, obj, __VA_ARGS__)\

#define z__objcl_implext(cl_T, obj_T)\
    extern void z__objcl_proto(cl_T, obj_T) (cl_T *cl, obj_T *obj)

#define z__objcl_set(cl, cl_T, obj, obj_T)\
    z__objcl_proto(cl_T, obj_T)(cl, obj)

#define z__objcl_call(v, method, ...)\
    (v)->method((v)->_obj_,##__VA_ARGS__)

/** PRIV - Vtables **/
#define z__PRIV__objvt_sin(obj_T, fn_name, ret, ...) z__fnptr(fn_name, ret, obj_T *_self_,##__VA_ARGS__);
#define z__PRIV__objvt_sinunpack(x, y) z__PRIV__objvt_sin(x, y)
#define z__PRIV__objvt_sinfxy(x, y) z__PRIV__objvt_sinunpack(x, zpp__EXPAND y)

/** PRIV - Hooking Vtables **/
#define z__PRIV__objvt_bind_sin(vt, T, v_name, fn_name) (vt)->v_name = &z__objfn(T, fn_name)
#define z__PRIV__objvt_bind_sinunpack(x, y) z__PRIV__objvt_bind_sin(x, y)
#define z__PRIV__objvt_bind_sinfxy(x, y) z__PRIV__objvt_bind_sinunpack(zpp__EXPAND x, zpp__EXPAND y);
#define z__PRIV__objvt_impl_proto(T, alias) zpp__CAT3(T, _vt_impl_for_, alias)

/** PRIV - Closure Implementation **/
#define z__PRIV__objcl_bind_sin(v, obj_T, cl_T, method) (v)->method = z__objfn_cl((obj_T, cl_T), method);
#define z__PRIV__objcl_bind_sinunpack(va, x) z__PRIV__objcl_bind_sin(va, x)
#define z__PRIV__objcl_bind_sinfn(va, x) z__PRIV__objcl_bind_sinunpack(zpp__EXPAND va, x)

#endif

