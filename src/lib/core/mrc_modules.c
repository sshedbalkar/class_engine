/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: mrc_modules.c
*/

#include "mrc_types.h"

typedef enum {
    MRC_ENGINE,
    MRC_GLUE,
    MRC_CORE,
    MRC_CONSOLE,
    MRC_GRAPHICS,
    MRC_GRAPHICS_UI
} mrc_module_type_t;

typedef struct {
    mrc_module_type_t type;
} mrc_module_t;