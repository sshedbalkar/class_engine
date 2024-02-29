/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __CLS_CONSOLE_H
#define __CLS_CONSOLE_H

#include "cls_types.h"
#include "cls_defines.h"

typedef struct {
    // Has to be the first property
    cls_obj_static_t* base;
} cls_console_t;

extern DECLSPEC int MRCCALL cls_print(const char* format, ...);

extern cls_obj_static_t* cls_console_static_init();

extern int cls_console_static_term();

extern cls_console_t* cls_console_ctor();

extern int cls_console_dtor(cls_console_t* obj);

#endif    //__CLS_CONSOLE_H
