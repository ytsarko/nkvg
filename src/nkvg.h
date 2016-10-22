/*
 * Copyright (c) 2016 Yaroslav Tsarko eriktsarko@gmail.com

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
 * EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef NKVG_H
#define NKVG_H

#pragma once

#include <nanovg.h>

#include "nuklear.h"

struct nk_vg {
    struct nk_vg_context *nkvg_ctx;
    struct nk_context *nk_ctx;
};

int nk_vg_create(struct nk_context *nk_ctx, struct nk_vg **out);
void nk_vg_destroy(struct nk_vg **nkvg);

NVGcontext *nk_vg_context(struct nk_vg *nkvg);

int nk_vg_add_font(struct nk_vg *nkvg, const char *id, const char *filename);

void nk_vg_render(struct nk_vg *nkvg, struct nk_color bg, int w, int h);

#endif /* NKVG_H */
