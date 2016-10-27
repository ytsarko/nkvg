/*
 * Copyright (c) 2016 Yaroslav Tsarko eriktsarko@gmail.com

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
 * EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef NKVG_RENDER_H
#define NKVG_RENDER_H

#pragma once

#include "nkvg.h"

#include <nanovg.h>

#ifdef __cplusplus
extern "C" {
#endif

void nk_nanovg_render(struct nk_vg *nkvg, int w, int h);

void nk_nanovg_scissor(NVGcontext *nvgctx, int x, int y, int w, int h);

void nk_nanovg_stroke_line(NVGcontext *nvgctx, int sx, int sy, int dx, int dy,
                           int thickness, struct nk_color color);

void nk_nanovg_stroke_line(NVGcontext *nvgctx, int sx, int sy, int dx, int dy,
                           int thickness, struct nk_color color);

void nk_nanovg_stroke_curve(NVGcontext *nvgctx, int ax, int ay, int cx1,
                            int cy1, int cx2, int cy2, int bx, int by,
                            int thickness, struct nk_color color);

void nk_nanovg_stroke_arc(NVGcontext *nvgctx, int cx, int cy, int r, float a1,
                          float a2, int thickness, struct nk_color color);

void nk_nanovg_fill_arc(NVGcontext *nvgctx, int cx, int cy, int r, float a1,
                        float a2, struct nk_color color);

void nk_nanovg_stroke_rect(NVGcontext *nvgctx, int x, int y, int w, int h,
                           int rounding, int thickness, struct nk_color color);

void nk_nanovg_fill_rect(NVGcontext *nvgctx, int x, int y, int w, int h,
                         int rounding, struct nk_color color);

void nk_nanovg_fill_rect_multicolor(NVGcontext *nvgctx, int x, int y, int w,
                                    int h, struct nk_color left,
                                    struct nk_color top, struct nk_color right,
                                    struct nk_color bottom);

void nk_nanovg_stroke_circle(NVGcontext *nvgctx, int x, int y, int w, int h,
                             int thickness, struct nk_color color);

void nk_nanovg_fill_circle(NVGcontext *nvgctx, int x, int y, int w, int h,
                           struct nk_color color);

void nk_nanovg_stroke_triangle(NVGcontext *nvgctx, int ax, int ay, int bx,
                               int by, int cx, int cy, int thickness,
                               struct nk_color color);

void nk_nanovg_fill_triangle(NVGcontext *nvgctx, int ax, int ay, int bx, int by,
                             int cx, int cy, struct nk_color color);

void nk_nanovg_stroke_polygon(NVGcontext *nvgctx, const struct nk_vec2i *points,
                              int point_count, int thickness,
                              struct nk_color color);

void nk_nanovg_fill_polygon(NVGcontext *nvgctx, const struct nk_vec2i *points,
                            int point_count, struct nk_color color);

void nk_nanovg_stroke_polyline(NVGcontext *nvgctx,
                               const struct nk_vec2i *points, int point_count,
                               int thickness, struct nk_color color);

void nk_nanovg_draw_text(NVGcontext *nvgctx, int x, int y, int w, int h,
                         const char *text, int length, nk_handle handle,
                         struct nk_color bg, struct nk_color fg);

#ifdef __cplusplus
}
#endif

#endif /* NKVG_RENDER_H */
