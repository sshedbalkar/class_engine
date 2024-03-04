/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __CLS_TYPES_H
#define __CLS_TYPES_H

typedef enum { CLS_FALSE = 0, CLS_TRUE = 1 } bool_t;

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

typedef struct cJSON cJSON;

extern const char* cls_module_type_to_string(cls_module_type_t);

typedef void (*cls_fn_v_v_t)();
typedef void (*cls_fn_v_vp_t)(void*);
typedef void (*cls_fn_v_vp_ui_vp_t)(void*, unsigned int, void*);
typedef int (*cls_fn_i_vp_t)(void*);
typedef void* (*cls_fn_vp_v_t)();
typedef const char* (*cls_fn_ccp_vp_i_t)(void*, int);
typedef void* (*cls_fn_vp_vp_t)(void*);
typedef int (*cls_fn_i_vp_vp_t)(void*, void*);

typedef struct {
    cls_module_type_t type;
    cls_fn_vp_v_t ctor;
    cls_fn_i_vp_t dtor;
    cls_fn_vp_vp_t serialize;
    cls_fn_i_vp_vp_t dserialize;
} cls_obj_static_t;

extern cJSON* cls_static_module_serialize(cls_obj_static_t* _obj);
extern bool_t cls_static_module_deserialize(cls_obj_static_t* _obj,
                                            cJSON* _json);
extern const char* cls_bool_type_to_string(bool_t _val);
#endif    // __CLS_TYPES_H