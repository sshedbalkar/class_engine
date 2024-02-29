/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_graphics.c
 */

#include <SDL2/SDL.h>
#include "cls_memory.h"
#include "cls_console.h"
#include "cls_graphics.h"
#include "cls_events.h"
#include "cls_list_core_events.h"
#include "cls_data_container.h"

static cls_obj_static_t __base = {CLS_GRAPHICS,
                                  (cls_fn_vp_v_t)&cls_graphics_ctor,
                                  (cls_fn_i_vp_t)&cls_graphics_dtor};

unsigned int CLS_H_SDL_EVT_OBJ;
unsigned int CLS_H_GRAPHICS_OBJ;
static SDL_Event __sdl_evt;

static cls_graphics_t* __create() {
    cls_graphics_t* app = (cls_graphics_t*)cls_alloc(sizeof(cls_graphics_t));
    return app;
}

static void __on_enter_frame() {
    // cls_print("GR Enter frame\n");
    while (SDL_PollEvent(&__sdl_evt)) {
        cls_events_trigger_event(CLS_EVT_SDL_EVENT);
        if (__sdl_evt.type == SDL_QUIT) {
            cls_events_trigger_event(CLS_EVT_QUIT);
        }
    }
}

void cls_graphics_test1(cls_graphics_t* obj) {
    (void)obj;
    cls_print("cls_graphics_test1");
}

cls_obj_static_t* cls_graphics_static_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cls_print("SDL init error: %s\n", SDL_GetError());
    }
    CLS_H_SDL_EVT_OBJ = cls_data_container_add(&__sdl_evt);
    cls_events_reg_callback(CLS_EVT_FRAME_ENTER, &__on_enter_frame);
    return &__base;
}

int cls_graphics_static_term() {
    cls_data_container_remove(CLS_H_SDL_EVT_OBJ);
    CLS_H_SDL_EVT_OBJ = 0;
    SDL_Quit();
    return 0;
}

cls_graphics_t* cls_graphics_ctor() {
    cls_graphics_t* _obj = __create();
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
        cls_print("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
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
    CLS_H_GRAPHICS_OBJ = cls_data_container_add(_obj);
    return _obj;
}

int cls_graphics_dtor(cls_graphics_t* obj) {
    cls_data_container_remove(CLS_H_GRAPHICS_OBJ);
    CLS_H_GRAPHICS_OBJ = 0;
    SDL_DestroyRenderer(obj->renderer);
    SDL_DestroyWindow(obj->window);
    cls_free(obj);
    return 0;
}