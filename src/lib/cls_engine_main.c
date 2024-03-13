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
#include "cJSON.h"
#include "cls_utils.h"
#include "cls_modules.h"

static cls_obj_static_t __base = {CLS_ENGINE, (cls_fn_vp_v_t)&cls_engine_ctor,
                                  (cls_fn_i_vp_t)&cls_engine_dtor,
                                  (cls_fn_vp_vp_t)&cls_engine_serialize,
                                  (cls_fn_i_vp_vp_t)&cls_engine_deserialize};

static void __add_default_modules(cls_engine_t* eng) {
    cls_console_t* console = cls_console_ctor();
    cls_vector_add(&eng->submodules, console);
}

static void __on_event_quit() { cls_timer_stop(); }

cls_obj_static_t* cls_engine_static_init() {
    cls_util_static_init();
    cls_memory_static_init();
    //
    cls_vector_set_mem_allocators(cls_alloc_new, cls_free_new, cls_realloc_new);
    //
    cJSON_Hooks _hooks;
    _hooks.malloc_fn = cls_alloc_new;
    _hooks.free_fn = cls_free_new;
    cJSON_InitHooks(&_hooks);
    //
    cls_modules_static_init();
    cls_modules_static_register_module_type(&__base);
    cls_data_container_static_init();
    cls_timer_static_init();
    // CLS_GLUE,
    cls_events_static_init();
    // CLS_CORE,
    // CLS_CONSOLE,
    cls_modules_static_register_module_type(cls_console_static_init());
    // CLS_GRAPHICS,
    cls_modules_static_register_module_type(cls_graphics_static_init());
    // CLS_GRAPHICS_UI
    cls_modules_static_register_module_type(cls_ui_static_init());
    cls_events_reg_callback(CLS_EVT_QUIT, &__on_event_quit);
    //
    cls_print("Serializing1\n");
    char* _memJson = cls_memory_serialize();
    cls_print("Mem1: %s\n", _memJson);
    cls_free_new(_memJson);
    void *_ptr1, *_ptr2, *_ptr3, *_ptr4;
    _ptr1 = cls_alloc_new(1);
    _ptr2 = cls_alloc_new(40);
    _ptr3 = cls_alloc_new(35);
    _ptr4 = cls_alloc_new(50);
    cls_free_new(_ptr1);
    cls_free_new(_ptr4);
    cls_free_new(_ptr2);
    cls_print("Serializing2\n");
    _memJson = cls_memory_serialize();
    cls_print("\nMem2: %s\n", _memJson);
    cls_free_new(_memJson);
    cls_free_new(_ptr3);
    return &__base;
}

int cls_engine_static_term() {
    cls_ui_static_term();
    cls_graphics_static_term();
    cls_console_static_term();
    cls_events_static_term();
    cls_timer_static_term();
    cls_data_container_static_term();
    cls_modules_static_term();
    cls_util_static_term();
    cls_print("Serializing3\n");
    char* _memJson = cls_memory_serialize();
    cls_print("\nMem Report: %s\n", _memJson);
    cls_print("memJson: %p\n", _memJson);
    cls_free_new(_memJson);
    //
    cls_memory_static_term();
    return 0;
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
    cls_modules_remove_all_modules(&eng->submodules);
    cls_vector_free(&eng->submodules);
    cls_free(eng);
    return 0;
}

cls_obj_static_t* cls_engine_add_module(cls_engine_t* eng,
                                        cls_module_type_t type) {
    // cls_vector_add(&eng->submodules, cls_engine_create_module(type));
    cls_obj_static_t* _mod = cls_modules_add_module(&eng->submodules, type);
    return _mod;
}

int cls_engine_remove_module(cls_engine_t* eng, cls_module_type_t type) {
    return cls_modules_remove_module(&eng->submodules, type);
}

cls_obj_static_t* cls_engine_get_module(cls_engine_t* eng,
                                        cls_module_type_t type) {
    return cls_modules_get_module(&eng->submodules, type);
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
char _buff2[1024];
const char* cls_engine_serialize(cls_engine_t* _eng) {
    cJSON* _root = cJSON_CreateObject();
    // const char* _name = cls_module_type_to_string(_eng->base->type);
    // cls_print("Engine: %s\n", _name);
    cJSON_AddStringToObject(_root, "base",
                            cls_module_type_to_string(_eng->base->type));
    cJSON_AddItemToObject(_root, "submodules",
                          cls_modules_serialize(&_eng->submodules));
    // char* _buff = cls_util_get_str_buff();
    if (cJSON_PrintPreallocated(_root, _buff2, CLS_DEFAULT_STR_BUFF_SIZE, 0) ==
        1) {
        cJSON_Delete(_root);
        return _buff2;
    }
    cJSON_Delete(_root);
    return NULL_STR;
}

int cls_engine_deserialize(cls_engine_t* _eng, const char* _json) {
    (void)_eng;
    (void)_json;
    return 0;
}