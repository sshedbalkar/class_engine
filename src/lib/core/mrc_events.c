/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_events.c
 */

#include "mrc_defines.h"
#include "mrc_memory.h"
#include "mrc_vector.h"
#include "mrc_events.h"
#include "mrc_list_core_events.h"
#include "mrc_utils.h"
#include "mrc_console.h"

static mrc_vector_t __events_map;

static void __unreg_event(mrc_vector_t* _cbs, unsigned int _index,
                          void* _param) {
    (void)_param;
    if (_cbs == NULL) return;
    mrc_vector_free(_cbs);
    mrc_free(_cbs);
    mrc_vector_set(&__events_map, _index, NULL);
}

static inline void __unreg_callback(mrc_fn_v_v_t _cb2, unsigned int _index,
                                    mrc_fn_v_v_t _cb1) {
    if (_cb1 == _cb2) {
        mrc_vector_set(&__events_map, _index, NULL);
    }
}

static inline void __trigger_callback(mrc_fn_v_v_t _cb, unsigned int _index,
                                      void* _param) {
    (void)_index;
    (void)_param;
    if (_cb != NULL) _cb();
}

void mrc_events_static_init() {
    mrc_vector_init_capacity(&__events_map, MRC_EVENTS_COUNT_MAX);
}

void mrc_events_static_term() {
    mrc_vector_foreach(&__events_map, (mrc_fn_v_vp_ui_vp_t)&__unreg_event,
                       NULL);
    mrc_vector_free(&__events_map);
}

int mrc_events_reg_callback(unsigned int _evt, mrc_fn_v_v_t _cb) {
    mrc_vector_t* _cbs = (mrc_vector_t*)mrc_vector_get(&__events_map, _evt);
    if (_cbs == NULL) {
        _cbs = mrc_alloc(sizeof(mrc_vector_t));
        mrc_vector_init_capacity(_cbs, MRC_EVENTS_CALLBACKS_PER_EVENT_COUNT);
        mrc_vector_set(&__events_map, _evt, _cbs);
    }
    mrc_vector_add(_cbs, _cb);
    return 0;
}

int mrc_events_unreg_callback(unsigned int _evt, mrc_fn_v_v_t _cb1) {
    mrc_vector_t* _cbs = (mrc_vector_t*)mrc_vector_get(&__events_map, _evt);
    if (_cbs != NULL) {
        mrc_vector_foreach(_cbs, (mrc_fn_v_vp_ui_vp_t)&__unreg_callback, _cb1);
        return 0;
    }
    return 1;
}

int mrc_events_trigger_event(unsigned int _evt) {
    mrc_vector_t* _cbs = (mrc_vector_t*)mrc_vector_get(&__events_map, _evt);
    if (_cbs != NULL) {
        mrc_vector_foreach(_cbs, (mrc_fn_v_vp_ui_vp_t)&__trigger_callback,
                           NULL);
        return 0;
    }
    return 1;
}