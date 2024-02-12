/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_engine_main.c
 */

#include "mrc_engine_main.h"
#include "mrc_memory.h"
#include "mrc_console.h"

static mrc_obj_static_t __base = {MRC_ENGINE, &mrc_engine_ctor,
                                  &mrc_engine_dtor};

static mrc_vector_t __modules_map;

mrc_obj_static_t* mrc_engine_static_init() {
    mrc_vector_init_capacity(&__modules_map, MRC_ENGINE_DEFAULT_MODULE_COUNT);
    mrc_vector_set(&__modules_map, MRC_ENGINE, &__base);
    // MRC_GLUE,
    // MRC_CORE,
    // MRC_CONSOLE,
    mrc_vector_set(&__modules_map, MRC_CONSOLE, mrc_console_static_init());
    // MRC_GRAPHICS,
    // MRC_GRAPHICS_UI
    return &__base;
}

void mrc_engine_static_register_module_type(mrc_obj_static_t* tHandler) {
    mrc_vector_set(&__modules_map, tHandler->type, tHandler);
}

static mrc_engine_t* __create() {
    mrc_engine_t* eng = (mrc_engine_t*)mrc_alloc(sizeof(mrc_engine_t));
    return eng;
}

mrc_engine_t* mrc_engine_ctor() {
    mrc_engine_t* eng = __create();
    eng->base = &__base;
    mrc_vector_init_capacity(&eng->modules, MRC_ENGINE_DEFAULT_MODULE_COUNT);
    __add_default_modules(eng);
    return eng;
}

static void __add_default_modules(mrc_engine_t* eng) {
    mrc_console_t* console = mrc_console_ctor();
    mrc_vector_add(&eng->modules, console);
}

int mrc_engine_dtor(mrc_engine_t* eng) {
    __remove_all_modules(eng);
    mrc_vector_free(&eng->modules);
    mrc_free(eng);
    return 0;
}

static void __remove_all_modules(mrc_engine_t* eng) {
    int i, t = mrc_vector_total(&eng->modules);
    mrc_obj_static_t* module;
    for (i = 0; i < t; ++i) {
        module = (mrc_obj_static_t*)mrc_vector_get(&eng->modules, i);
        if (module != NULL) module->dtor(module);
    }
}
int mrc_engine_add_module(mrc_engine_t* eng, mrc_module_type_t type) {
    mrc_obj_static_t* mod =
        ((mrc_obj_static_t*)mrc_vector_get(&__modules_map, type))->ctor();
    mrc_vector_add(&eng->modules, mod);
    return 0;
}

int mrc_engine_remove_module(mrc_engine_t* eng, mrc_module_type_t type) {
    int i, t = mrc_vector_total(&eng->modules), count = 0;
    mrc_obj_static_t* mod;
    for (i = 0; i < t; ++i) {
        mod = mrc_vector_get(&eng->modules, i);
        if (mod->type == type) {
            mod->dtor(mod);
            mrc_vector_delete(&eng->modules, i);
            ++count;
        }
    }
    return count;
}

mrc_obj_static_t* mrc_engine_get_module(mrc_engine_t* eng,
                                        mrc_module_type_t type) {
    int i, t = mrc_vector_total(&eng->modules);
    mrc_obj_static_t* module;
    for (i = 0; i < t; ++i) {
        module = (mrc_obj_static_t*)mrc_vector_get(&eng->modules, i);
        if (module->type == type) return module;
    }
    return NULL;
}

int mrc_parse_args(mrc_engine_t* eng, int argc, char** argv) { return 0; }