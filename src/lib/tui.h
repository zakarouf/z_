#ifndef ZAKAROUF_Z__TUI_H
#define ZAKAROUF_Z__TUI_H

/*
 * Screen window tui, very much needed in case complex screen display.
 * Example
       +---------------------------------+
       | +-------------------+ +-------+ |
       | |TTTTTTTTTTTT       | |HP 100%| |
       | |TTTTTT             | |MP 70% | |
       | |  TT      X        | |AP 34  | |
       | |                   | |       | |
       | |         @         | +-------+ |
       | |                   | | 15:11 | |
       | |                   | |       | |
       | |##                 | |       | |
       | |##                 | |       | |
       | +-------------------+-+-------+ |
       | |                             | |
       | |                             | |
       | +-----------------------------+ |
       +---------------------------------+
 */


#include "std/primitives.h"
#include "arr.h"
#include "vector.h"
#include "string.h"

typedef z__u8 z__tui_attr;
typedef char  z__tui_char;

typedef struct z__tui_Window z__tui_Window;
typedef z__Arr(z__tui_Window) z__tui_WindowArr;
struct z__tui_Window {
    z__tui_char  *ch_data;
    z__u8 *fg_data;
    z__u8 *bg_data;
    z__tui_attr  *at_data;

    z__u32 width;
    z__u32 height;
    z__u32 len;

    z__u32 cursor;
};

typedef struct z__tui_Window_point z__tui_Window_point;
struct z__tui_Window_point {
    z__tui_char  c;
    z__u8 fg;
    z__u8 bg;
    z__tui_attr  at;
};

/* Colors as per ansi-256 */

#define c(X) z__tui_COLOR_##X
//#define _map(start_with, ...) start_with,  zpp__Args_maplist(c, __VA_ARGS__)

enum z__tui_color {

        // System 0 - 7
        c(DEFAULT) = 0
        , c(MAROON)
        , c(GREEN)
        , c(OLIVE)
        , c(NAVY)
        , c(PURPLE)
        , c(TEAL)
        , c(SILVER)
        , c(GREY)


        , c(RED)
        , c(LIME)
        , c(YELLOW)
        , c(BLUE)
        , c(FUCHSIA)
        , c(AQUA)
        , c(WHITE)

        , c(GS_0)
        , c(NAVY_BLUE)
        , c(DARK_BLUE)
       
        // Grey Scale
        , c(GS_1) = 232
        , c(GS_2)
        , c(GS_3)
        , c(GS_4)
        , c(GS_5)
        , c(GS_6)
        , c(GS_7)
        , c(GS_8)
        , c(GS_9)
        , c(GS_10)
        , c(GS_11)
        , c(GS_12)
        , c(GS_13)
        , c(GS_14)
        , c(GS_15)
        , c(GS_16)
        , c(GS_17)
        , c(GS_18)
        , c(GS_19)
        , c(GS_20)
        , c(GS_21)
        , c(GS_22)
        , c(GS_23)
    , c(TOTAL)
};

#undef c
#undef _map

typedef struct z__tui_Term z__tui_Term;
struct z__tui_Term {
    z__String buffer;
    z__tui_Window main_window;
    z__tui_WindowArr windows;
    z__Arr(z__u32Vec2) windows_pos;
};

/** Term Impl **/

z__u32 z__tui_Term_get_height(void);
z__u32 z__tui_Term_get_width(void);

void z__tui_Term_new_custom(z__tui_Term *t, z__u32 const x, z__u32 const y);
void z__tui_Term_new(z__tui_Term *t);
void z__tui_Term_delete(z__tui_Term *t);


/* Window Impl */
void z__tui_Window_new(z__tui_Window *w, z__u32 const width, z__u32 const height);
void z__tui_Window_delete(z__tui_Window *window);

void z__tui_Window_set_cur_x(z__tui_Window *w, z__u32 x);
void z__tui_Window_set_cur_y(z__tui_Window *w, z__u32 y);
void z__tui_Window_set_cur_xy(z__tui_Window *w, z__u32 x, z__u32 y);
#define z__tui_Window_xy(w, x, y) z__xy2Dto1D(x, y, (w)->width)

