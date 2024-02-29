/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <stdlib.h>
#include <string.h>
#include "cls_memory.h"
// #include "cls_console.h"

void* cls_alloc(size_t size) { return malloc(size); }
void* cls_alloc_c(size_t _size, void* _context) {
    (void)_context;
    // cls_print("cls_alloc_c: %d", _size);
    return malloc(_size);
}

void cls_free(void* ptr) { free(ptr); }
void cls_free_c(void* _ptr, void* _context) {
    (void)_context;
    free(_ptr);
}

void* cls_realloc(void* ptr, size_t new_size) { return realloc(ptr, new_size); }

void* cls_memset(void* dest, int ch, size_t count) {
    return memset(dest, ch, count);
}