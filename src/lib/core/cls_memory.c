/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_memory.c
 */

#include <stdlib.h>
#include <string.h>
#include "cls_memory.h"
#include "cls_console.h"
#include "cls_vector.h"
#include "cls_utils.h"
#include "cls_error.h"

#ifdef CLS_DEBUG
#include "cJSON.h"
#ifdef CLS_DEBUG_LIVE
#include "cls_defines.h"
#include <stdio.h>
#endif
#endif
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
static unsigned int __page_count =
    21;    // Should be the size of the array below
static unsigned int __page_chunk_counts[] = {
    8,       // 2^0  = 1
    128,     // 2^1  = 2
    128,     // 2^2  = 4
    128,     // 2^3  = 8
    128,     // 2^4  = 16
    128,     // 2^5  = 32
    1024,    // 2^6  = 64
    16,      // 2^7  = 128
    16,      // 2^8  = 256
    16,      // 2^9  = 512
    16,      // 2^10 = 1024
    16,      // 2^11 = 2048
    8,       // 2^12 = 4096
    8,       // 2^13 = 8192
    4,       // 2^14 = 16384
    4,       // 2^15 = 32768
    4,       // 2^16 = 65536
    2,       // 2^17 = 131072
    1,       // 2^18 = 262144
    1,       // 2^19 = 524288
    1,       // 2^20 = 1048576
};
typedef struct __memory_raw_t {
    size_t size;
    void* memory;
} __memory_raw_t;

typedef struct __memory_page_t {
    __memory_raw_t raw;
    size_t chunk_size;
    unsigned int chunk_total;
    unsigned int chunk_allocated_count;
    void* next_available;
    void* chunk_last;
    cls_vector_t free_list;
#ifdef CLS_DEBUG
    void* chunk_first;
    unsigned int total_allocations;
    unsigned int total_frees;
    unsigned int multi_frees;
    unsigned int max_in_use;
#endif
} __memory_page_t;

typedef struct __memory_t {
    cls_vector_t mem_banks;
#ifdef CLS_DEBUG
    unsigned int total_allocations;
    unsigned int total_frees;
#endif
} __memory_t;

static size_t __charSz = sizeof(char);
static __memory_t __memory;
////////////////////////////////////////////////////////
static __memory_page_t* __create_page(size_t _chunk_size,
                                      unsigned int _chunk_count) {
    __memory_page_t* _page;
    _page = (__memory_page_t*)cls_alloc(sizeof(__memory_page_t));
    _page->raw.size = _chunk_size * _chunk_count;
    _page->raw.memory = cls_alloc(_page->raw.size);
    _page->chunk_size = _chunk_size;
    _page->chunk_total = _chunk_count;
    _page->chunk_allocated_count = 0;
    _page->next_available = _page->raw.memory;
    _page->chunk_last =
        _page->next_available + _page->raw.size - _page->chunk_size;
#ifdef CLS_DEBUG
    _page->chunk_first = _page->next_available;
    _page->total_allocations = 0;
    _page->total_frees = 0;
    _page->multi_frees = 0;
    _page->max_in_use = 0;
#endif
    cls_vector_init_capacity(&_page->free_list, _chunk_count);
    return _page;
}

static void __destroy_page(__memory_page_t* _page) {
    // cls_print("Freeing page: chunk: %d\n", _page->chunk_size);
    cls_vector_free(&_page->free_list);
    _page->next_available = NULL;
    cls_free(_page->raw.memory);
    _page->raw.memory = NULL;
    cls_free(_page);
}

int __has_null(cls_vector_t* _vec) {
    int _i, _c = _vec->length;
    for (_i = 0; _i < _c; ++_i) {
        if (_vec->items[_i] == NULL) return 1;
    }
    return 0;
}

void cls_memory_static_init() {
    unsigned int _i, _chunkSz;
    __memory_page_t* _page;
    cls_vector_init_capacity(&__memory.mem_banks, __page_count);
    for (_i = 0; _i < __page_count; ++_i) {
        _chunkSz = 1 << _i;
        _page = __create_page(__charSz * _chunkSz, __page_chunk_counts[_i]);
        cls_vector_add(&__memory.mem_banks, _page);
    }
#ifdef CLS_DEBUG
    __memory.total_allocations = 0;
    __memory.total_frees = 0;
#endif
}

void cls_memory_static_term() {
    int _i, _c = cls_vector_total(&__memory.mem_banks);
    __memory_page_t* _page;
    for (_i = _c - 1; _i > -1; --_i) {
        _page = cls_vector_get(&__memory.mem_banks, _i);
        __destroy_page(_page);
        cls_vector_replace(&__memory.mem_banks, _i, NULL);
    }
    cls_vector_free(&__memory.mem_banks);
}

