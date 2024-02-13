/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#include <SDL2/SDL.h>
#include "mrc_console.h"
#include "mrc_graphics.h"

void mrc_graphics_init(mrc_graphics_t* obj) { SDL_Init(SDL_INIT_VIDEO); }
void mrc_graphics_test1(mrc_graphics_t* obj) {
    mrc_print("mrc_graphics_test1");
}