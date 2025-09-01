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

#ifdef Z__IMPLEMENTATION

/************************************************************************
 *                              Term 
 ************************************************************************/
#include "ansifmt.h"
#include "string.h"
#include "termio.h"
#include "arr.h"
#include <stdlib.h>

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


/************************************************************************
 *                              Window 
 ************************************************************************/
#include "string.h"
#include "std/mem.h"
#include "std/alloc.h"
#include "utils.h"

#include <stdlib.h>

#define z__tui_Window_draw_point_i(window, index, c, fg, bg)\
    {                                \
        (w)->ch_data[index] = c;       \
        (w)->fg_data[index] = fg;      \
        (w)->bg_data[index] = bg;      \
    }

void z__tui_Window_new(z__tui_Window *window, z__u32 const x, z__u32 const y)
{
    window->height = y;
    window->width = x;
    window->len = x * y;

    window->cursor = 0;

    window->ch_data = z__New(*window->ch_data, window->len);
    window->bg_data = z__New(*window->bg_data, window->len);
    window->fg_data = z__New(*window->fg_data, window->len);
    window->at_data = z__New0(*window->fg_data, window->len);

    memset(window->ch_data, ' ', window->len * sizeof(*window->ch_data));
    memset(window->fg_data,  z__tui_COLOR_DEFAULT
            , window->len * sizeof(*window->fg_data));
    memset(window->bg_data,  z__tui_COLOR_DEFAULT
            , window->len * sizeof(*window->bg_data));
}

void z__tui_Window_delete(z__tui_Window *window)
{
    z__FREE(window->ch_data);
    z__FREE(window->fg_data);
    z__FREE(window->bg_data);
    z__FREE(window->at_data);
}

inline void z__tui_Window_cursor_inc(z__tui_Window *w)
{
    if(w->cursor < w->len) w->cursor += 1;
}

inline int z__tui_Window_is_cursor_atend(z__tui_Window *w)
{
    return w->cursor == w->len;
}

inline int z__tui_Window_is_cursor_valid(z__tui_Window *w)
{
    return w->cursor < w->len;
}

inline z__u32 z__tui_Window_get_x(z__tui_Window *w)
{
    return (w->cursor % w->width);
}

inline z__u32 z__tui_Window_get_y(z__tui_Window *w)
{
    return w->cursor/w->width;
}

inline void z__tui_Window_set_cur_x(z__tui_Window *w, z__u32 x)
{
    z__u32 y = z__tui_Window_get_y(w);
    w->cursor = z__xy2Dto1D(x, y, w->width);
}

inline void z__tui_Window_set_cur_y(z__tui_Window *w, z__u32 y)
{
    z__u32 x = z__tui_Window_get_x(w);
    w->cursor = z__xy2Dto1D(x, y, w->width);
}

inline void z__tui_Window_set_cur_xy(z__tui_Window *w, z__u32 x, z__u32 y)
{
    w->cursor = z__xy2Dto1D(x, y, w->width);
}

inline void z__tui_Window_put(z__tui_Window *w, z__tui_char c, z__u8 fg, z__u8 bg)
{
    z__u32 const index = w->cursor;
    w->ch_data[index] = c;
    w->fg_data[index] = fg;
    w->bg_data[index] = bg;

    z__tui_Window_cursor_inc(w);
}

inline void z__tui_Window_putxy(z__tui_Window *w, z__u32 const x, z__u32 const y, z__tui_char c, z__u8 fg, z__u8 bg)
{
    z__tui_Window_set_cur_xy(w, x, y);
    z__tui_Window_put(w, c, fg, bg);
}

inline void z__tui_Window_change_ch(z__tui_Window *w, z__tui_char c)
{
    w->ch_data[w->cursor] = c;
    z__tui_Window_cursor_inc(w);
}

inline void z__tui_Window_change_fg(z__tui_Window *w, z__u8 fg)
{
    w->fg_data[w->cursor] = fg;
    z__tui_Window_cursor_inc(w);
}

inline void z__tui_Window_change_bg(z__tui_Window *w, z__u8 bg)
{
    w->bg_data[w->cursor] = bg;
    z__tui_Window_cursor_inc(w);
}

inline void z__tui_Window_change_chars(z__tui_Window *w, char const *s, z__u32 const len)
{
    size_t i = w->cursor;
    size_t end = z__min_unsafe(len, w->len);
    for (; i < end; i++) {
        z__tui_Window_change_ch(w, s[i]);
    }
}

inline void z__tui_Window_overlay(z__tui_Window *w, z__tui_Window const *w1, z__u32 x, z__u32 y)
{
    size_t h_end = z__min_unsafe(w->height, w1->height);
    size_t w_end = z__min_unsafe(w->width, w1->width);

    for (size_t _h = 0; _h < h_end; _h++) {

        z__tui_Window_set_cur_xy(w, x, y + _h);
        size_t plot = z__xy2Dto1D(0, _h, w1->width);

        for (size_t _w = 0; _w < w_end; _w++) {
            
            z__tui_Window_draw_point_i(
                w, w->cursor
              , w1->ch_data[plot]
              , w1->fg_data[plot]
              , w1->bg_data[plot]
            );

            w->cursor += 1;
            plot += 1;
        }
    }
    
}

