/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_modules.h
 */
#ifndef __CLS_MODULES_H
#define __CLS_MODULES_H

#define CLS_MODULES_DEFAULT_MODULE_COUNT 8

#include "cls_types.h"

struct cls_vector_t;
typedef struct cls_vector_t cls_vector_t;

extern cls_obj_static_t* cls_modules_static_init();

extern int cls_modules_static_term();

extern void cls_modules_static_register_module_type(cls_obj_static_t* tHandler);

extern cls_obj_static_t* cls_modules_create_module(cls_module_type_t _type);

extern cls_obj_static_t* cls_modules_add_module(cls_vector_t* eng,
                                                cls_module_type_t type);

extern int cls_modules_remove_module(cls_vector_t* eng, cls_module_type_t type);

extern cls_obj_static_t* cls_modules_get_module(cls_vector_t* eng,
                                                cls_module_type_t type);
extern cJSON* cls_modules_serialize(cls_vector_t* _vec);

extern int cls_modules_deserialize(cls_vector_t* _vec, cJSON* _arr);

extern void cls_modules_remove_all_modules(cls_vector_t* eng);
#endif    // __CLS_MODULES_H