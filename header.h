#include <SDL2/SDL.h>
#include "mrc_console.h"

#define MERCI_VERSION "@MERCI_VERSION@"

int main(int argc, char* argv[]) {
    mrc_print("Hello CMake3: " MERCI_VERSION "\n")
    SDL_Init(SDL_INIT_VIDEO)
    return 0
}
