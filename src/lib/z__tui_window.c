#include <stdlib.h>

#include "string.h"
#include "tui.h"
#include "std/mem.h"
#include "std/alloc.h"
#include "utils.h"

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
    len = z__min(len, w->width);

    memcpy(w->ch_data + index, str, len * sizeof(*w->ch_data));
    memset(w->fg_data + index, fg , len);
    memset(w->bg_data + index, bg , len);
}

void z__tui_Window_draw_str_right(z__tui_Window *w, z__u32 const x_end, z__u32 const y, z__tui_char const *str, z__u32 len, z__u8 fg, z__u8 bg)
{
    len = z__min(len, w->width);
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

