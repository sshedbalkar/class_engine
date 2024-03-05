/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#ifndef __CLS_MEMORY_H
#define __CLS_MEMORY_H

#include <stddef.h>
#ifdef CLS_DEBUG_LIVE
typedef struct cJSON cJSON;
#endif

extern void* cls_alloc(size_t size);
extern void cls_free(void* ptr);
extern void* cls_alloc_c(size_t _size, void* _context);
extern void cls_free_c(void* _ptr, void* _context);
extern void* cls_realloc(void* ptr, size_t new_size);
extern void* cls_memset(void* dest, int ch, size_t count);
extern void* cls_calloc(size_t num, size_t size);

//////////////////////////////
extern void cls_memory_static_init();
extern void cls_memory_static_term();
extern void* cls_alloc_new(size_t _size);
extern void cls_free_new(void* _ptr);

#ifdef CLS_DEBUG_LIVE
extern char* cls_memory_serialize();
#endif
#endif    // __CLS_MEMORY_H