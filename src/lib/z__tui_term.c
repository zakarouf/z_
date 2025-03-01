#include "ansifmt.h"
#include "string.h"
#include "termio.h"
#include "arr.h"

#include <stdlib.h>
#include "tui.h"

#define NORMAL_CHAR_SIZE sizeof(z__ansi_fmt((cl256, 001, 002)) " ")

z__u32 z__tui_Term_get_height(void)
{
    z__u32 x, y;
    z__termio_get_term_size(&x, &y);
    return y;
}

z__u32 z__tui_Term_get_width(void)
{
    z__u32 x, y;
    z__termio_get_term_size(&x, &y);
    return x;
}

void z__tui_Term_new_custom(z__tui_Term *t, z__u32 const x, z__u32 const y)
{
    z__Arr_new(&t->windows, 4);
    z__Arr_new(&t->windows_pos, 4);

    z__String_new(NORMAL_CHAR_SIZE * x * y);

    z__tui_Window_new(&t->main_window, x, y);
}

void z__tui_Term_delete(z__tui_Term *t)
{
    for (size_t i = 0; i < t->windows.lenUsed; i++) {
        z__tui_Window_delete(t->windows.data + i);
    }

    z__tui_Window_delete(&t->main_window);

    z__Arr_delete(&t->windows);
    z__Arr_delete(&t->windows_pos);
}

void z__tui_Term_new(z__tui_Term *t)
{
    z__tui_Term_new_custom(t
            , z__tui_Term_get_width() -2
            , z__tui_Term_get_height() -3);
}

z__tui_Window* z__tui_Term_win_push(z__tui_Term *t, z__u32 const x, z__u32 const y, z__u32 const width, z__u32 const height)
{
    z__Arr_pushInc(&t->windows);
    z__tui_Window *w = &z__Arr_getTop(t->windows);
    z__tui_Window_new(w, width, height);

    z__Arr_pushInc(&t->windows_pos);
    z__Arr_getTop(t->windows_pos).x = x;
    z__Arr_getTop(t->windows_pos).y = y;

    return w;
}

