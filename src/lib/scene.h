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

#ifndef ZAKAROUF_Z_SCENE_H
#define ZAKAROUF_Z_SCENE_H

#include <stdbool.h>
#include <string.h>
#include <z_/arr.h>
#include <z_/prep/base.h>

typedef struct z__Scene z__Scene;
typedef struct z__SceneConf z__SceneConf;
typedef z__Arr(z__Scene) z__SceneArr;
typedef void (*z__SceneFn)(void *state);
typedef struct z__SceneDt z__SceneDt;

// The Default values for all these is zero, conf = {0} will suffice.
struct z__SceneConf {
    z__u8 init:1
        , skip_deinit:1
        , update_end:1;
};

struct z__Scene {
    z__SceneFn fn;
    z__SceneConf conf;
    void *data;
};

struct z__SceneDt {
    z__Scene current;
    z__SceneFn next_scene;
    z__SceneArr suspend_stack;
};

// Generic Scenes you can get
z__Scene z__Scene_make(z__SceneFn scenefn);
void z__SceneDt_new(z__SceneDt *sdt, z__SceneFn first_scene);
int z__SceneDt_delete(z__SceneDt *sdt);
void z__SceneDt_suspend(z__SceneDt *sdt);
void z__SceneDt_recover(z__SceneDt *sdt);
void z__SceneDt_scene_new(z__SceneDt *sdt, z__SceneFn next_scene);
void z__SceneDt_scene_end(z__SceneDt *sdt);

#define z__SceneDt_scenefn(name, T, sdt, initfn, updatefn, deinitfn)\
    void name(void *_state){\
        T* state = _state;\
        z__Scene *scene = &state->sdt.current;\
        if(!(scene)->conf.init) {           \
            initfn(state);                  \
            (scene)->conf.init = true;      \
        }                                   \
        while(!(scene)->conf.update_end) {  \
            updatefn(state);                \
        }                                   \
        if(!(scene)->conf.skip_deinit) {    \
            deinitfn(state);                \
            (scene)->conf.init = false;     \
        }                                   \
    }

#define z__SceneDt_mainloop(state, sdt)\
        do {\
            (state)->sdt.current.fn(state);\
            if((state)->sdt.next_scene) { z__SceneDt_suspend(&(state)->sdt); }\
            else{ printf("scene end\n"); z__SceneDt_recover(&(state)->sdt);}\
        } while(!(state)->sdt.current.conf.update_end)


#define z__SceneDt_run(state, sdt, first_scene){\
        z__SceneDt_new(&(state)->sdt, first_scene);\
        z__SceneDt_mainloop(state, sdt);\
        z__SceneDt_delete(&(state)->sdt);\
    }

#ifdef Z__IMPLEMENTATION

z__Scene z__Scene_make(z__SceneFn scenefn)
{
    return (z__Scene){
        .conf = {0}
        ,.data = NULL
        ,.fn = scenefn
    };
}

void z__SceneDt_new(z__SceneDt *sdt, z__SceneFn first_scene)
{
    sdt->current = z__Scene_make(first_scene);
    sdt->next_scene = NULL;
    z__Arr_new(&sdt->suspend_stack, 8);
}

int z__SceneDt_delete(z__SceneDt *sdt)
{
    if(sdt->suspend_stack.lenUsed) return false;
    z__Arr_delete(&sdt->suspend_stack);
    return true;
}

void z__SceneDt_suspend(z__SceneDt *sdt)
{
    z__Arr_push(&sdt->suspend_stack, sdt->current);
    sdt->current = z__Scene_make(sdt->next_scene);
    sdt->next_scene = NULL;
}

void z__SceneDt_recover(z__SceneDt *sdt)
{
    if(!sdt->suspend_stack.lenUsed) { sdt->current.conf.update_end = true; return; }; // stack empty, no scene left
    sdt->current = z__Arr_getTop(sdt->suspend_stack);
    z__Arr_pop(&sdt->suspend_stack);
    sdt->current.conf.update_end = false;
}

void z__SceneDt_scene_new(z__SceneDt *sdt, z__SceneFn next_scene)
{
    sdt->next_scene = next_scene;
    sdt->current.conf.skip_deinit = true;
    sdt->current.conf.update_end = true;
}

void z__SceneDt_scene_end(z__SceneDt *sdt)
{
    sdt->next_scene = NULL;
    sdt->current.conf.skip_deinit = false;
    sdt->current.conf.update_end = true;
}

#endif // Z__IMPLEMENTATION
#endif
