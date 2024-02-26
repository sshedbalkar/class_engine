/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <stdlib.h>
#include <string.h>
#include "mrc_memory.h"
// #include "mrc_console.h"

void* mrc_alloc(size_t size) { return malloc(size); }
void* mrc_alloc_c(size_t _size, void* _context) {
    (void)_context;
    // mrc_print("mrc_alloc_c: %d", _size);
    return malloc(_size);
}

void mrc_free(void* ptr) { free(ptr); }
void mrc_free_c(void* _ptr, void* _context) {
    (void)_context;
    free(_ptr);
}

void* mrc_realloc(void* ptr, size_t new_size) { return realloc(ptr, new_size); }

void* mrc_memset(void* dest, int ch, size_t count) {
    return memset(dest, ch, count);
}