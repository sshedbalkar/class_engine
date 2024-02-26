/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __MRC_MEMORY_H
#define __MRC_MEMORY_H

#include <stddef.h>

extern void* mrc_alloc(size_t size);
extern void mrc_free(void* ptr);
extern void* mrc_alloc_c(size_t _size, void* _context);
extern void mrc_free_c(void* _ptr, void* _context);
extern void* mrc_realloc(void* ptr, size_t new_size);
extern void* mrc_memset(void* dest, int ch, size_t count);

#endif    // __MRC_MEMORY_H