void* cls_alloc_new(size_t _size) {
    // if (_size > 16)
    //     return cls_alloc(_size);
    // else if (_size < 1)
    //     cls_print("0 alloc request\n");
    unsigned int _mem_bank_id = cls_util_upper_twos_exponent(_size);
    // if (_mem_bank_id == 13) {
    //     cls_print("Alloc request: bank: %d, size:%d\n", _mem_bank_id, _size);
    // }
    void* _ptr = NULL;
    if ((int)_mem_bank_id < cls_vector_total(&__memory.mem_banks)) {
        __memory_page_t* _page =
            cls_vector_get(&__memory.mem_banks, _mem_bank_id);
        if (_page->chunk_allocated_count < _page->chunk_total) {
            if (cls_vector_total(&_page->free_list) > 0) {
                _ptr = cls_vector_pop_back(&_page->free_list);

                // char* _buff = cls_alloc(65536);
                // cls_vector_serialize_compact_no_alloc(&_page->free_list,
                // _buff,
                //                                       65536);
                // cls_print("Allocated, Ptr: %p, Free: %s\n", _ptr, _buff);
                // cls_free(_buff);
                if (__has_null(&_page->free_list)) {
                    cls_print("1 Chunk: %d, found null\n", _page->chunk_size);
                    CLS_CRASH_ME();
                }
            } else {
                _ptr = _page->next_available;
                _page->next_available += _page->chunk_size;
                ++_page->max_in_use;
            }
            // if (_page->chunk_size == 8192) {
            //     cls_print("Allocated: %d, %p\n", _page->chunk_size, _ptr);
            // }
            ++_page->chunk_allocated_count;
#ifdef CLS_DEBUG
            ++_page->total_allocations;
            ++__memory.total_allocations;
#endif
        } else {
            // cls_error_set(CLS_ERROR_FATAL, CLS_ERR_ID_MEM_PAGE_OUT_OF_MEMORY,
            //               "Out of memory");
            // cls_print("[MEM]Page[%d * %d]: Out of memory\n",
            // _page->chunk_size,
            //          _page->chunk_total);
            _ptr = cls_alloc(_size);
        }
    } else {
        cls_print("Mem request unavailable: %d, bank: %d\n", _size,
                  _mem_bank_id);
        _ptr = cls_alloc(_size);
    }
    return _ptr;
}

static int __ptr_compare(void* _ptra, void* _ptrb) {
    if (_ptra < _ptrb) return CLS_TRUE;
    return CLS_FALSE;
}

static bool_t __free_internal(__memory_page_t* _page, void* _ptr) {
    if (_ptr >= _page->raw.memory && _ptr <= _page->chunk_last) {
        if (((long)_ptr - (long)_page->raw.memory) % _page->chunk_size == 0) {
            if (_ptr == NULL)
                cls_print("Inserting null, chunk: %d\n", _page->chunk_size);
            int _id = cls_vector_insert_in_asc_order(&_page->free_list, _ptr,
                                                     __ptr_compare);
            if (__has_null(&_page->free_list)) {
                cls_print("2 Chunk: %d, found null\n", _page->chunk_size);
                CLS_CRASH_ME();
            }
            // if (_page->chunk_size == 64) {
            //     cls_print("Inserting into free, chunk: %d, len: %d, ptr:
            //     %p\n",
            //               _page->chunk_size,
            //               cls_vector_total(&_page->free_list), _ptr);
            // }
            if (_id > -1) {
                --_page->chunk_allocated_count;
#ifdef CLS_DEBUG
                ++_page->total_frees;
                ++__memory.total_frees;
#endif
            } else {
#ifdef CLS_DEBUG
                ++_page->multi_frees;
#endif
                cls_error_set(CLS_ERROR_RECOVERABLE,
                              CLS_ERR_ID_MEM_PAGE_MULTI_FREE, "Multi-free");
                cls_print("[MEM]Page[%d * %d: %p]: Multi free\n",
                          _page->chunk_size, _page->chunk_total, _ptr);
            }
        } else {
            cls_error_set(CLS_ERROR_RECOVERABLE,
                          CLS_ERR_ID_MEM_PAGE_UNKNOWN_CHUNK_SIZE,
                          "Unknown chunk size");
            cls_print("[MEM]Page[%d * %d]: Unknown chunk size: Rel Addr: %u\n",
                      _page->chunk_size, _page->chunk_total,
                      ((long)_ptr - (long)_page->raw.memory));
        }
        return CLS_TRUE;
    } else {
        return CLS_FALSE;
    }
}

void cls_free_new(void* _ptr) {
    unsigned int _i, _c = cls_vector_total(&__memory.mem_banks);
    bool_t _freed = CLS_FALSE;
    if (_ptr != NULL) {
        for (_i = 0; _i < _c; ++_i) {
            if (__free_internal(cls_vector_get(&__memory.mem_banks, _i),
                                _ptr) == CLS_TRUE) {
                _freed = CLS_TRUE;
                _i = _c;
            }
        }
    }
    if (_freed == CLS_FALSE) {
        // cls_print("Freeing unknown mem: %p\n", _ptr);
        cls_free(_ptr);
    }
}

