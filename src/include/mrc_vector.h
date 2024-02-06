/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: mrc_vector.h
*/

#ifndef __MRC_VECTOR_H
#define __MRC_VECTOR_H

#include <stddef.h>

#define VECTOR_INIT_CAPACITY 4
#define VECTOR_REALLOC_ON_DELETE 1

typedef struct {
    size_t length;
    size_t capacity;
    void **items;

} mrc_vector_t;

void mrc_vector_init(mrc_vector_t *);
int mrc_vector_total(mrc_vector_t *);
static void mrc_vector_resize(mrc_vector_t *, int);
void mrc_vector_add(mrc_vector_t *, void *);
void mrc_vector_set(mrc_vector_t *, int, void *);
void *mrc_vector_get(mrc_vector_t *, int);
void mrc_vector_delete(mrc_vector_t *, int);
void mrc_vector_free(mrc_vector_t *);

#endif    // __MRC_VECTOR_H
