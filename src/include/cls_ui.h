/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __CLS_UI_H
#define __CLS_UI_H

#include <stdbool.h>
#include "cls_types.h"
#include "cls_defines.h"

typedef struct {
    // Has to be the first property
    cls_obj_static_t* base;
    bool show_win_main;
    bool show_menu_main;
    bool show_demo_window;
    bool show_another_window;
} cls_ui_t;

EXTERNC void cls_ui_init(cls_ui_t* obj);
EXTERNC void cls_ui_test1(cls_ui_t* obj);

EXTERNC cls_obj_static_t* cls_ui_static_init();

EXTERNC int cls_ui_static_term();

EXTERNC cls_ui_t* cls_ui_ctor();

EXTERNC int cls_ui_dtor(cls_ui_t* obj);

#endif    // __CLS_UI_H