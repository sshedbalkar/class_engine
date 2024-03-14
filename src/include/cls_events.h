/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_events.h
 */
#ifndef __CLS_EVENTS_H
#define __CLS_EVENTS_H

#include "cls_types.h"
#include "cls_list_core_events.h"

extern void cls_events_static_init();
extern void cls_events_static_term();
extern int cls_events_reg_callback(unsigned int, cls_fn_v_v_t);
extern int cls_events_unreg_callback(unsigned int, cls_fn_v_v_t);
extern int cls_events_trigger_event(unsigned int _evt);

#endif    // __CLS_EVENTS_H