/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <SDL2/SDL.h>
#include "mrc_console.h"
#include "mrc_version.h"
#include "mrc_vector.h"

void printi(void* v) {
    char* i = (char*)v;
    mrc_print("%s, ", i);
}

void printv(mrc_vector_t* v) {
    mrc_print("Curr vector: ");
    mrc_vector_foreach(v, &printi);
    mrc_print("\n");
}
int main(int argc, char* argv[]) {
    mrc_print("Hello CMake3: " APP_VERSION "\n");
    SDL_Init(SDL_INIT_VIDEO);
    //
    mrc_vector_t vec;
    mrc_vector_init(&vec);
    mrc_vector_add(&vec, "Enter");
    mrc_vector_add(&vec, "node");
    mrc_vector_add(&vec, "position");
    mrc_vector_add(&vec, "to");
    mrc_vector_add(&vec, "delete");
    mrc_vector_add(&vec, "hiya");
    printv(&vec);

    mrc_vector_delete(&vec, 4);
    printv(&vec);

    mrc_vector_set(&vec, 4, "hurrah");
    mrc_vector_add(&vec, "Linked");
    mrc_vector_add(&vec, "list");
    printv(&vec);

    mrc_print("Size: %d\n", mrc_vector_total(&vec));
    mrc_print("Item at 6: %s\n", (char*)mrc_vector_get(&vec, 6));

    mrc_vector_free(&vec);
    //
    return 0;
}
