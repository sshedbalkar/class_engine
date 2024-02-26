/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __MRC_CONSOLE_H
#define __MRC_CONSOLE_H

#include "mrc_types.h"
#include "mrc_defines.h"

typedef struct {
    // Has to be the first property
    mrc_obj_static_t* base;
} mrc_console_t;

extern DECLSPEC int MRCCALL mrc_print(const char* format, ...);

extern mrc_obj_static_t* mrc_console_static_init();

extern int mrc_console_static_term();

extern mrc_console_t* mrc_console_ctor();

extern int mrc_console_dtor(mrc_console_t* obj);

#endif    //__MRC_CONSOLE_H
