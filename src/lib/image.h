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

#ifndef ZAKAROUF_IMAGE_H
#define ZAKAROUF_IMAGE_H

#include "std/primitives.h"
#include "arr.h"
#include "_export.h"

typedef struct z__Image z__Image;
struct z__Image {
	z__u32 *data;
	z__u32 width;
	z__u32 height;
	z__u32 stride;
};

Z__EXPORT z__Image z__Image_make(z__u32 *data, z__u32 width, z__u32 height, z__u32 stride);
Z__EXPORT z__Image z__Image_makesub(z__Image I, z__i32 x, z__i32 y, z__i32 w, z__i32 h);
Z__EXPORT z__u32 z__Image_to_ppm(z__Image const canvas, z__u8Arr *output);

Z__EXPORT void z__Image_fill(z__Image *canvas, z__u32 color);

Z__EXPORT bool z__Image_in_bounds(z__Image I, z__i32 x, z__i32 y);
Z__EXPORT void z__Image_blend_color(uint32_t *c1, uint32_t c2);

Z__EXPORT void z__Image_rect(z__Image I, z__i32 x, z__i32 y, z__i32 w, z__i32 h, uint32_t color);
Z__EXPORT void z__Image_frame(z__Image I, z__i32 x, z__i32 y, z__i32 w, z__i32 h, size_t thiccness, uint32_t color);

Z__EXPORT void z__Image_circle(z__Image I, z__i32 cx, z__i32 cy, z__i32 r, uint32_t color);
Z__EXPORT void z__Image_ellipse(z__Image I, z__i32 cx, z__i32 cy, z__i32 rx, z__i32 ry, uint32_t color);

// TODO: lines with different thiccness
Z__EXPORT void z__Image_line(z__Image I, z__i32 x1, z__i32 y1, z__i32 x2, z__i32 y2, uint32_t color);

Z__EXPORT bool z__Image_normalize_triangle(size_t width, size_t height, z__i32 x1, z__i32 y1, z__i32 x2, z__i32 y2, z__i32 x3, z__i32 y3, z__i32 *lx, z__i32 *hx, z__i32 *ly, z__i32 *hy);
Z__EXPORT bool z__Image_barycentric(z__i32 x1, z__i32 y1, z__i32 x2, z__i32 y2, z__i32 x3, z__i32 y3, z__i32 xp, z__i32 yp, z__i32 *u1, z__i32 *u2, z__i32 *det);
Z__EXPORT void z__Image_triangle(z__Image I, z__i32 x1, z__i32 y1, z__i32 x2, z__i32 y2, z__i32 x3, z__i32 y3, uint32_t color);
Z__EXPORT void z__Image_triangle3c(z__Image I, z__i32 x1, z__i32 y1, z__i32 x2, z__i32 y2, z__i32 x3, z__i32 y3, uint32_t c1, uint32_t c2, uint32_t c3);
Z__EXPORT void z__Image_triangle3z(z__Image I, z__i32 x1, z__i32 y1, z__i32 x2, z__i32 y2, z__i32 x3, z__i32 y3, float z1, float z2, float z3);
Z__EXPORT void z__Image_triangle3uv(z__Image I, z__i32 x1, z__i32 y1, z__i32 x2, z__i32 y2, z__i32 x3, z__i32 y3, float tx1, float ty1, float tx2, float ty2, float tx3, float ty3, float z1, float z2, float z3, z__Image texture);
Z__EXPORT void z__Image_triangle3uv_bilinear(z__Image I, z__i32 x1, z__i32 y1, z__i32 x2, z__i32 y2, z__i32 x3, z__i32 y3, float tx1, float ty1, float tx2, float ty2, float tx3, float ty3, float z1, float z2, float z3, z__Image texture);

Z__EXPORT void z__Image_sprite_blend(z__Image I, z__i32 x, z__i32 y, z__i32 w, z__i32 h, z__Image sprite);
Z__EXPORT void z__Image_sprite_copy(z__Image I, z__i32 x, z__i32 y, z__i32 w, z__i32 h, z__Image sprite);
Z__EXPORT void z__Image_sprite_copy_bilinear(z__Image I, z__i32 x, z__i32 y, z__i32 w, z__i32 h, z__Image sprite);
Z__EXPORT uint32_t z__Image_pixel_bilinear(z__Image sprite, z__i32 nx, z__i32 ny, z__i32 w, z__i32 h);

//Z__EXPORT void z__Image_text(z__Image I, const char *text, z__i32 x, z__i32 y, Olivec_Font font, size_t size, uint32_t color);

#define z__Image_PIXEL_GET(I, x, y) ((I).data[ z__xy2Dto1D(x, y, (I).stride) ])
#define z__Image_PIXEL_SET(I, x, y, v) { z__Image_PIXEL_GET(I, x, y) = v; }


// Color
#define z__Image_RED(color)   (((color)&0x000000FF)>>(8*0))
#define z__Image_GREEN(color) (((color)&0x0000FF00)>>(8*1))
#define z__Image_BLUE(color)  (((color)&0x00FF0000)>>(8*2))
#define z__Image_ALPHA(color) (((color)&0xFF000000)>>(8*3))
#define z__Image_RGBA(r, g, b, a) ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((a)&0xFF)<<(8*3)))

#ifdef Z__IMPLEMENTATION
#include "string.h"
#include "u8arr.h"
#include <inttypes.h>

z__Image z__Image_make(z__u32 *data, z__u32 width, z__u32 height, z__u32 stride)
{
	return (z__Image){data, width, height, stride};
}

void z__Image_fill(z__Image *canvas, z__u32 color)
{
	for (size_t i = 0; i < canvas->height * canvas->width; i++) {
		canvas->data[i] = color;
	}
}

z__u32 z__Image_to_ppm(z__Image const canvas, z__u8Arr *output)
{
	z__u8Arr_pushfmt(output, "P6\n%"PRIu32 " %"PRIu32" 255\n", canvas.width, canvas.height);
	for (size_t i = 0; i < canvas.width * canvas.height; i++) {
		z__u32 pixel = canvas.data[i];
		z__u8 rgb[] = { 
			(pixel>>(8*0))&0xff,
			(pixel>>(8*1))&0xff,
			(pixel>>(8*2))&0xff,
		};
		z__u8Arr_pushStream(output, rgb, sizeof(rgb));
	}
	return output->lenUsed;
}

#endif // Z__IMPLEMENTATION

#endif


