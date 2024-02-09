/*
Copyright (c) Santosh Shedbalkar
Year: 2024 - 2024
All rights reserved

File: merci_engine.h
*/

#ifndef __MERCI_ENGINE_H
#define __MERCI_ENGINE_H

#include "mrc_engine_main_p.h"

typedef enum {
    MRC_ENGINE,
    MRC_GLUE,
    MRC_CORE,
    MRC_CONSOLE,
    MRC_GRAPHICS,
    MRC_GRAPHICS_UI
} mrc_module_type_t;

typedef struct {
    mrc_vector_t modules;
} mrc_engine_t;

extern mrc_engine_t* mrc_engine_create();

extern int mrc_engine_init(mrc_engine_t* eng);

extern int mrc_engine_add_module(mrc_engine_t* eng, unsigned int flags);

extern int mrc_parse_args(mrc_engine_t* eng, int argc, char** argv);

#endif    // __MERCI_ENGINE_H