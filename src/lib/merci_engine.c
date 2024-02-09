/*
Copyright (c) Santosh Shedbalkar
Year: 2024 - 2024
All rights reserved

File: merci_engine.c
*/
#include "merci_engine.h"

mrc_engine_t* mrc_engine_create() {
    return (mrc_engine_t*)mrc_alloc(sizeof(mrc_engine_t));
}

int mrc_engine_init(mrc_engine_t* eng) { return 0; }

int mrc_engine_add_module(mrc_engine_t* eng, unsigned int flags) { return 0; }

int mrc_parse_args(mrc_engine_t* eng, int argc, char** argv) { return 0; }