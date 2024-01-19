#include <SDL2/SDL.h>
#include "console.h"

int main() {
    print("Hello CMake3\n");
    SDL_Init(SDL_INIT_VIDEO);
    return 0;
}
