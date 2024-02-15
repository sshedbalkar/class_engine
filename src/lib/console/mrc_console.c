/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <stdio.h>
#include <stdarg.h>
#include "mrc_types.h"
#include "mrc_console.h"
#include "mrc_memory.h"

static mrc_obj_static_t __base = {MRC_CONSOLE, (mrc_fn_vp_v_t)&mrc_console_ctor,
                                  (mrc_fn_i_vp_t)&mrc_console_dtor};

int mrc_print(const char* format, ...) {
    int result;
    va_list args;
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);
    return result;
}

mrc_obj_static_t* mrc_console_static_init() { return &__base; }

int mrc_console_static_term() { return 0; }

static mrc_console_t* __create() {
    return (mrc_console_t*)mrc_alloc(sizeof(mrc_console_t));
}

mrc_console_t* mrc_console_ctor() {
    mrc_console_t* obj = __create();
    obj->base = &__base;
    return obj;
}

int mrc_console_dtor(mrc_console_t* obj) {
    mrc_free(obj);
    return 0;
}