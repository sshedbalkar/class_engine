/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_vector.c
 */

#include "mrc_vector.h"
#include "mrc_memory.h"
#include "mrc_console.h"

void mrc_vector_init(mrc_vector_t *v) {
    v->capacity = VECTOR_INIT_CAPACITY;
    v->length = 0;
    v->items = mrc_alloc(sizeof(void *) * v->capacity);
}

void mrc_vector_init_capacity(mrc_vector_t *v, size_t capacity) {
    v->capacity = capacity;
    v->length = 0;
    if (capacity < 1) return;
    v->items = mrc_alloc(sizeof(void *) * v->capacity);
}

int mrc_vector_total(mrc_vector_t *v) { return v->length; }

int mrc_vector_capacity(mrc_vector_t *v) { return v->capacity; }

static void mrc_vector_resize(mrc_vector_t *v, size_t capacity) {
#ifdef DEBUG_ON
    mrc_print("mrc_vector_resize: %d to %d\n", v->capacity, capacity);
#endif

    void **items = mrc_realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void mrc_vector_add(mrc_vector_t *v, void *item) {
    if (v->capacity == v->length) {
        if (v->capacity == 0) v->capacity = 1;
        mrc_vector_resize(v, v->capacity * 2);
    }
    v->items[v->length++] = item;
}

void mrc_vector_set(mrc_vector_t *v, unsigned int index, void *item) {
    if (index < v->capacity) {
        v->items[index] = item;
        ++v->length;
    }
}

void mrc_vector_replace(mrc_vector_t *v, unsigned int index, void *item) {
    if (index < v->capacity) v->items[index] = item;
}

void *mrc_vector_get(mrc_vector_t *v, unsigned int index) {
    if (index < v->capacity) return v->items[index];
    return NULL;
}

void mrc_vector_delete(mrc_vector_t *v, unsigned int index) {
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
        mrc_vector_resize(v, v->capacity / 2);
#endif
}

void mrc_vector_free(mrc_vector_t *v) {
    mrc_free(v->items);
    v->length = 0;
    v->capacity = 0;
}

void mrc_vector_foreach(mrc_vector_t *v, mrc_fn_v_vp_t fn) {
    unsigned int i;
    for (i = 0; i < v->capacity; ++i) {
        (*fn)(v->items[i]);
    }
}