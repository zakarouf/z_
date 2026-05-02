#define Z__IMPLEMENTATION
#include <z_/string.h>

#include "src/lib/termio.h"
#include "src/lib/tui.h"
#include <z_/std/mem.h>
#include <z_/std/primitives.h>

#include <z_/tui.h>

z__u32 z__tui_Window_fmt_dialogue_box(z__tui_Window *w, z__String const *head, z__String const *text, z__tui_Window_point headfmt, z__tui_Window_point textfmt, z__tui_Window_point borderfmt, z__u32 scroll) {
    if(borderfmt.c) z__tui_Window_draw_border(w, borderfmt);
    z__tui_Window_set_cur_xy(w, 0, 0);
    z__tui_Window_draw_str(w, 0, 0, head->data, head->lenUsed, headfmt.fg, headfmt.bg);
    
    z__tui_Window_draw_hline(w, 1, z__tui_Window_get_y(w)+1, head->lenUsed, headfmt.c, headfmt.fg, headfmt.bg);
    z__tui_Window_draw_str(w, 1, z__tui_Window_get_y(w)+1, text->data, text->lenUsed, textfmt.fg, textfmt.bg);
    return 0;
}

void test(void) {
    z__tui_display_init();
    z__tui_Window win;
    z__tui_Window_new(&win, 30, 7);

    z__String head = z__String_newFrom("Zakarouf");
    z__String text = z__String_newFrom("How are you doing?");

    z__tui_Window_point headfmt = {.c = '-'},
                        textfmt = {.fg = z__tui_COLOR_YELLOW},
                        bordfmt = {0};

    //z__tui_Window_fmt_dialogue_box(&win, &head, &text, headfmt, textfmt, bordfmt, 0);

    z__String a_very_long_text = z__String_newFrom("This is a very very long text, for test the text box wrap for strings, i can use it in he rpg/text based games etc etc");
    
    char key = 0;
    z__u32 scroll = 0;
    while (key != 'q') {
        z__tui_Window_draw_str_wrapbox(&win, 0, 0, 12, 5, a_very_long_text.data, a_very_long_text.lenUsed, 0, scroll);
        z__tui_display_window(&win);
        key = z__termio_getchar();
        if(key == 'w') scroll--; 
        if(key == 's') scroll++; 
    }
    z__tui_display_deinit();
}

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;
    test();
    return EXIT_SUCCESS;
}
