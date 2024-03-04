/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_engine_main.h
 */

#ifndef __CLS_ENGINE_MAIN_H
#define __CLS_ENGINE_MAIN_H

#include "cls_defines.h"
#include "cls_types.h"
#include "cls_vector.h"

#define CLS_ENGINE_DEFAULT_MODULE_COUNT 8

typedef struct cls_engine_t {
    // Has to be the first property
    cls_obj_static_t* base;
    cls_vector_t submodules;
} cls_engine_t;

extern cls_obj_static_t* cls_engine_static_init();

extern int cls_engine_static_term();

extern void cls_engine_static_register_module_type(cls_obj_static_t* tHandler);

extern cls_engine_t* cls_engine_ctor();

extern int cls_engine_dtor(cls_engine_t* eng);

extern int cls_engine_add_module(cls_engine_t* eng, cls_module_type_t type);

extern int cls_engine_remove_module(cls_engine_t* eng, cls_module_type_t type);

extern cls_obj_static_t* cls_engine_get_module(cls_engine_t* eng,
                                               cls_module_type_t type);

extern int cls_parse_args(cls_engine_t* eng, int argc, char** argv);

extern int cls_engine_run(cls_engine_t* eng);

extern const char* cls_engine_serialize(cls_engine_t* eng);

extern int cls_engine_deserialize(cls_engine_t* eng, const char* json);

#endif    // __CLS_ENGINE_MAIN_H