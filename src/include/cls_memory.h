/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __CLS_MEMORY_H
#define __CLS_MEMORY_H

#include <stddef.h>

extern void* cls_alloc(size_t size);
extern void cls_free(void* ptr);
extern void* cls_alloc_c(size_t _size, void* _context);
extern void cls_free_c(void* _ptr, void* _context);
extern void* cls_realloc(void* ptr, size_t new_size);
extern void* cls_memset(void* dest, int ch, size_t count);

#endif    // __CLS_MEMORY_H