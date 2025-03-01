#include "tui.h"
#include "termio.h"
#include "print.h"

void z__tui_display_init(void)
{
    z__termio_echo(false);
    z__print(z__ansi_scr( (clear), (jump) ) );
    z__print(z__ansi_scr( (cur_hide) ));
}

void z__tui_display_deinit(void)
{
    z__print(z__ansi_scr( (jump), (clear) ));
    z__print(z__ansi_scr( (cur_show) ));
    z__termio_echo(true);
}

void z__tui_display_window(z__tui_Window const *w)
{
    z__print( z__ansi_scr( (jump) ));

    int plain_set = false;
    z__u32 i = 0;
    for (size_t y = 0; y < w->height; y++) {
        for (size_t x = 0; x < w->width; x++) {

            if(w->bg_data[i]) {
                if(w->fg_data[i]) {
                    z__print(z__ansi_fmt((cl256, %d, %d)), w->fg_data[i], w->bg_data[i]);
                } else {
                    z__print(z__ansi_fmt((plain), (cl256_bg, %d)), w->bg_data[i]);
                }
                plain_set = false;
                goto _L_print_char;
            } 

            if(w->fg_data[i]) {
                z__print(z__ansi_fmt((plain), (cl256_fg, %d)), w->fg_data[i]);
                plain_set = false;
            } else if(!plain_set) {
                z__print(z__ansi_fmt((plain)));
                plain_set = true;
            }

            _L_print_char:
            z__print_char(w->ch_data[i]);

            i += 1;
        }
        z__print(z__ansi_fmt((plain))"\n");
    } 
}


