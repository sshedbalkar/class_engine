/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: mrc_vector.h
*/

#ifndef __MRC_VECTOR_H
#define __MRC_VECTOR_H

#include <stddef.h>
#include "mrc_types.h"

#define VECTOR_INIT_CAPACITY 4
#define VECTOR_REALLOC_ON_DELETE

typedef struct {
    size_t length;
    size_t capacity;
    void **items;

} mrc_vector_t;

void mrc_vector_init(mrc_vector_t *);
void mrc_vector_init_capacity(mrc_vector_t *, size_t);
int mrc_vector_total(mrc_vector_t *);
int mrc_vector_capacity(mrc_vector_t *);
// static void mrc_vector_resize(mrc_vector_t *, int);
unsigned int mrc_vector_add(mrc_vector_t *, void *);
void mrc_vector_set(mrc_vector_t *, unsigned int, void *);
void mrc_vector_unset(mrc_vector_t *, unsigned int);
void mrc_vector_replace(mrc_vector_t *, unsigned int, void *);
void *mrc_vector_get(mrc_vector_t *, unsigned int);
void mrc_vector_delete(mrc_vector_t *, unsigned int);
void mrc_vector_free(mrc_vector_t *);
void mrc_vector_foreach(mrc_vector_t *, mrc_fn_v_vp_ui_vp_t, void *);

#endif    // __MRC_VECTOR_H
