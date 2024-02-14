/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __MRC_UI_H
#define __MRC_UI_H

#include "mrc_types.h"

typedef struct {
    // Has to be the first property
    mrc_obj_static_t* base;
} mrc_ui_t;

extern void mrc_ui_init(mrc_ui_t* obj);
extern void mrc_ui_test1(mrc_ui_t* obj);

extern mrc_obj_static_t* mrc_ui_static_init();

extern mrc_ui_t* mrc_ui_ctor();

extern int mrc_ui_dtor(mrc_ui_t* obj);

#endif    // __MRC_UI_H