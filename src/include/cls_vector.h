/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: cls_vector.h
*/

#ifndef __CLS_VECTOR_H
#define __CLS_VECTOR_H

#include <stddef.h>
#include "cls_types.h"

#define VECTOR_INIT_CAPACITY 4
#define VECTOR_REALLOC_ON_DELETE

typedef struct cls_vector_t {
    size_t length;
    size_t capacity;
    void **items;

} cls_vector_t;

void cls_vector_init(cls_vector_t *);
void cls_vector_init_capacity(cls_vector_t *, size_t);
int cls_vector_total(cls_vector_t *);
int cls_vector_capacity(cls_vector_t *);
// static void cls_vector_resize(cls_vector_t *, int);
unsigned int cls_vector_add(cls_vector_t *, void *);
void cls_vector_set(cls_vector_t *, unsigned int, void *);
void cls_vector_unset(cls_vector_t *, unsigned int);
void cls_vector_replace(cls_vector_t *, unsigned int, void *);
void *cls_vector_get(cls_vector_t *, unsigned int);
void cls_vector_delete(cls_vector_t *, unsigned int);
void cls_vector_free(cls_vector_t *);
void cls_vector_foreach(cls_vector_t *, cls_fn_v_vp_ui_vp_t, void *);

#endif    // __CLS_VECTOR_H
