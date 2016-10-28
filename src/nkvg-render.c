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

#include "nkvg-render.h"
#include "font-registry.h"

#include <assert.h>

void nk_nanovg_render(struct nk_vg *nkvg, int w, int h)
{
    const struct nk_command *cmd = 0;
    NVGcontext *nvg_context      = nkvg->nkvg_ctx->nvg_context;

    nvgBeginFrame(nvg_context, w, h, 1.0f);

    nk_foreach(cmd, nkvg->nk_ctx)
    {
        switch (cmd->type) {
        case NK_COMMAND_SCISSOR: {
            const struct nk_command_scissor *s =
                (const struct nk_command_scissor *)cmd;
            nk_nanovg_scissor(nvg_context, s->x, s->y, s->w, s->h);
        } break;

        case NK_COMMAND_LINE: {
            const struct nk_command_line *l =
                (const struct nk_command_line *)cmd;
            nk_nanovg_stroke_line(nvg_context, l->begin.x, l->begin.y, l->end.x,
                                  l->end.y, l->line_thickness, l->color);
        } break;

        case NK_COMMAND_ARC: {
            const struct nk_command_arc *arc =
                (const struct nk_command_arc *)cmd;
            nk_nanovg_stroke_arc(nvg_context, arc->cx, arc->cy, arc->r,
                                 arc->a[0], arc->a[1], arc->line_thickness,
                                 arc->color);
        } break;

        case NK_COMMAND_ARC_FILLED: {
            const struct nk_command_arc_filled *arc =
                (const struct nk_command_arc_filled *)cmd;
            nk_nanovg_fill_arc(nvg_context, arc->cx, arc->cy, arc->r, arc->a[0],
                               arc->a[1], arc->color);
        } break;

        case NK_COMMAND_CURVE: {
            const struct nk_command_curve *q =
                (const struct nk_command_curve *)cmd;
            nk_nanovg_stroke_curve(nvg_context, q->begin.x, q->begin.y,
                                   q->ctrl[0].x, q->ctrl[0].y, q->ctrl[1].x,
                                   q->ctrl[1].y, q->end.x, q->end.y,
                                   q->line_thickness, q->color);
        } break;

        case NK_COMMAND_RECT: {
            const struct nk_command_rect *r =
                (const struct nk_command_rect *)cmd;
            nk_nanovg_stroke_rect(nvg_context, r->x, r->y, r->w, r->h,
                                  r->rounding, r->line_thickness, r->color);
        } break;

        case NK_COMMAND_RECT_FILLED: {
            const struct nk_command_rect_filled *r =
                (const struct nk_command_rect_filled *)cmd;
            nk_nanovg_fill_rect(nvg_context, r->x, r->y, r->w, r->h,
                                (unsigned short)r->rounding, r->color);
        } break;

        case NK_COMMAND_RECT_MULTI_COLOR: {
            const struct nk_command_rect_multi_color *r =
                (const struct nk_command_rect_multi_color *)cmd;
            nk_nanovg_fill_rect_multicolor(nvg_context, r->x, r->y, r->w, r->h,
                                           r->left, r->top, r->right,
                                           r->bottom);
        } break;

        case NK_COMMAND_CIRCLE: {
            const struct nk_command_circle *c =
                (const struct nk_command_circle *)cmd;
            nk_nanovg_stroke_circle(nvg_context, c->x, c->y, c->w, c->h,
                                    c->line_thickness, c->color);
        } break;

        case NK_COMMAND_CIRCLE_FILLED: {
            const struct nk_command_circle_filled *c =
                (const struct nk_command_circle_filled *)cmd;
            nk_nanovg_fill_circle(nvg_context, c->x, c->y, c->w, c->h,
                                  c->color);
        } break;

        case NK_COMMAND_TRIANGLE: {
            const struct nk_command_triangle *t =
                (const struct nk_command_triangle *)cmd;
            nk_nanovg_stroke_triangle(nvg_context, t->a.x, t->a.y, t->b.x,
                                      t->b.y, t->c.x, t->c.y, t->line_thickness,
                                      t->color);
        } break;

        case NK_COMMAND_TRIANGLE_FILLED: {
            const struct nk_command_triangle_filled *t =
                (const struct nk_command_triangle_filled *)cmd;
            nk_nanovg_fill_triangle(nvg_context, t->a.x, t->a.y, t->b.x, t->b.y,
                                    t->c.x, t->c.y, t->color);
        } break;

        case NK_COMMAND_POLYGON: {
            const struct nk_command_polygon *p =
                (const struct nk_command_polygon *)cmd;
            nk_nanovg_stroke_polygon(nvg_context, p->points, p->point_count,
                                     p->line_thickness, p->color);
        } break;

        case NK_COMMAND_POLYGON_FILLED: {
            const struct nk_command_polygon_filled *p =
                (const struct nk_command_polygon_filled *)cmd;
            nk_nanovg_fill_polygon(nvg_context, p->points, p->point_count,
                                   p->color);
        } break;

        case NK_COMMAND_POLYLINE: {
            const struct nk_command_polyline *p =
                (const struct nk_command_polyline *)cmd;
            nk_nanovg_stroke_polyline(nvg_context, p->points, p->point_count,
                                      p->line_thickness, p->color);
        } break;

        case NK_COMMAND_TEXT: {
            const struct nk_command_text *t =
                (const struct nk_command_text *)cmd;
            nk_nanovg_draw_text(nvg_context, t->font, t->x, t->y, t->w, t->h,
                                (const char *)t->string, t->length,
                                t->font->userdata, t->background,
                                t->foreground);
        } break;

        case NK_COMMAND_NOP:
            break;
        case NK_COMMAND_IMAGE:
        // fprintf(stderr, "unimplemented nk_command_xxx: %d\n", cmd->type);
        default:
            break;
        }
    }

    nvgEndFrame(nvg_context);
}

