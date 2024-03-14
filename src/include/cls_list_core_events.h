/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_list_core_events.h
 */

#ifndef __CLS_LIST_CORE_EVENTS_H
#define __CLS_LIST_CORE_EVENTS_H

typedef enum {
    CLS_EVT_FRAME_ENTER = 0,
    CLS_EVT_TIMER,
    CLS_EVT_QUIT_WINDOW,
    CLS_EVT_QUIT,
    CLS_EVT_SDL_EVENT,
    CLS_EVT_THRD_CREATE,
    //
    CLS_EVT_MAX
} cls_events_t;

#endif    // __CLS_LIST_CORE_EVENTS_H