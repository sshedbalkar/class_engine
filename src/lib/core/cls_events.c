/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_events.c
 */

#include "cls_defines.h"
#include "cls_memory.h"
#include "cls_vector.h"
#include "cls_events.h"
#include "cls_list_core_events.h"
#include "cls_utils.h"
#include "cls_console.h"

static cls_vector_t __events_map;

static void __unreg_event(cls_vector_t* _cbs, unsigned int _index,
                          void* _param) {
    (void)_param;
    if (_cbs == NULL) return;
    cls_vector_free(_cbs);
    cls_free(_cbs);
    cls_vector_unset(&__events_map, _index);
}

static inline void __unreg_callback(cls_fn_v_v_t _cb2, unsigned int _index,
                                    cls_fn_v_v_t _cb1) {
    if (_cb1 == _cb2) {
        cls_vector_unset(&__events_map, _index);
    }
}

static inline void __trigger_callback(cls_fn_v_v_t _cb, unsigned int _index,
                                      void* _param) {
    (void)_index;
    (void)_param;
    if (_cb != NULL) _cb();
}

void cls_events_static_init() {
    cls_vector_init_capacity(&__events_map, CLS_EVENTS_COUNT_MAX);
}

void cls_events_static_term() {
    cls_vector_foreach(&__events_map, (cls_fn_v_vp_ui_vp_t)&__unreg_event,
                       NULL);
    cls_vector_free(&__events_map);
}

int cls_events_reg_callback(unsigned int _evt, cls_fn_v_v_t _cb) {
    cls_vector_t* _cbs = (cls_vector_t*)cls_vector_get(&__events_map, _evt);
    if (_cbs == NULL) {
        _cbs = cls_alloc(sizeof(cls_vector_t));
        cls_vector_init_capacity(_cbs, CLS_EVENTS_CALLBACKS_PER_EVENT_COUNT);
        cls_vector_set(&__events_map, _evt, _cbs);
    }
    cls_vector_add(_cbs, _cb);
    return 0;
}

int cls_events_unreg_callback(unsigned int _evt, cls_fn_v_v_t _cb1) {
    cls_vector_t* _cbs = (cls_vector_t*)cls_vector_get(&__events_map, _evt);
    if (_cbs != NULL) {
        cls_vector_foreach(_cbs, (cls_fn_v_vp_ui_vp_t)&__unreg_callback, _cb1);
        return 0;
    }
    return 1;
}

int cls_events_trigger_event(unsigned int _evt) {
    cls_vector_t* _cbs = (cls_vector_t*)cls_vector_get(&__events_map, _evt);
    if (_cbs != NULL) {
        cls_vector_foreach(_cbs, (cls_fn_v_vp_ui_vp_t)&__trigger_callback,
                           NULL);
        return 0;
    }
    return 1;
}