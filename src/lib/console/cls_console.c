/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <stdio.h>
#include <stdarg.h>
#include "cls_types.h"
#include "cls_console.h"
#include "cls_memory.h"

static cls_obj_static_t __base = {CLS_CONSOLE, (cls_fn_vp_v_t)&cls_console_ctor,
                                  (cls_fn_i_vp_t)&cls_console_dtor};

DECLSPEC int MRCCALL cls_print(const char* format, ...) {
    int result;
    va_list args;
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);
    return result;
}

cls_obj_static_t* cls_console_static_init() { return &__base; }

int cls_console_static_term() { return 0; }

static cls_console_t* __create() {
    cls_console_t* app = (cls_console_t*)cls_alloc(sizeof(cls_console_t));
    return app;
}

cls_console_t* cls_console_ctor() {
    cls_console_t* obj = __create();
    obj->base = &__base;
    return obj;
}

int cls_console_dtor(cls_console_t* obj) {
    cls_free(obj);
    return 0;
}