/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#include <SDL2/SDL.h>
#include "mrc_memory.h"
#include "mrc_console.h"
#include "mrc_graphics.h"

static mrc_obj_static_t __base = {MRC_GRAPHICS,
                                  (mrc_fn_vp_v_t)&mrc_graphics_ctor,
                                  (mrc_fn_i_vp_t)&mrc_graphics_dtor};

void mrc_graphics_init(mrc_graphics_t* obj) { SDL_Init(SDL_INIT_VIDEO); }
void mrc_graphics_test1(mrc_graphics_t* obj) {
    mrc_print("mrc_graphics_test1");
}

mrc_obj_static_t* mrc_graphics_static_init() { return &__base; }

static mrc_graphics_t* __create() {
    return (mrc_graphics_t*)mrc_alloc(sizeof(mrc_graphics_t));
}

mrc_graphics_t* mrc_graphics_ctor() {
    mrc_graphics_t* obj = __create();
    obj->base = &__base;
    return obj;
}

int mrc_graphics_dtor(mrc_graphics_t* obj) {
    mrc_free(obj);
    return 0;
}