void z__tui_Window_draw_line(
      z__tui_Window *w
    , z__u32 const x1, z__u32 const y1, z__u32 x2, z__u32 y2
    , z__tui_char c, z__u8 fg, z__u8 bg) 
{
    y2 = z__min_unsafe(y2, w->height);
    x2 = z__min_unsafe(x2, w->width);

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = z__max_unsafe(abs(dx), abs(dy));

    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;

    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++) {
        
        size_t index = (z__xy2Dto1D(x, y, w->width));
        z__tui_Window_draw_point_i(w, index, c, fg, bg);
    
        x += xIncrement;
        y += yIncrement;
    }
}

void z__tui_Window_draw_line_ch(
        z__tui_Window *w
      , z__u32 const x1, z__u32 const y1, z__u32 x2, z__u32 y2, z__tui_char c)
{
    z__i32 const dy = y2 - y1;
    z__i32 const dx = x2 - x1;
    z__i32 d = 2 * dy - dx;
    z__u32 x = x1;
    z__u32 y = y1;

    while (x <= x2) {

        size_t index = (z__xy2Dto1D(x, y, w->width));
        w->ch_data[index] = c;

        x += 1;

        if (d < 0) {
            d += 2 * dy;
        } else {
            d += 2 * (dy - dx);
            y += 1;
        }
    }
}

void z__tui_Window_draw_line_ch_old(z__tui_Window *w, z__u32 const x1, z__u32 const y1, z__u32 x2, z__u32 y2, z__tui_char c)
{
    y2 = z__min_unsafe(y2, w->height);
    x2 = z__min_unsafe(x2, w->width);

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;

    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++) {
        
        size_t index = (z__xy2Dto1D(x, y, w->width));
        w->ch_data[index] = c;
    
        x += xIncrement;
        y += yIncrement;
    }
}

void z__tui_Window_draw_rect(
    z__tui_Window *w
  , z__u32 const x, z__u32 const y, z__u32 width, z__u32 height
  , z__tui_char c, z__u8 fg, z__u8 bg)
{
    size_t x_end = z__min_unsafe((x + width), w->width);
    size_t y_end = z__min_unsafe((y + height), w->height);

    // Draw top line
    size_t i = z__xy2Dto1D(x, y, w->width);
    size_t i_end = z__xy2Dto1D(x_end, y, w->width);
    for (; i < i_end; i++) { 
        z__tui_Window_draw_point_i(w, i, c, fg, bg);        
    }

    // Draw bottom line
    i = z__xy2Dto1D(x, y_end, w->width);
    i_end = z__xy2Dto1D(x_end, y_end, w->width);
    for (; i < i_end; i++) {
        z__tui_Window_draw_point_i(w, i, c, fg, bg);        
    }

    // Draw left line
    i = z__xy2Dto1D(x, y+1, w->width);
    i_end = z__xy2Dto1D(x, y_end, w->width);
    for (; i < i_end; i += w->width) {
        z__tui_Window_draw_point_i(w, i, c, fg, bg);
    }

    // Draw right line
    i = z__xy2Dto1D(x_end-1, y+1, w->width);
    i_end = z__xy2Dto1D(x_end, y_end, w->width);
    for (; i < i_end; i += w->width) {
        z__tui_Window_draw_point_i(w, i, c, fg, bg);
    }
}

void z__tui_Window_draw_rect_fill(
    z__tui_Window *w
  , z__u32 const x, z__u32 const y, z__u32 const width, z__u32 const height
  , z__tui_char c, z__u8 fg, z__u8 bg)
{
    size_t x_end = x + width;
    if(x_end > w->width) x_end = (w->width - x);
    else x_end = (width);
    size_t y_end = z__min_unsafe((y + height), w->height);

    for (size_t i = y; i < y_end; i++) {
        size_t index = (z__tui_Window_xy(w, x, i));
        memset(w->ch_data + index, c, x_end);
        memset(w->fg_data + index, fg, x_end);
        memset(w->bg_data + index, bg, x_end);
    }
}

void z__tui_Window_clear(z__tui_Window *w, z__tui_char c, z__u8 fg, z__u8 bg)
{
    memset(w->ch_data, c , w->len * sizeof(*w->ch_data));
    memset(w->fg_data, fg, w->len * sizeof(*w->fg_data));
    memset(w->bg_data, bg, w->len * sizeof(*w->bg_data));
    memset(w->at_data, 0 , w->len * sizeof(*w->bg_data));
}

void z__tui_Window_clear_ch(z__tui_Window *w, z__tui_char c)
{
    memset(w->ch_data, c, w->len * sizeof(*w->ch_data));
}

void z__tui_Window_clear_fg(z__tui_Window *w, z__u8 fg)
{
    memset(w->fg_data, fg, w->len * sizeof(*w->fg_data));
}

