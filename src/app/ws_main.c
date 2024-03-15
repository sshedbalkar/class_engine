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
#include "cls_ui.h"
#include "cls_modules.h"

static ws_app_t* __create() {
    ws_app_t* _app = (ws_app_t*)cls_alloc(sizeof(ws_app_t));
    return _app;
}

static void __do_static_init() {
    cls_engine_static_init();
    cls_modules_static_register_module_type(cls_graphics_static_init());
    cls_modules_static_register_module_type(cls_ui_static_init());
}
static void __do_static_term() {
    cls_ui_static_term();
    cls_graphics_static_term();
    cls_engine_static_term();
}

ws_app_t* ws_app_ctor() {
    __do_static_init();
    ws_app_t* _app = __create();
    _app->engine = cls_engine_ctor();
    cls_graphics_t* _gra =
        (cls_graphics_t*)cls_modules_create_module(CLS_GRAPHICS);
    cls_graphics_add_module(_gra, CLS_GRAPHICS_UI);
    _app->graphics = _gra;
    // cls_engine_add_module(_app->engine, CLS_GRAPHICS_UI);
    //  int r = cls_engine_remove_module(_app->engine, CLS_GRAPHICS);
    const char* str = cls_engine_serialize(_app->engine);
    cls_print("ENGINE: %s\n", str);
    return _app;
}

int ws_app_dtor(ws_app_t* _app) {
    cls_graphics_dtor(_app->graphics);
    cls_engine_dtor(_app->engine);
    cls_free(_app);
    __do_static_term();
    return 0;
}

void ws_app_run(ws_app_t* _app) { cls_engine_run(_app->engine); }