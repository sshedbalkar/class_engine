/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_threads.c
 */
#include <pthread.h>
#include "cls_vector.h"
#include "cls_error.h"
#include "cls_data_container.h"
#include "cls_events.h"
#include "cls_threads.h"

#ifdef CLS_DEBUG
#include "cls_console.h"
#endif

static cls_vector_t __threads;

unsigned int CLS_H_THRD_CREATE_OBJ;

void __thread_join(void* _thread, unsigned int _index, void* _user_data) {
    (void)_index;
    (void)_user_data;
    if (pthread_join((pthread_t)_thread, NULL)) {
        cls_error_set(CLS_ERROR_FATAL, CLS_ERR_ID_THREAD_COULD_NOT_JOIN,
                      "Thread could not join");
#ifdef CLS_DEBUG
        cls_print("[THRD]: Could not join\n");
#endif
    }
}

void __on_thread_create() {
    cls_thrd_create_t* _obj = cls_data_container_get(CLS_H_THRD_CREATE_OBJ);
    pthread_t _thread;
    int _result =
        pthread_create(&_thread, NULL, _obj->fn_body, _obj->user_data);
    if (_result) {
        cls_error_set(CLS_ERROR_FATAL, CLS_ERR_ID_THREAD_COULD_NOT_CREATE,
                      "Thread could not create");
#ifdef CLS_DEBUG
        cls_print("[THRD]: Could not create\n");
#endif
    } else {
        cls_vector_add(&__threads, (void*)_thread);
    }
    cls_data_container_remove(CLS_H_THRD_CREATE_OBJ);
}

void cls_threads_static_init() {
    cls_vector_init_capacity(&__threads, 8);
    cls_events_reg_callback(CLS_EVT_THRD_CREATE, __on_thread_create);
}

void cls_threads_static_term() {
    cls_events_unreg_callback(CLS_EVT_THRD_CREATE, __on_thread_create);
    cls_vector_foreach(&__threads, __thread_join, NULL);
    cls_vector_free(&__threads);
}
