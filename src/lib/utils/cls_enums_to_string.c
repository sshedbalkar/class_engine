/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_enums_to_string.c
 */

#include "cls_defines.h"
#include "cls_types.h"
#include "cls_error.h"

static const char* __cls_module_type_t_strings[] = {
    "CLS_ENGINE",  "CLS_GLUE",     "CLS_CORE",
    "CLS_CONSOLE", "CLS_GRAPHICS", "CLS_GRAPHICS_UI"};

static const char* __cls_error_type_strings[] = {
    "CLS_ERROR_RECOVERABLE", "CLS_ERROR_FATAL", "CLS_ERROR_COUNT"};

static const char* __cls_bool_strings[] = {"CLS_FALSE", "CLS_TRUE"};

const char* cls_module_type_to_string(cls_module_type_t val) {
    if (val < CLS_MODULES_COUNT) return __cls_module_type_t_strings[val];
    return NULL_STR;
}

const char* cls_error_type_to_string(cls_error_type_t _type) {
    if (_type < CLS_ERROR_COUNT) return __cls_error_type_strings[_type];
    return NULL_STR;
}

const char* cls_bool_type_to_string(bool_t _val) {
    if (_val < 2) return __cls_bool_strings[_val];
    return NULL_STR;
}