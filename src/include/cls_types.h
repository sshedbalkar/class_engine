/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __CLS_TYPES_H
#define __CLS_TYPES_H

typedef enum { FALSE = 0, TRUE = 1 } bool_t;

typedef enum {
    // CLS_ENGINE should be 0 and other entries should have incremental values
    CLS_ENGINE = 0,
    CLS_GLUE,
    CLS_CORE,
    CLS_CONSOLE,
    CLS_GRAPHICS,
    CLS_GRAPHICS_UI,
    //
    CLS_MODULES_COUNT
} cls_module_type_t;

extern const char* cls_module_type_t_to_string(cls_module_type_t);

typedef void (*cls_fn_v_v_t)();
typedef void (*cls_fn_v_vp_t)(void*);
typedef void (*cls_fn_v_vp_ui_vp_t)(void*, unsigned int, void*);
typedef int (*cls_fn_i_vp_t)(void*);
typedef void* (*cls_fn_vp_v_t)();
typedef const char* (*cls_fn_ccp_vp_i_t)(void*, int);
typedef void* (*cls_fn_vp_vp_t)(void*);
typedef void (*cls_fn_v_vp_vp_t)(void*, void*);

typedef struct {
    cls_module_type_t type;
    cls_fn_vp_v_t ctor;
    cls_fn_i_vp_t dtor;
    cls_fn_vp_vp_t serialize;
    cls_fn_v_vp_vp_t dserialize;
} cls_obj_static_t;

#endif    // __CLS_TYPES_H