void nk_nanovg_scissor(NVGcontext *nvgctx, int x, int y, int w, int h)
{
    nvgScissor(nvgctx, x, y, w, h);
}

void nk_nanovg_stroke_line(NVGcontext *nvgctx, int sx, int sy, int dx, int dy,
                           int thickness, struct nk_color color)
{
    nvgBeginPath(nvgctx);
    nvgMoveTo(nvgctx, sx, sy);
    nvgLineTo(nvgctx, dx, dy);
    nvgStrokeColor(nvgctx, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgStrokeWidth(nvgctx, thickness);
    nvgStroke(nvgctx);
}

void nk_nanovg_stroke_curve(NVGcontext *nvgctx, int ax, int ay, int cx1,
                            int cy1, int cx2, int cy2, int bx, int by,
                            int thickness, struct nk_color color)
{
}

void nk_nanovg_stroke_arc(NVGcontext *nvgctx, int cx, int cy, int r, float a1,
                          float a2, int thickness, struct nk_color color)
{
    nvgBeginPath(nvgctx);
    nvgStrokeColor(nvgctx, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgStrokeWidth(nvgctx, thickness);
    /* TODO: implement */
    nvgArcTo(nvgctx, cx, cy, a1, a2, r);
    nvgStroke(nvgctx);
}

void nk_nanovg_fill_arc(NVGcontext *nvgctx, int cx, int cy, int r, float a1,
                        float a2, struct nk_color color)
{
    /* TODO: implement */
}

void nk_nanovg_stroke_rect(NVGcontext *nvgctx, int x, int y, int w, int h,
                           int rounding, int thickness, struct nk_color color)
{
    nvgBeginPath(nvgctx);
    nvgStrokeColor(nvgctx, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgStrokeWidth(nvgctx, thickness);
    nvgRoundedRect(nvgctx, x, y, w, h, rounding);
    nvgStroke(nvgctx);
}

void nk_nanovg_fill_rect(NVGcontext *nvgctx, int x, int y, int w, int h,
                         int rounding, struct nk_color color)
{
    nvgBeginPath(nvgctx);
    nvgFillColor(nvgctx, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgRoundedRect(nvgctx, x, y, w, h, rounding);
    nvgFill(nvgctx);
}

void nk_nanovg_fill_rect_multicolor(NVGcontext *nvgctx, int x, int y, int w,
                                    int h, struct nk_color left,
                                    struct nk_color top, struct nk_color right,
                                    struct nk_color bottom)
{
    struct nk_rect topleft_rect = nk_rect(x, y, w / 2, h / 2);
    NVGpaint topleft            = nvgLinearGradient(
        nvgctx, topleft_rect.x, topleft_rect.y, topleft_rect.w, topleft_rect.h,
        nvgRGBA(left.r, left.g, left.b, left.a),
        nvgRGBA(top.r, top.g, top.b, top.a));

    struct nk_rect topright_rect = nk_rect(x + w / 2, y, w / 2, h);
    NVGpaint topright            = nvgLinearGradient(
        nvgctx, topright_rect.x, topright_rect.y, topright_rect.w,
        topright_rect.h, nvgRGBA(top.r, top.g, top.b, top.a),
        nvgRGBA(right.r, right.g, right.b, right.a));

    /* TODO: implement */

    nvgBeginPath(nvgctx);
    nvgRect(nvgctx, topleft_rect.x, topleft_rect.y, topleft_rect.w,
            topleft_rect.h);
    nvgFillPaint(nvgctx, topleft);
    nvgFill(nvgctx);

    nvgFillPaint(nvgctx, topleft);
    nvgRect(nvgctx, topright_rect.x, topright_rect.y, topright_rect.w,
            topright_rect.h);
    nvgFill(nvgctx);
}

void nk_nanovg_stroke_circle(NVGcontext *nvgctx, int x, int y, int w, int h,
                             int thickness, struct nk_color color)
{
    nvgBeginPath(nvgctx);
    nvgStrokeColor(nvgctx, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgStrokeWidth(nvgctx, thickness);
    float cx = x + w / 2.0f;
    float cy = y + h / 2.0f;
    nvgEllipse(nvgctx, cx, cy, w / 2.0f, h / 2.0f);
    nvgStroke(nvgctx);
}

void nk_nanovg_fill_circle(NVGcontext *nvgctx, int x, int y, int w, int h,
                           struct nk_color color)
{
    nvgBeginPath(nvgctx);
    nvgFillColor(nvgctx, nvgRGBA(color.r, color.g, color.b, color.a));
    float cx = x + w / 2.0f;
    float cy = y + h / 2.0f;
    nvgEllipse(nvgctx, cx, cy, w / 2.0f, h / 2.0f);
    nvgFill(nvgctx);
}

void nk_nanovg_stroke_triangle(NVGcontext *nvgctx, int ax, int ay, int bx,
                               int by, int cx, int cy, int thickness,
                               struct nk_color color)
{
    nvgBeginPath(nvgctx);
    nvgStrokeColor(nvgctx, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgStrokeWidth(nvgctx, thickness);
    nvgMoveTo(nvgctx, ax, ay);
    nvgLineTo(nvgctx, bx, by);
    nvgLineTo(nvgctx, cx, cy);
    nvgClosePath(nvgctx);
    nvgStroke(nvgctx);
}

void nk_nanovg_fill_triangle(NVGcontext *nvgctx, int ax, int ay, int bx, int by,
                             int cx, int cy, struct nk_color color)
{
    nvgBeginPath(nvgctx);
    nvgFillColor(nvgctx, nvgRGBA(color.r, color.g, color.b, color.a));
    nvgMoveTo(nvgctx, ax, ay);
    nvgLineTo(nvgctx, bx, by);
    nvgLineTo(nvgctx, cx, cy);
    nvgClosePath(nvgctx);
    nvgFill(nvgctx);
}

void nk_nanovg_stroke_polygon(NVGcontext *nvgctx, const struct nk_vec2i *points,
                              int point_count, int thickness,
                              struct nk_color color)
{
    /* TODO: implement*/
}

void nk_nanovg_fill_polygon(NVGcontext *nvgctx, const struct nk_vec2i *points,
                            int point_count, struct nk_color color)
{
    /* TODO: implement*/
}

void nk_nanovg_stroke_polyline(NVGcontext *nvgctx,
                               const struct nk_vec2i *points, int point_count,
                               int thickness, struct nk_color color)
{
    /* TODO: implement*/
}

void nk_nanovg_draw_text(NVGcontext *nvgctx, const struct nk_user_font *font,
                         int x, int y, int w, int h, const char *text,
                         int length, nk_handle handle, struct nk_color bg,
                         struct nk_color fg)
{
    nvgBeginPath(nvgctx);
    nvgFillColor(nvgctx, nvgRGBA(bg.r, bg.g, bg.b, bg.a));
    nvgRect(nvgctx, x, y, w, h);
    nvgFill(nvgctx);
    nvgFillColor(nvgctx, nvgRGBA(fg.r, fg.g, fg.b, fg.a));
    nvgFontSize(nvgctx, font->height);
    nvgFontFace(nvgctx, "default");
    nvgTextAlign(nvgctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
    float bounds[4];
    nvgText(nvgctx, x, y, text, text + length);
}
