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

typedef struct cJSON cJSON;

typedef struct cls_vector_t {
    size_t length;
    size_t capacity;
    void **items;

} cls_vector_t;

extern void cls_vector_init(cls_vector_t *);
extern void cls_vector_init_capacity(cls_vector_t *, size_t);
extern int cls_vector_total(cls_vector_t *);
extern int cls_vector_capacity(cls_vector_t *);
// static void cls_vector_resize(cls_vector_t *, int);
extern unsigned int cls_vector_add(cls_vector_t *, void *);
extern void cls_vector_set(cls_vector_t *, unsigned int, void *);
extern void cls_vector_unset(cls_vector_t *, unsigned int);
extern void cls_vector_replace(cls_vector_t *, unsigned int, void *);
extern void *cls_vector_get(cls_vector_t *, unsigned int);
extern void cls_vector_delete(cls_vector_t *, unsigned int);
extern void cls_vector_free(cls_vector_t *);
extern void cls_vector_foreach(cls_vector_t *, cls_fn_v_vp_ui_vp_t, void *);
extern void cls_vector_insert_at(cls_vector_t *_vec, unsigned int _index,
                                 void *_data);
extern int cls_vector_insert_in_asc_order(cls_vector_t *_vec, void *_data,
                                          cls_fn_i_vp_vp_t _lessthan_fn);
extern int cls_vector_insert_in_desc_order(cls_vector_t *_vec, void *_data,
                                           cls_fn_i_vp_vp_t _lessthan_fn);
extern int cls_vector_asc_order_insert_pos(cls_vector_t *_vec, void *_data,
                                           cls_fn_i_vp_vp_t _lessthan_fn);
extern int cls_vector_desc_order_insert_pos(cls_vector_t *_vec, void *_data,
                                            cls_fn_i_vp_vp_t _lessthan_fn);
extern void *cls_vector_pop_back(cls_vector_t *_vec);

extern cJSON *cls_vector_serialize(cls_vector_t *_vec);

#endif    // __CLS_VECTOR_H