int cls_memory_free_list_null_check() {
    unsigned int _i, _c = __memory.mem_banks.length;
    __memory_page_t* _page;
    for (_i = 0; _i < _c; ++_i) {
        _page = __memory.mem_banks.items[_i];
        if (__has_null(&_page->free_list)) {
            return 1;
        }
    }
    return 0;
}

#ifdef CLS_DEBUG
static cJSON* __memory_raw_serialize(__memory_page_t* _page) {
    cJSON* _rawJ = cJSON_CreateObject();
    cJSON_AddNumberToObject(_rawJ, "size", _page->raw.size);
#ifdef CLS_DEBUG_LIVE
#ifdef CLS_MEM_DETAILED_REPORT
    void* _ptr = _page->raw.memory;
    unsigned int _ci = 0;
    char* _buff2 = cls_alloc_new(8192);
    while (_ptr <= _page->chunk_last) {
        _ci += snprintf(&_buff2[_ci], (8192 - _ci), "%p ", _ptr);
        _ptr += _page->chunk_size;
    }
    _buff2[_ci - 1] = '\0';
    cJSON_AddStringToObject(_rawJ, "memory", _buff2);
    cls_free_new(_buff2);
#else
    cJSON_AddStringToObject(_rawJ, "memory", "{}");
#endif
#endif
    return _rawJ;
}

static cJSON* __memory_page_serialize(__memory_page_t* _page) {
    cJSON* _pageJ;
    char _buff[16];
    _pageJ = cJSON_CreateObject();
    cJSON_AddNumberToObject(_pageJ, "chunk_size", _page->chunk_size);
    cJSON_AddNumberToObject(_pageJ, "chunk_total", _page->chunk_total);
    cJSON_AddNumberToObject(_pageJ, "chunk_allocated_count",
                            _page->chunk_allocated_count);
    snprintf(_buff, 16, "%p", _page->next_available);
    // cls_util_ptr_to_str(_page->next_available);
    cJSON_AddStringToObject(_pageJ, "next_available", _buff);
    snprintf(_buff, 16, "%p", _page->chunk_first);
    cJSON_AddStringToObject(_pageJ, "chunk_first", _buff);
    snprintf(_buff, 16, "%p", _page->chunk_last);
    cJSON_AddStringToObject(_pageJ, "chunk_last", _buff);
    cJSON_AddNumberToObject(_pageJ, "total_allocations",
                            _page->total_allocations);
    cJSON_AddNumberToObject(_pageJ, "total_frees", _page->total_frees);
    cJSON_AddNumberToObject(_pageJ, "multi_frees", _page->multi_frees);
    cJSON_AddNumberToObject(_pageJ, "max_in_use", _page->max_in_use);
    cJSON_AddItemToObject(_pageJ, "free_list",
                          cls_vector_serialize(&_page->free_list));
    cJSON_AddItemToObject(_pageJ, "raw", __memory_raw_serialize(_page));
    return _pageJ;
}

char* cls_memory_serialize() {
    cJSON* _root = cJSON_CreateObject();
    __memory_page_t* _page;
    cJSON_AddNumberToObject(_root, "total_allocations",
                            __memory.total_allocations);
    cJSON_AddNumberToObject(_root, "total_frees", __memory.total_frees);
    cJSON *_banks = cJSON_CreateArray(), *_pageJ;
    cJSON_AddItemToObject(_root, "mem_banks", _banks);
    int _i, _c = cls_vector_total(&__memory.mem_banks);
    if (cls_memory_free_list_null_check()) CLS_CRASH_ME();
    for (_i = 0; _i < _c; ++_i) {
        _page = cls_vector_get(&__memory.mem_banks, _i);
        _pageJ = __memory_page_serialize(_page);
        cJSON_AddItemToArray(_banks, _pageJ);
    }
    char* _json = cJSON_PrintBuffered(_root, 8192, 0);
    cJSON_Delete(_root);
    return _json;
}
#endif
////////////////////////////////////////////////////////
void* cls_alloc(size_t size) { return malloc(size); }
void* cls_alloc_c(size_t _size, void* _context) {
    (void)_context;
    // cls_print("cls_alloc_c: %d", _size);
    return malloc(_size);
    // return cls_alloc_new(_size);
}

void cls_free(void* ptr) { free(ptr); }
void cls_free_c(void* _ptr, void* _context) {
    (void)_context;
    free(_ptr);
    // cls_free_new(_ptr);
}

void* cls_realloc(void* ptr, size_t new_size) { return realloc(ptr, new_size); }

void* cls_memset(void* dest, int ch, size_t count) {
    return memset(dest, ch, count);
}

void* cls_calloc(size_t num, size_t size) { return calloc(num, size); }
