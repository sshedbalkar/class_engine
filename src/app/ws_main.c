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
#include "cls_graphics.h"

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
    cls_graphics_t* _gra =
        (cls_graphics_t*)cls_engine_add_module(app->engine, CLS_GRAPHICS);
    cls_graphics_add_module(_gra, CLS_GRAPHICS_UI);
    // cls_engine_add_module(app->engine, CLS_GRAPHICS_UI);
    //  int r = cls_engine_remove_module(app->engine, CLS_GRAPHICS);
    const char* str = cls_engine_serialize(app->engine);
    cls_print("ENGINE: %s\n", str);
    return app;
}

int ws_app_dtor(ws_app_t* app) {
    cls_engine_dtor(app->engine);
    cls_free(app);
    __do_static_term();
    return 0;
}

void ws_app_run(ws_app_t* app) { cls_engine_run(app->engine); }