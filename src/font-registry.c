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

#include "font-registry.h"

#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

struct font_registry_node {
    struct font_description value;
    struct font_registry_node *next;
};

struct font_registry {
    struct NVGcontext *nvgctx;
    struct font_registry_node *head;
};

int font_registry_create(struct NVGcontext *nvgctx, struct font_registry **out)
{
    assert(nvgctx);
    assert(out);

    int ret = 0;
    struct font_registry *reg = 0;

    *out = 0;

    reg = calloc(1, sizeof(*reg));
    if (!reg) {
        return ENOMEM;
    }

    reg->nvgctx = nvgctx;

    *out = reg;

    return 0;
}

void font_registry_destroy(struct font_registry **out)
{
    assert(out);

    struct font_registry *registry = *out;
    assert(registry);

    struct font_registry_node *node = registry->head;
    while (node) {
        struct font_registry_node *tmp = node;
        free((void*)tmp->value.id);

        node = node->next;

        free(tmp);
    }

    free(registry);

    *out = 0;
}

int font_registry_add_font(struct font_registry *registry, const char *id,
                           int handle, int default_height)
{
    assert(registry);
    assert(id);

    int len = strlen(id);
    char *mem = calloc(len + 1, sizeof(char));
    if (!mem) {
        return ENOMEM;
    }

    strncpy(mem, id, len);

    struct font_description desc = {
        .id = mem,
        .nvgctx = registry->nvgctx,
        .handle = handle,
        .height = default_height,
    };

    struct font_registry_node *new_node = calloc(1, sizeof(*new_node));
    if (!new_node) {
        free(mem);
        return ENOMEM;
    }

    new_node->value = desc;

    struct font_registry_node *node = registry->head;
    if (!node) {
        registry->head = new_node;
    } else {
        while (node) {
            if (node->next == 0) {
                node->next = new_node;
                return 0;
            }
            node = node->next;
        }
    }

    return 0;
}

struct font_description *font_registry_find_font(struct font_registry *registry,
                                                 const char *id)
{
    assert(registry);
    assert(id);

    struct font_registry_node *node = registry->head;
    while (node) {
        if (strcmp(node->value.id, id) == 0) {
            return &node->value;
        }

        node = node->next;
    }

    return 0;
}