void z__tui_Window_put(z__tui_Window *w, z__tui_char c, z__u8 fg, z__u8 bg);
void z__tui_Window_putxy(z__tui_Window *w, z__u32 x, z__u32 y, z__tui_char c, z__u8 fg, z__u8 bg);

void z__tui_Window_change_ch(z__tui_Window *w, char c);
void z__tui_Window_change_fg(z__tui_Window *w, z__u8 fg);
void z__tui_Window_change_bg(z__tui_Window *w, z__u8 bg);
void z__tui_Window_change_chars(z__tui_Window *w, char const *s, z__u32 const len);

/**/

// Sub-window Functions
void z__tui_Window_overlay(z__tui_Window *w, z__tui_Window const *w1, z__u32 x, z__u32 y);
void z__tui_Window_overlay_segment(z__tui_Window *w, z__tui_Window const *w1, z__u32 x, z__u32 y, z__u32 wx, z__u32 wy, z__u32 wx1, z__u32 wy1);

void z__tui_Window_overlay_vert(z__tui_Window *w, z__tui_Window const *w1, z__u32 x, z__u32 y, z__u32 x1);
void z__tui_Window_overlay_hori(z__tui_Window *w, z__tui_Window const *w1, z__u32 x, z__u32 y, z__u32 y1);


/* Clear Functions; */
void z__tui_Window_clear(z__tui_Window *w, z__tui_char c, z__u8 fg, z__u8 bg);
void z__tui_Window_clear_ch(z__tui_Window *w, z__tui_char  c);
void z__tui_Window_clear_fg(z__tui_Window *w, z__u8 fg);
void z__tui_Window_clear_bg(z__tui_Window *w, z__u8 bg);
void z__tui_Window_clear_at(z__tui_Window *w, z__tui_attr  at);


/* Draw Functions, does not change the cursor position.*/
void z__tui_Window_draw_point(z__tui_Window *w, z__tui_char c, z__u8 fg, z__u8 bg, z__tui_attr at);
void z__tui_Window_draw_border(z__tui_Window *w, z__tui_char c, z__u8 fg, z__u8 bg);

void z__tui_Window_draw_line(z__tui_Window *w, z__u32 const x1, z__u32 const y1, z__u32 x2, z__u32 y2, z__tui_char c, z__u8 fg, z__u8 bg);
void z__tui_Window_draw_line_ch(z__tui_Window *w, z__u32 const x1, z__u32 const y1, z__u32 x2, z__u32 y2, z__tui_char c);

void z__tui_Window_draw_rect(z__tui_Window *w , z__u32 const x, z__u32 const y, z__u32 const width, z__u32 const height, z__tui_char c, z__u8 fg, z__u8 bg);
void z__tui_Window_draw_rect_fill(z__tui_Window *w , z__u32 const x, z__u32 const y, z__u32 const width, z__u32 const height, z__tui_char c, z__u8 fg, z__u8 bg);

void z__tui_Window_draw_vline(z__tui_Window *w, z__u32 x, z__u32 y, z__u32 len, z__tui_char ch, z__u8 fg, z__u8 bg);
void z__tui_Window_draw_vline_fg(z__tui_Window *w, z__u32 x, z__u32 y, z__u32 len, z__u8 fg);
void z__tui_Window_draw_vline_fg(z__tui_Window *w, z__u32 x, z__u32 y, z__u32 len, z__u8 bg);

void z__tui_Window_draw_str(z__tui_Window *w, z__u32 const x, z__u32 const y, z__tui_char const *str, z__u32 len, z__u8 fg, z__u8 bg);
void z__tui_Window_draw_str_right(z__tui_Window *w, z__u32 const x_end, z__u32 const y, z__tui_char const *str, z__u32 len, z__u8 fg, z__u8 bg);

/*
int z__tui_Window_draw_strl_center(
    z__tui_Window *w, z__u32 x, z__u32 y, z__u32 width, z__u32 height
  , z__Str str, z__u32 highlight
  , z__u8 fg, z__u8 bg, z__u8 h_fg, z__u8 h_bg);
*/

/** Display **/
void z__tui_display_init(void);
void z__tui_display_deinit(void);

void z__tui_display_window(z__tui_Window const *w);



#endif

