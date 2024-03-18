/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __CLS_GRAPHICS_H
#define __CLS_GRAPHICS_H

#include "cls_types.h"
#include "cls_vector.h"

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct cJSON cJSON;

typedef struct {
    // Has to be the first property
    cls_obj_static_t* base;
    SDL_Window* window;
    SDL_Renderer* renderer;
    cls_vector_t submodules;
    bool_t app_run;
} cls_graphics_t;

extern void cls_graphics_test1(cls_graphics_t* obj);

extern cls_obj_static_t* cls_graphics_static_init();

extern int cls_graphics_static_term();

extern cls_graphics_t* cls_graphics_ctor();

extern int cls_graphics_dtor(cls_graphics_t* obj);

cJSON* cls_graphics_serz(cls_graphics_t* _obj);
int cls_graphics_dsrz(cls_graphics_t* _obj, cJSON* _json);

extern cls_obj_static_t* cls_graphics_add_module(cls_graphics_t* _gra,
                                                 cls_module_type_t type);

extern int cls_graphics_remove_module(cls_graphics_t* _gra,
                                      cls_module_type_t type);

extern cls_obj_static_t* cls_graphics_get_module(cls_graphics_t* _gra,
                                                 cls_module_type_t type);

extern unsigned int CLS_H_SDL_EVT_OBJ;
extern unsigned int CLS_H_GRAPHICS_OBJ;

#endif    // __CLS_GRAPHICS_H