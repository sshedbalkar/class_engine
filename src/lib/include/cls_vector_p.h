/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_vector_p.h
 */

#ifndef __CLS_VECTOR_P_H
#define __CLS_VECTOR_P_H

#include <stddef.h>

typedef struct cls_vector_t cls_vector_t;

extern void cls_vector_init_p(cls_vector_t *v);
extern void cls_vector_init_capacity_p(cls_vector_t *v, size_t capacity);
extern unsigned int cls_vector_add_p(cls_vector_t *v, void *item);
extern void cls_vector_delete_p(cls_vector_t *v, unsigned int index);
extern void cls_vector_free_p(cls_vector_t *v);
extern void cls_vector_insert_at_p(cls_vector_t *_vec, unsigned int _index,
                                   void *_data);
#endif    // __CLS_VECTOR_P_H