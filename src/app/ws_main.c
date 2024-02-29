/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: ws_main.c
 */
#include "ws_main.h"
#include "cls_memory.h"
#include "cls_console.h"

static ws_app_t* __create() {
    ws_app_t* app = (ws_app_t*)cls_alloc(sizeof(ws_app_t));
    return app;
}

static void __do_static_init() { cls_engine_static_init(); }
static void __do_static_term() { cls_engine_static_term(); }

ws_app_t* ws_app_ctor() {
    __do_static_init();
    ws_app_t* app = __create();
    app->engine = cls_engine_ctor();
    cls_engine_add_module(app->engine, CLS_GRAPHICS);
    cls_engine_add_module(app->engine, CLS_GRAPHICS_UI);
    // int r = cls_engine_remove_module(app->engine, CLS_GRAPHICS);
    return app;
}

int ws_app_dtor(ws_app_t* app) {
    cls_engine_dtor(app->engine);
    cls_free(app);
    __do_static_term();
    return 0;
}

void ws_app_run(ws_app_t* app) { cls_engine_run(app->engine); }