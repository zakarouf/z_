#include "../lib/test.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <z_/arr.h>
#include "../lib/scene.h"
#include "../lib/termio.h"

#define TEST_SUITE scene
#define TEST(name) z__test_def(TEST_SUITE, name)

struct app_state {
    int x, m_x;
    int init, deinit, w_init, w_deinit;
    z__SceneDt sdt;
};

void app_scene_window_init(struct app_state *s) {
    printf("Scene: Window Init\n");
    s->w_init = true;
    s->w_deinit = false;
    s->m_x = 0;
}

void app_scene_window_update(struct app_state *s) {
    if(s->m_x < 10) { s->m_x += 1; }
    else {z__SceneDt_scene_end(&s->sdt);}
}

void app_scene_window_deinit(struct app_state *s) {
    s->w_deinit = true;
    s->x = 1;
}

z__SceneDt_scenefn(app_scene_window, struct app_state, sdt
        , app_scene_window_init, app_scene_window_update, app_scene_window_deinit);

void app_scene_menu_init(struct app_state *s) { s->x = 0; s->init = true; }
void app_scene_menu_update(struct app_state *s) { 
    if(s->x == 0) { z__SceneDt_scene_new(&s->sdt, app_scene_window);}
    else {
        if(s->x < 5) s->x += 1;
        else z__SceneDt_scene_end(&s->sdt);
    }
}

void app_scene_menu_deinit(struct app_state *s) {
    s->deinit = true;
}

z__SceneDt_scenefn(app_scene_menu, struct app_state
         , sdt, app_scene_menu_init
                         , app_scene_menu_update
                         , app_scene_menu_deinit);

TEST(scene) {
    struct app_state state;
    z__SceneDt_run(&state, sdt, app_scene_menu);

    z__test_assert(state.init, "init not set");
    z__test_assert(state.deinit, "deinit not set");
    z__test_assert(state.x == 5, "x = %u", state.x);

    z__test_assert(state.w_init, "init not set");
    z__test_assert(state.w_deinit, "deinit not set");
    z__test_assert_int(state.m_x, 10);

    z__test_assert(1, "");
    z__test_done();
}

z__test_impl(TEST_SUITE, scene);
