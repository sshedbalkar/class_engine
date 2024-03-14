/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_threads.h
 */
#ifndef __CLS_THREADS_H
#define __CLS_THREADS_H

#include "cls_types.h"

typedef struct cls_thrd_create_t {
    cls_fn_vp_vp_t fn_body;
    void* user_data;
} cls_thrd_create_t;

extern void cls_threads_static_init();
extern void cls_threads_static_term();
#endif    // __CLS_THREADS_H