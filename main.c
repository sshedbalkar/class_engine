/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <argp.h>
#include <SDL2/SDL.h>
#include "mrc_console.h"
#include "mrc_version.h"

void init_argp() {
    argp_program_version = APP_VERSION;
    argp_program_bug_address = PROGRAM_BUG_EMAIL_CONTACT;
}

int main(int argc, char* argv[]) {
    mrc_print("Hello CMake3: " APP_VERSION "\n");
    SDL_Init(SDL_INIT_VIDEO);
    return 0;
}
