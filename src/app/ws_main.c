/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: ws_main.c
 */
#include "ws_main.h"
#include "mrc_memory.h"
#include "mrc_console.h"

static ws_app_t* __create() {
    ws_app_t* app = (ws_app_t*)mrc_alloc(sizeof(ws_app_t));
    return app;
}

static void __do_static_init() { mrc_engine_static_init(); }
static void __do_static_term() { mrc_engine_static_term(); }

ws_app_t* ws_app_ctor() {
    __do_static_init();
    ws_app_t* app = __create();
    app->engine = mrc_engine_ctor();
    mrc_engine_add_module(app->engine, MRC_GRAPHICS);
    mrc_engine_add_module(app->engine, MRC_GRAPHICS_UI);
    // int r = mrc_engine_remove_module(app->engine, MRC_GRAPHICS);
    return app;
}

int ws_app_dtor(ws_app_t* app) {
    mrc_engine_dtor(app->engine);
    mrc_free(app);
    __do_static_term();
    return 0;
}

void ws_app_run(ws_app_t* app) { mrc_engine_run(app->engine); }