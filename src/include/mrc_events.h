/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_events.h
 */
#ifndef __MRC_EVENTS_H
#define __MRC_EVENTS_H

#include "mrc_types.h"

extern void mrc_events_static_init();
extern void mrc_events_static_term();
extern int mrc_events_reg_callback(unsigned int, mrc_fn_v_v_t);
extern int mrc_events_unreg_callback(unsigned int, mrc_fn_v_v_t);
extern int mrc_events_trigger_event(unsigned int _evt);

#endif    // __MRC_EVENTS_H