/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __MRC_GRAPHICS_H
#define __MRC_GRAPHICS_H

#include "mrc_types.h"

struct SDL_Window;
typedef struct SDL_Window SDL_Window;
struct SDL_Renderer;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct {
    // Has to be the first property
    mrc_obj_static_t* base;
    SDL_Window* window;
    SDL_Renderer* renderer;
} mrc_graphics_t;

extern void mrc_graphics_test1(mrc_graphics_t* obj);

extern mrc_obj_static_t* mrc_graphics_static_init();

extern int mrc_graphics_static_term();

extern mrc_graphics_t* mrc_graphics_ctor();

extern int mrc_graphics_dtor(mrc_graphics_t* obj);

extern unsigned int MRC_H_SDL_EVT_OBJ;
extern unsigned int MRC_H_GRAPHICS_OBJ;

#endif    // __MRC_GRAPHICS_H