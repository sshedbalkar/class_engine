/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __MRC_MEMORY_H
#define __MRC_MEMORY_H

#include <stddef.h>

void* mrc_alloc(size_t size);
void mrc_free(void* ptr);
void* mrc_realloc(void* ptr, size_t new_size);

#endif    // __MRC_MEMORY_H