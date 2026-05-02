#include <stdlib.h>
#include <time.h>
#include <math.h>
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

float PI;

z__Vector2 _screen(z__Vector2 p, z__tui_Window const *scr)
{
    return (z__Vector2){.x = (p.x + 1)/2 * scr->width
                       ,.y = (1 - (p.y + 1)/2) * scr->height};
}

void _print(z__tui_Window const *scr)
{
    z__tui_display_window(scr);
}

void _point(z__Vector2 p, z__tui_Window *scr)
{
    p = _screen(p, scr);
    z__tui_Window_draw_point(scr, p.x, p.y, 'x', 0, 0);
}

int main(int argc, char *argv[])
{
    PI = atan2f(1, 1)*4;
    z__tui_Window scr;
    _init(&scr);
    
    while (z__termio_getchar() != 'q') {
        _point((z__Vector2){.x = 0, .y = 0.5}, &scr);
        _print(&scr);
    }
    
    _deinit(&scr);
    return EXIT_SUCCESS;
}
