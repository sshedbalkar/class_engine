/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <stdlib.h>
#include <string.h>
#include "cls_memory.h"
#include "cls_console.h"
#include "cls_vector.h"
#include "cls_utils.h"
#include "cls_error.h"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
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
} __memory_page_t;

typedef struct __memory_t {
    cls_vector_t mem_banks;
} __memory_t;

static size_t __charSz = sizeof(char);
static __memory_t __memory;
////////////////////////////////////////////////////////
static __memory_page_t* __create_page(size_t _chunk_size,
                                      unsigned int _chunk_total) {
    __memory_page_t* _page;
    _page = (__memory_page_t*)cls_alloc(sizeof(__memory_page_t));
    _page->raw.size = _chunk_size * _chunk_total;
    _page->raw.memory = cls_alloc(_page->raw.size);
    _page->chunk_size = _chunk_size;
    _page->chunk_total = _chunk_total;
    _page->chunk_allocated_count = 0;
    _page->next_available = _page->raw.memory;
    _page->chunk_last =
        _page->next_available + _page->raw.size - _page->chunk_size;
    cls_vector_init_capacity(&_page->free_list, _chunk_total);
    return NULL;
}

static void __destroy_page(__memory_page_t* _page) {
    cls_vector_free(&_page->free_list);
    _page->next_available = NULL;
    cls_free(_page->raw.memory);
    cls_free(_page);
}

void cls_memory_static_init() {
    int _banks = 6, _i, _chunks = 16, _chunkSz;
    __memory_page_t* _page;
    cls_vector_init_capacity(&__memory.mem_banks, _banks);
    for (_i = 0; _i < _banks; ++_i) {
        _chunkSz = 1 << _i;
        _page = __create_page(__charSz * _chunkSz, _chunks);
        cls_vector_add(&__memory.mem_banks, _page);
    }
}

void cls_memory_static_term() {
    int _i, _c = cls_vector_total(&__memory.mem_banks);
    __memory_page_t* _page;
    for (_i = 0; _i < _c; ++_i) {
        _page = cls_vector_get(&__memory.mem_banks, _i);
        __destroy_page(_page);
    }
    cls_vector_free(&__memory.mem_banks);
}

void* cls_alloc_new(size_t _size) {
    unsigned int _mem_bank_id = cls_util_upper_twos_exponent(_size);
    __memory_page_t* _page = cls_vector_get(&__memory.mem_banks, _mem_bank_id);
    void* _ptr = NULL;
    if (_page->chunk_allocated_count < _page->chunk_total) {
        if (cls_vector_total(&_page->free_list) > 0) {
            _ptr = cls_vector_pop_back(&_page->free_list);
        } else {
            _ptr = _page->next_available;
            _page->next_available += _page->chunk_size;
        }
        ++_page->chunk_allocated_count;
    } else {
        cls_error_set(CLS_ERROR_FATAL, CLS_ERR_ID_MEM_PAGE_OUT_OF_MEMORY,
                      "Out of memory");
        cls_print("[MEM]Page[%d * %d]: Out of memory\n", _page->chunk_size,
                  _page->chunk_total);
    }
    return _ptr;
}

void __free_internal(__memory_page_t* _page, unsigned int _index, void* _ptr) {
    if (_ptr >= _page->raw.memory && _ptr <= _page->chunk_last) {
        long _addr = _ptr;
        _addr -= (long)_page->raw.memory;
        if (_addr % _page->chunk_size == 0) {
            cls_vector_add(&_page->free_list, _ptr);
            --_page->chunk_allocated_count;
        }
    }
}

void cls_free_new(void* _ptr) {
    cls_vector_foreach(&__memory.mem_banks, __free_internal, _ptr);
}
////////////////////////////////////////////////////////
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

void* cls_calloc(size_t num, size_t size) { return calloc(num, size); }
