/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_graphics.c
 */

#include <SDL2/SDL.h>
#include "mrc_memory.h"
#include "mrc_console.h"
#include "mrc_graphics.h"
#include "mrc_events.h"
#include "mrc_list_core_events.h"

static mrc_obj_static_t __base = {MRC_GRAPHICS,
                                  (mrc_fn_vp_v_t)&mrc_graphics_ctor,
                                  (mrc_fn_i_vp_t)&mrc_graphics_dtor};

static mrc_graphics_t* __create() {
    mrc_graphics_t* app = (mrc_graphics_t*)mrc_alloc(sizeof(mrc_graphics_t));
    return app;
}

static void __on_enter_frame() {
    // mrc_print("GR Enter frame\n");
    /*    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            mrc_events_trigger_event(MRC_EVT_QUIT);
        }
    }
    */
    /*
       if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(__window))
                mrc_events_trigger_event(MRC_EVT_QUIT);
                */
}

void mrc_graphics_test1(mrc_graphics_t* obj) {
    (void)obj;
    mrc_print("mrc_graphics_test1");
}

mrc_obj_static_t* mrc_graphics_static_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        mrc_print("SDL init error: %s\n", SDL_GetError());
    }
    mrc_events_reg_callback(MRC_EVT_FRAME_ENTER, &__on_enter_frame);
    return &__base;
}

int mrc_graphics_static_term() {
    SDL_Quit();
    return 0;
}

mrc_graphics_t* mrc_graphics_ctor() {
    mrc_graphics_t* obj = __create();
    obj->base = &__base;
    SDL_Window* window =
        SDL_CreateWindow("Window 1", 0, 0, 600, 480, SDL_WINDOW_SHOWN);
    obj->window = window;
    // SDL_Delay(5000);
    return obj;
}

int mrc_graphics_dtor(mrc_graphics_t* obj) {
    SDL_DestroyWindow(obj->window);
    mrc_free(obj);
    return 0;
}