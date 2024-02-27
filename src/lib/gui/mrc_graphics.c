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
#include "mrc_data_container.h"

static mrc_obj_static_t __base = {MRC_GRAPHICS,
                                  (mrc_fn_vp_v_t)&mrc_graphics_ctor,
                                  (mrc_fn_i_vp_t)&mrc_graphics_dtor};

unsigned int MRC_H_SDL_EVT_OBJ;
unsigned int MRC_H_GRAPHICS_OBJ;
static SDL_Event __sdl_evt;

static mrc_graphics_t* __create() {
    mrc_graphics_t* app = (mrc_graphics_t*)mrc_alloc(sizeof(mrc_graphics_t));
    return app;
}

static void __on_enter_frame() {
    // mrc_print("GR Enter frame\n");
    while (SDL_PollEvent(&__sdl_evt)) {
        mrc_events_trigger_event(MRC_EVT_SDL_EVENT);
        if (__sdl_evt.type == SDL_QUIT) {
            mrc_events_trigger_event(MRC_EVT_QUIT);
        }
    }
}

void mrc_graphics_test1(mrc_graphics_t* obj) {
    (void)obj;
    mrc_print("mrc_graphics_test1");
}

mrc_obj_static_t* mrc_graphics_static_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        mrc_print("SDL init error: %s\n", SDL_GetError());
    }
    MRC_H_SDL_EVT_OBJ = mrc_data_container_add(&__sdl_evt);
    mrc_events_reg_callback(MRC_EVT_FRAME_ENTER, &__on_enter_frame);
    return &__base;
}

int mrc_graphics_static_term() {
    mrc_data_container_remove(MRC_H_SDL_EVT_OBJ);
    MRC_H_SDL_EVT_OBJ = 0;
    SDL_Quit();
    return 0;
}

mrc_graphics_t* mrc_graphics_ctor() {
    mrc_graphics_t* _obj = __create();
    _obj->base = &__base;
// SDL Init
// From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    SDL_WindowFlags _window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* _window =
        SDL_CreateWindow("Word Scape", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 1280, 720, _window_flags);
    if (_window == NULL) {
        mrc_print("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return NULL;
    }
    _obj->window = _window;
    _obj->renderer = SDL_CreateRenderer(
        _window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (_obj->renderer == NULL) {
        SDL_Log("Error creating SDL_Renderer!");
        return NULL;
    }
    SDL_RendererInfo info;
    SDL_GetRendererInfo(_obj->renderer, &info);
    SDL_Log("Current SDL_Renderer: %s", info.name);
    // SDL_Delay(5000);
    //
    MRC_H_GRAPHICS_OBJ = mrc_data_container_add(_obj);
    return _obj;
}

int mrc_graphics_dtor(mrc_graphics_t* obj) {
    mrc_data_container_remove(MRC_H_GRAPHICS_OBJ);
    MRC_H_GRAPHICS_OBJ = 0;
    SDL_DestroyRenderer(obj->renderer);
    SDL_DestroyWindow(obj->window);
    mrc_free(obj);
    return 0;
}