/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __MRC_UI_H
#define __MRC_UI_H

#include <stdbool.h>
#include "mrc_types.h"
#include "mrc_defines.h"

typedef struct {
    // Has to be the first property
    mrc_obj_static_t* base;
    bool show_win_main;
    bool show_menu_main;
    bool show_demo_window;
    bool show_another_window;
} mrc_ui_t;

EXTERNC void mrc_ui_init(mrc_ui_t* obj);
EXTERNC void mrc_ui_test1(mrc_ui_t* obj);

EXTERNC mrc_obj_static_t* mrc_ui_static_init();

EXTERNC int mrc_ui_static_term();

EXTERNC mrc_ui_t* mrc_ui_ctor();

EXTERNC int mrc_ui_dtor(mrc_ui_t* obj);

#endif    // __MRC_UI_H