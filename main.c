/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: main.c
 */

#include <SDL2/SDL.h>
#include "ws_main.h"
#include "ws_terminal_ui.h"
#include "mrc_console.h"

int main(int argc, char* argv[]) {
    mrc_print("Hello WordScape2\n");
    SDL_Init(SDL_INIT_VIDEO);
    //
    mrc_print("Creating WordScape2\n");
    ws_app_t* app = ws_app_ctor();
    if (ws_parse_args(argc, argv, app) == 0) {
        mrc_print("Successfully parsed\n");
    }
    //
    return 0;
}
