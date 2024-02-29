/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_enums_to_string.c
 */

#include "cls_defines.h"
#include "cls_types.h"

static const char* __cls_module_type_t_strings[] = {
    "\"CLS_ENGINE\"",  "\"CLS_GLUE\"",     "\"CLS_CORE\"",
    "\"CLS_CONSOLE\"", "\"CLS_GRAPHICS\"", "\"CLS_GRAPHICS_UI\""};

const char* cls_module_type_t_to_string(cls_module_type_t val) {
    if (val < CLS_MODULES_COUNT) return __cls_module_type_t_strings[val];
    return NULL_STR;
}