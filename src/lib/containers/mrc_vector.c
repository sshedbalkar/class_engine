/*
Copyright (c) Santosh Shedbalkar
Year: 2024 - 2024
All rights reserved

File: mrc_vector.c
*/
#include "mrc_vector.h"
#include "mrc_memory.h"
#include "mrc_console.h"

void mrc_vector_init(mrc_vector_t *v) {
    v->capacity = VECTOR_INIT_CAPACITY;
    v->length = 0;
    v->items = mrc_alloc(sizeof(void *) * v->capacity);
    mrc_print("mrc_vector_init\n");
}

void mrc_vector_init_capacity(mrc_vector_t *v, size_t capacity) {
    v->capacity = capacity;
    v->length = 0;
    if (capacity < 1) return;
    v->items = mrc_alloc(sizeof(void *) * v->capacity);
    mrc_print("mrc_vector_init_capacity\n");
}

int mrc_vector_total(mrc_vector_t *v) { return v->length; }

static void mrc_vector_resize(mrc_vector_t *v, int capacity) {
#ifdef DEBUG_ON
    mrc_print("mrc_vector_resize: %d to %d\n", v->capacity, capacity);
#endif

    void **items = mrc_realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
    mrc_print("mrc_vector_resize: new: %d\n", capacity);
}

void mrc_vector_add(mrc_vector_t *v, void *item) {
    if (v->capacity == v->length) {
        if (v->capacity == 0) v->capacity = 1;
        mrc_vector_resize(v, v->capacity * 2);
    }
    v->items[v->length++] = item;
    mrc_print("mrc_vector_add: %d\n", v->length);
}

void mrc_vector_set(mrc_vector_t *v, int index, void *item) {
    if (index >= 0 && index < v->length) v->items[index] = item;
    mrc_print("mrc_vector_set at: %d\n", index);
}

void *mrc_vector_get(mrc_vector_t *v, int index) {
    if (index >= 0 && index < v->length) return v->items[index];
    mrc_print("mrc_vector_get at: %d\n", index);
    return NULL;
}

void mrc_vector_delete(mrc_vector_t *v, int index) {
    if (index < 0 || index >= v->length) return;

    // v->items[index] = NULL;
    // int i;
    // for (i = 0; i < v->length - 1; i++) {
    //     v->items[i] = v->items[i + 1];
    //     v->items[i + 1] = NULL;
    // }
    int i;
    for (i = index; i < v->length - 1; ++i) {
        v->items[i] = v->items[i + 1];
    }
    --v->length;
    mrc_print("mrc_vector_delete at: %d, len: %d\n", index, v->length);
#ifdef VECTOR_REALLOC_ON_DELETE
    if (v->length > 0 && v->length == v->capacity / 4)
        mrc_vector_resize(v, v->capacity / 2);
#endif
}

void mrc_vector_free(mrc_vector_t *v) {
    mrc_free(v->items);
    v->length = 0;
    v->capacity = 0;
    mrc_print("mrc_vector_free\n");
}

void mrc_vector_foreach(mrc_vector_t *v, mrc_fn_v_vp_t fn) {
    int i;
    mrc_print("mrc_vector_foreach\n");
    for (i = 0; i < v->length; ++i) {
        (*fn)(v->items[i]);
    }
}