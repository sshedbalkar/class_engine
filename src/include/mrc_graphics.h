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

extern void mrc_graphics_init(mrc_graphics_t* obj);
extern void mrc_graphics_test1(mrc_graphics_t* obj);

#endif    // __MRC_GRAPHICS_H