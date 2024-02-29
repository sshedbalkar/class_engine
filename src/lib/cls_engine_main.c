/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_engine_main.c
 */

#include "cls_engine_main.h"
#include "cls_memory.h"
#include "cls_console.h"
#include "cls_data_container.h"
#include "cls_events.h"
#include "cls_list_core_events.h"
#include "cls_graphics.h"
#include "cls_ui.h"
#include "cls_timer.h"

static cls_obj_static_t __base = {CLS_ENGINE, (cls_fn_vp_v_t)&cls_engine_ctor,
                                  (cls_fn_i_vp_t)&cls_engine_dtor};

static cls_vector_t __modules_map;

static void __add_default_modules(cls_engine_t* eng) {
    cls_console_t* console = cls_console_ctor();
    cls_vector_add(&eng->submodules, console);
}

static void __remove_all_modules(cls_engine_t* eng) {
    int i, t = cls_vector_total(&eng->submodules);
    cls_obj_static_t** pmodule;
    for (i = 0; i < t; ++i) {
        pmodule = (cls_obj_static_t**)cls_vector_get(&eng->submodules, i);
        if (*pmodule != NULL) (*pmodule)->dtor(pmodule);
    }
}

static void __on_event_quit() { cls_timer_stop(); }

cls_obj_static_t* cls_engine_static_init() {
    cls_vector_init_capacity(&__modules_map, CLS_ENGINE_DEFAULT_MODULE_COUNT);
    cls_vector_set(&__modules_map, CLS_ENGINE, &__base);
    cls_data_container_static_init();
    cls_timer_static_init();
    // CLS_GLUE,
    cls_events_static_init();
    // CLS_CORE,
    // CLS_CONSOLE,
    cls_vector_set(&__modules_map, CLS_CONSOLE, cls_console_static_init());
    // CLS_GRAPHICS,
    cls_vector_set(&__modules_map, CLS_GRAPHICS, cls_graphics_static_init());
    // CLS_GRAPHICS_UI
    cls_vector_set(&__modules_map, CLS_GRAPHICS_UI, cls_ui_static_init());
    cls_events_reg_callback(CLS_EVT_QUIT, &__on_event_quit);
    return &__base;
}

int cls_engine_static_term() {
    cls_ui_static_term();
    cls_graphics_static_term();
    cls_console_static_term();
    cls_events_static_term();
    cls_timer_static_term();
    cls_data_container_static_term();
    cls_vector_free(&__modules_map);
    return 0;
}
void cls_engine_static_register_module_type(cls_obj_static_t* tHandler) {
    cls_vector_set(&__modules_map, tHandler->type, tHandler);
}

static cls_engine_t* __create() {
    cls_engine_t* eng = (cls_engine_t*)cls_alloc(sizeof(cls_engine_t));
    return eng;
}

cls_engine_t* cls_engine_ctor() {
    cls_engine_t* eng = __create();
    eng->base = &__base;
    cls_vector_init_capacity(&eng->submodules, CLS_ENGINE_DEFAULT_MODULE_COUNT);
    __add_default_modules(eng);
    return eng;
}

int cls_engine_dtor(cls_engine_t* eng) {
    __remove_all_modules(eng);
    cls_vector_free(&eng->submodules);
    cls_free(eng);
    return 0;
}

int cls_engine_add_module(cls_engine_t* eng, cls_module_type_t type) {
    cls_obj_static_t* mod =
        ((cls_obj_static_t*)cls_vector_get(&__modules_map, type))->ctor();
    cls_vector_add(&eng->submodules, mod);
    return 0;
}

int cls_engine_remove_module(cls_engine_t* eng, cls_module_type_t type) {
    int i, t, count = 0, found = 0;
    cls_obj_static_t** pmod;
    do {
        found = 0;
        t = cls_vector_total(&eng->submodules);
        for (i = 0; i < t; ++i) {
            pmod = cls_vector_get(&eng->submodules, i);
            if ((*pmod)->type == type) {
                found = 1;
                (*pmod)->dtor(pmod);
                cls_vector_delete(&eng->submodules, i);
                i = t;
                ++count;
            }
        }
    } while (found > 0);
    return count;
}

cls_obj_static_t* cls_engine_get_module(cls_engine_t* eng,
                                        cls_module_type_t type) {
    int i, t = cls_vector_total(&eng->submodules);
    cls_obj_static_t** pmodule;
    for (i = 0; i < t; ++i) {
        pmodule = (cls_obj_static_t**)cls_vector_get(&eng->submodules, i);
        if ((*pmodule)->type == type) return *pmodule;
    }
    return NULL;
}

int cls_parse_args(cls_engine_t* eng, int argc, char** argv) {
    (void)eng;
    (void)argc;
    (void)argv;
    return 0;
}

int cls_engine_run(cls_engine_t* eng) {
    (void)eng;
    cls_timer_run();
    return 0;
}