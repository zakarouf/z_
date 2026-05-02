#include <stdlib.h>
#include <time.h>
#define Z__IMPLEMENTATION
#include <z_/std/primitives.h>
#include <z_/string.h>
#include <z_/utils.h>
#include <z_/time.h>
#include <z_/tui.h>
#include <z_/termio.h>
#include <z_/random.h>

static void _init(z__tui_Window *screen)
{
    z__u32 x, y;
    z__termio_get_term_size(&x, &y);
    z__tui_Window_new(screen, x, y-1);
    z__tui_display_init();
}

static void _deinit(z__tui_Window *screen)
{
    z__tui_display_deinit();
    z__tui_Window_delete(screen);
}

z__f64 z__frandom()
{
    union {
        z__u64 u64;
        z__f64 f64;
    } v = {.u64 = z__rnd_hash64_wang(0x46F0FA6A5CE21025ULL)};
    return v.f64;
}

static void _make_bargraph(
        z__tui_Window *window
      , z__u32x2 range
      , z__constptr(z__i64Arr) points) {
    /** 
     * ymax |
     *      |
     *      |        #
     *      |#       #   
     *      |# # #   # # #
     *      |# # # # # # # #
     * ymin +--------------- xmax
     *      xmin            
     */
    z__tui_Window_clear(window, ' ', z__tui_COLOR_DEFAULT, z__tui_COLOR_DEFAULT);

}

int main(int argc, char *argv[])
{
    z__tui_Window screen;
    _init(&screen);

    //z__tui_Window_draw_border(&screen, ' ', z__tui_COLOR_RED, z__tui_COLOR_RED);

    #define BCOUNT 10
    z__u32Vec2 bullets[BCOUNT] = {0};
    z__Vector2 bspeed[BCOUNT] = {0};

    for (size_t i = 0; i < BCOUNT; i++) {

    }

    z__String buffer = z__String_new(32);
    int quit = 0;
    z__u64 t = z__time_process();
    z__float dt = 0;

    while(!quit){
        // keypress
        char key = z__termio_getchar();
        switch (key) {
            break; case 'q': quit = 1;
            break; default: {};
        }
        dt = z__time_delta(t, z__time_process());
        t = z__time_process();

        buffer.lenUsed = 0;
        z__String_append_nopad(&buffer, "%lf", z__frandom());
        z__tui_Window_draw_str(&screen, 0, 0, buffer.data
                , buffer.lenUsed
                , z__tui_COLOR_DEFAULT, z__tui_COLOR_DEFAULT);

        z__tui_display_window(&screen);
    }

    _deinit(&screen);
    return EXIT_SUCCESS;
}
