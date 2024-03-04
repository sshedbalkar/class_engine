/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_vector.c
 */

#include "cls_vector.h"
#include "cls_memory.h"
#include "cls_console.h"

void cls_vector_init(cls_vector_t *v) {
    cls_vector_init_capacity(v, VECTOR_INIT_CAPACITY);
}

void cls_vector_init_capacity(cls_vector_t *v, size_t capacity) {
    v->capacity = capacity;
    v->length = 0;
    if (capacity < 1) return;
    size_t _sz = sizeof(void *) * v->capacity;
    v->items = cls_alloc(_sz);
    cls_memset(v->items, 0, _sz);
}

int cls_vector_total(cls_vector_t *v) { return v->length; }

int cls_vector_capacity(cls_vector_t *v) { return v->capacity; }

static void cls_vector_resize(cls_vector_t *v, size_t capacity) {
#ifdef DEBUG_ON
    cls_print("cls_vector_resize: %d to %d\n", v->capacity, capacity);
#endif

    void **items = cls_realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

unsigned int cls_vector_add(cls_vector_t *v, void *item) {
    if (v->capacity == v->length) {
        if (v->capacity == 0) v->capacity = 1;
        cls_vector_resize(v, v->capacity * 2);
    }
    v->items[v->length++] = item;
    return v->length;
}

void cls_vector_set(cls_vector_t *v, unsigned int index, void *item) {
    if (index < v->capacity) {
        v->items[index] = item;
        ++v->length;
    }
}

void cls_vector_unset(cls_vector_t *v, unsigned int index) {
    if (index < v->capacity) {
        v->items[index] = NULL;
        --v->length;
    }
}

void cls_vector_replace(cls_vector_t *v, unsigned int index, void *item) {
    if (index < v->capacity) v->items[index] = item;
}

void *cls_vector_get(cls_vector_t *v, unsigned int index) {
    if (index < v->capacity) return v->items[index];
    return NULL;
}

void cls_vector_delete(cls_vector_t *v, unsigned int index) {
    if (index >= v->length) return;

    // v->items[index] = NULL;
    // int i;
    // for (i = 0; i < v->length - 1; i++) {
    //     v->items[i] = v->items[i + 1];
    //     v->items[i + 1] = NULL;
    // }
    unsigned int i;
    for (i = index; i < v->length - 1; ++i) {
        v->items[i] = v->items[i + 1];
    }
    --v->length;
#ifdef VECTOR_REALLOC_ON_DELETE
    if (v->length > 0 && v->length == v->capacity / 4)
        cls_vector_resize(v, v->capacity / 2);
#endif
}

void cls_vector_free(cls_vector_t *v) {
    cls_free(v->items);
    v->length = 0;
    v->capacity = 0;
}

void cls_vector_foreach(cls_vector_t *_v, cls_fn_v_vp_ui_vp_t _fn,
                        void *_param) {
    unsigned int _i;
    for (_i = 0; _i < _v->capacity; ++_i) {
        (*_fn)(_v->items[_i], _i, _param);
    }
}