void z__tui_Window_clear_bg(z__tui_Window *w, z__u8 bg)
{
    memset(w->bg_data, bg, w->len * sizeof(*w->bg_data));
}

void z__tui_Window_clear_at(z__tui_Window *w, z__tui_attr at)
{
    memset(w->at_data, at, w->len * sizeof(*w->bg_data));
}

void z__tui_Window_draw_border(z__tui_Window *w, z__tui_char c, z__u8 fg, z__u8 bg)
{
    // top
    memset(w->ch_data, c, w->width - 1);
    memset(w->fg_data, fg, w->width - 1);
    memset(w->bg_data, bg, w->width - 1);

    // bottom
    size_t i = z__tui_Window_xy(w, 0, w->height - 1);
    memset(w->ch_data + i, c, w->width - 1);
    memset(w->fg_data + i, fg, w->width - 1);
    memset(w->bg_data + i, bg, w->width - 1);

    // left
    size_t y = 1;
    for (y = 0; y < w->height; y++) {
        i = z__tui_Window_xy(w, 0, y);
        z__tui_Window_draw_point_i(w, i, c, fg, bg);
    }

    // right
    y = 1;
    for (y = 0; y < w->height; y++) {
        i = z__tui_Window_xy(w, w->width - 1, y);
        z__tui_Window_draw_point_i(w, i, c, fg, bg);
    }
}

void z__tui_Window_draw_vline(z__tui_Window *w, z__u32 x, z__u32 y, z__u32 len, z__tui_char ch, z__u8 fg, z__u8 bg)
{
    z__u32 index = z__tui_Window_xy(w, x, y);
    len = z__min_unsafe(len + index, w->width);
    memset(w->ch_data + index, ch, len);
    memset(w->fg_data + index, fg, len);
    memset(w->bg_data + index, bg, len);
}

void z__tui_Window_draw_vline_bg(z__tui_Window *w, z__u32 x, z__u32 y, z__u32 len, z__u8 bg)
{
    z__u32 index = z__tui_Window_xy(w, x, y);
    len = z__min_unsafe(len + index, w->width);
    memset(w->bg_data + index, bg, len);
}

void z__tui_Window_draw_vline_fg(z__tui_Window *w, z__u32 x, z__u32 y, z__u32 len, z__u8 fg)
{
    z__u32 index = z__tui_Window_xy(w, x, y);
    len = z__min_unsafe(len + index, w->width);
    memset(w->fg_data + index, fg, len);
}

void z__tui_Window_draw_str(z__tui_Window *w, z__u32 const x, z__u32 const y, z__tui_char const *str, z__u32 len, z__u8 fg, z__u8 bg)
{
    z__u32 index = z__tui_Window_xy(w, x, y);
    len = z__min_unsafe(len, w->width);

    memcpy(w->ch_data + index, str, len * sizeof(*w->ch_data));
    memset(w->fg_data + index, fg , len);
    memset(w->bg_data + index, bg , len);
}

void z__tui_Window_draw_str_right(z__tui_Window *w, z__u32 const x_end, z__u32 const y, z__tui_char const *str, z__u32 len, z__u8 fg, z__u8 bg)
{
    len = z__min_unsafe(len, w->width);
    z__u32 const x = w->width - x_end - len;
    z__u32 index = z__tui_Window_xy(w, x, y);

    memcpy(w->ch_data + index, str, len * sizeof(*w->ch_data));
    memset(w->fg_data + index, fg , len);
    memset(w->bg_data + index, bg , len);
}

/*
int z__tui_Window_draw_strl_center(
    z__tui_Window *w, z__u32 x, z__u32 y, z__u32 width, z__u32 height
  , z__Str str, z__u32 highlight
  , z__u8 fg, z__u8 bg, z__u8 h_fg, z__u8 h_bg)
{
    if(x > w->width || y > w->height) return 0;

    // Clipping so we dont go out of screen;
    z__u32 const x1 = x + width;
    z__u32 const y1 = y + height;
    if(x1 > w->width) {
        width = w->width - x;
    }
    if(y1 > w->height) {
        height = w->height - y;
    }

    str.len = z__min_unsafe(str.len, height);
    char const *i = str.data;

    char const *i_end = i + str.len;
    char const *h = i + highlight;
    for (; i < i_end; i++, y++) {

        z__tui_char const * = str.data;
        z__u32 str_len = str.len;
        str_len = z__min_unsafe(str_len, width);

        z__u32 const wx = (width - str_len) >> 1;

        // Hightlight the selected string
        if (i == h) {
            z__tui_Window_draw_str(w, x + wx, y, str, str_len, h_fg, h_bg);
        } else {
            z__tui_Window_draw_str(w, x + wx, y, str, str_len, fg, bg);
        }
    }

    return 0;
}
*/


/************************************************************************
 *                              Display 
 ************************************************************************/
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


#endif //Z__IMPLEMENTATION
#endif

