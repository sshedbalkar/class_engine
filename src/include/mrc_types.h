/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __MRC_TYPES_H
#define __MRC_TYPES_H

typedef enum { FALSE = 0, TRUE = 1 } bool_t;

typedef enum {
    // MRC_ENGINE should be 0 and other entries should have incremental values
    MRC_ENGINE = 0,
    MRC_GLUE,
    MRC_CORE,
    MRC_CONSOLE,
    MRC_GRAPHICS,
    MRC_GRAPHICS_UI,
    //
    MRC_MODULES_COUNT
} mrc_module_type_t;

extern const char* mrc_module_type_t_to_string(mrc_module_type_t);

typedef void (*mrc_fn_v_v_t)();
typedef void (*mrc_fn_v_vp_t)(void*);
typedef int (*mrc_fn_i_vp_t)(void*);
typedef void* (*mrc_fn_vp_v_t)();
typedef const char* (*mrc_fn_ccp_vp_i_t)(void*, int);

typedef struct {
    mrc_module_type_t type;
    mrc_fn_vp_v_t ctor;
    mrc_fn_i_vp_t dtor;
} mrc_obj_static_t;

#endif    // __MRC_TYPES_H