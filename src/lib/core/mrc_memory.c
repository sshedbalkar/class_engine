/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <stdlib.h>
#include <string.h>
#include "mrc_memory.h"

void* mrc_alloc(size_t size) { return malloc(size); }
void mrc_free(void* ptr) { free(ptr); }

void* mrc_realloc(void* ptr, size_t new_size) { return realloc(ptr, new_size); }

void* mrc_memcpy(void* dest, const void* src, size_t count) {
    return memcpy(dest, src, count);
}