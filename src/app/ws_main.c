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

ws_app_t* ws_app_ctor() {
    ws_app_t* app = __create();
    app->engine = mrc_engine_ctor();
    mrc_print("App created\n");
    return app;
}

int ws_app_dtor(ws_app_t* app) {
    mrc_engine_dtor(app->engine);
    mrc_free(app);
    return 0;
}
