/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: ws_main.h
 */
#ifndef __WS_MAIN_H
#define __WS_MAIN_H

#include "merci_engine.h"

typedef struct {
    mrc_engine_t* engine;
} ws_app_t;

extern ws_app_t* ws_app_ctor();
extern int ws_app_dtor(ws_app_t* app);
extern void ws_app_run(ws_app_t* app);

#endif    // __WS_MAIN_H