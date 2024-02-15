/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_engine_main.h
 */

#ifndef __MRC_ENGINE_MAIN_H
#define __MRC_ENGINE_MAIN_H

#include "mrc_defines.h"
#include "mrc_types.h"
#include "mrc_vector.h"

#define MRC_ENGINE_DEFAULT_MODULE_COUNT 8

typedef struct mrc_engine_t {
    // Has to be the first property
    mrc_obj_static_t* base;
    mrc_vector_t modules;
} mrc_engine_t;

extern mrc_obj_static_t* mrc_engine_static_init();

extern void mrc_engine_static_register_module_type(mrc_obj_static_t* tHandler);

extern mrc_engine_t* mrc_engine_ctor();

extern int mrc_engine_dtor(mrc_engine_t* eng);

extern int mrc_engine_add_module(mrc_engine_t* eng, mrc_module_type_t type);

extern int mrc_engine_remove_module(mrc_engine_t* eng, mrc_module_type_t type);

extern mrc_obj_static_t* mrc_engine_get_module(mrc_engine_t* eng,
                                               mrc_module_type_t type);

extern int mrc_parse_args(mrc_engine_t* eng, int argc, char** argv);

#endif    // __MRC_ENGINE_MAIN_H