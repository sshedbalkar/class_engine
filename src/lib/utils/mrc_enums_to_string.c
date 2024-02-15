/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_enums_to_string.c
 */

#include "mrc_defines.h"
#include "mrc_types.h"

static const char* __mrc_module_type_t_strings[] = {
    "\"MRC_ENGINE\"",  "\"MRC_GLUE\"",     "\"MRC_CORE\"",
    "\"MRC_CONSOLE\"", "\"MRC_GRAPHICS\"", "\"MRC_GRAPHICS_UI\""};

const char* mrc_module_type_t_to_string(mrc_module_type_t val) {
    if (val < MRC_MODULES_COUNT) return __mrc_module_type_t_strings[val];
    return NULL_STR;
}