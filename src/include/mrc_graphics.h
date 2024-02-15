/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __MRC_GRAPHICS_H
#define __MRC_GRAPHICS_H

#include "mrc_types.h"

typedef struct {
    // Has to be the first property
    mrc_obj_static_t* base;
} mrc_graphics_t;

extern void mrc_graphics_test1(mrc_graphics_t* obj);

extern mrc_obj_static_t* mrc_graphics_static_init();

extern mrc_graphics_t* mrc_graphics_ctor();

extern int mrc_graphics_dtor(mrc_graphics_t* obj);

#endif    // __MRC_GRAPHICS_H