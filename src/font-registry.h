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

#ifndef FONT_REGISTRY_H
#define FONT_REGISTRY_H

#pragma once

struct font_registry;

struct font_description {
    /* User-defined id of font*/
    const char *id;

    struct NVGcontext *nvgctx;

    /* NanoVG font handle */
    int handle;

    /* Default size */
    int height;
};

int font_registry_create(struct NVGcontext *nvgctx, struct font_registry **out);
void font_registry_destroy(struct font_registry **out);

int font_registry_add_font(struct font_registry *registry, const char *id,
                           int handle, int default_height);

struct font_description *font_registry_find_font(struct font_registry *registry,
                                                 const char *id);

#endif /* FONT_REGISTRY_H */
