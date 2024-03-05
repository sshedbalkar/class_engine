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

#ifdef CLS_DEBUG
#include "cJSON.h"
#ifdef CLS_DEBUG_LIVE
#include <stdio.h>
#endif
#endif
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
#ifdef CLS_DEBUG
    unsigned int total_allocations;
    unsigned int total_frees;
    unsigned int multi_frees;
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
#ifdef CLS_DEBUG
    _page->total_allocations = 0;
    _page->total_frees = 0;
    _page->multi_frees = 0;
#endif
    cls_vector_init_capacity(&_page->free_list, _chunk_total);
    return _page;
}

static void __destroy_page(__memory_page_t* _page) {
    cls_vector_free(&_page->free_list);
    _page->next_available = NULL;
    cls_free(_page->raw.memory);
    cls_free(_page);
}

void cls_memory_static_init() {
    int _banks = 8, _i, _chunks = 8, _chunkSz;
    __memory_page_t* _page;
    cls_vector_init_capacity(&__memory.mem_banks, _banks);
    for (_i = 0; _i < _banks; ++_i) {
        _chunkSz = 1 << _i;
        cls_print("Adding page: %d * %d\n", _chunkSz, _chunks);
        _page = __create_page(__charSz * _chunkSz, _chunks);
        cls_vector_add(&__memory.mem_banks, _page);
    }
    cls_print("Bank size: %d\n", __memory.mem_banks.length);
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
#ifdef CLS_DEBUG
        ++_page->total_allocations;
        ++__memory.total_allocations;
#endif
    } else {
        cls_error_set(CLS_ERROR_FATAL, CLS_ERR_ID_MEM_PAGE_OUT_OF_MEMORY,
                      "Out of memory");
        cls_print("[MEM]Page[%d * %d]: Out of memory\n", _page->chunk_size,
                  _page->chunk_total);
    }
    return _ptr;
}

static int __ptr_compare(void* _ptra, void* _ptrb) {
    if (_ptra < _ptrb) return CLS_TRUE;
    return CLS_FALSE;
}

void __free_internal(__memory_page_t* _page, unsigned int _index, void* _ptr) {
    (void)_index;
    if (_ptr >= _page->raw.memory && _ptr <= _page->chunk_last) {
        long _addr = (long)_ptr;
        _addr -= (long)_page->raw.memory;
        if (_addr % _page->chunk_size == 0) {
            // cls_vector_add(&_page->free_list, _ptr);
            int _id = cls_vector_insert_in_asc_order(&_page->free_list, _ptr,
                                                     __ptr_compare);
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
                      _page->chunk_size, _page->chunk_total, _addr);
        }
    }
}

void cls_free_new(void* _ptr) {
    cls_vector_foreach(&__memory.mem_banks,
                       (cls_fn_v_vp_ui_vp_t)__free_internal, _ptr);
}

#ifdef CLS_DEBUG
char* cls_memory_serialize() {
    cJSON* _root = cJSON_CreateObject();
    __memory_page_t* _page;
    cJSON_AddNumberToObject(_root, "total_allocations",
                            __memory.total_allocations);
    cJSON_AddNumberToObject(_root, "total_frees", __memory.total_frees);
    cJSON *_banks = cJSON_CreateArray(), *_pageJ, *_freeJ, *_freesJ, *_ptrJ,
          *_rawJ;
    void* _ptr;
    unsigned int _ci = 0;
    char* _buff = cls_alloc(8192);
    cJSON_AddItemToObject(_root, "mem_banks", _banks);
    int _i, _c = cls_vector_total(&__memory.mem_banks), _j, _l;
    for (_i = 0; _i < _c; ++_i) {
        _page = cls_vector_get(&__memory.mem_banks, _i);
        cls_print("Page: %p\n", _page);
        _pageJ = cJSON_CreateObject();
        cJSON_AddNumberToObject(_pageJ, "chunk_size", _page->chunk_size);
        cJSON_AddNumberToObject(_pageJ, "chunk_total", _page->chunk_total);
        cJSON_AddNumberToObject(_pageJ, "chunk_allocated_count",
                                _page->chunk_allocated_count);
        cJSON_AddNumberToObject(_pageJ, "total_allocations",
                                _page->total_allocations);
        cJSON_AddNumberToObject(_pageJ, "total_frees", _page->total_frees);
        cJSON_AddNumberToObject(_pageJ, "multi_frees", _page->multi_frees);
        _freeJ = cJSON_CreateObject();
        cJSON_AddItemToObject(_pageJ, "free_list", _freeJ);
        cJSON_AddNumberToObject(_freeJ, "length", _page->free_list.length);
        cJSON_AddNumberToObject(_freeJ, "capacity", _page->free_list.capacity);
        _freesJ = cJSON_CreateArray();
        cJSON_AddItemToObject(_freeJ, "items", _freesJ);
#ifdef CLS_DEBUG_LIVE
        _l = _page->free_list.length;
        for (_j = 0; _j < _l; ++_j) {
            _ptrJ = cJSON_CreateObject();
            cls_util_ptr_to_str(cls_vector_get(&_page->free_list, _j));
            sprintf(_buff, "%d", _j);
            cJSON_AddStringToObject(_ptrJ, _buff, cls_util_get_str_buff());
            cJSON_AddItemToArray(_freesJ, _ptrJ);
        }
#endif
        _rawJ = cJSON_CreateObject();
        cJSON_AddItemToObject(_pageJ, "raw", _rawJ);
        cJSON_AddNumberToObject(_rawJ, "size", _page->raw.size);
#ifdef CLS_DEBUG_LIVE
        _ptr = _page->raw.memory;
        _ci = 0;
        while (_ptr != _page->chunk_last) {
            _ci += sprintf(&_buff[_ci], "%p ", _ptr);
            _ptr += _page->chunk_size;
        }
        _buff[_ci - 1] = '\0';
        cJSON_AddStringToObject(_rawJ, "memory", _buff);
#else
        _ptrJ = cJSON_CreateArray();
        cJSON_AddItemToObject(_rawJ, "memory", _ptrJ);
#endif
    }
    cls_free(_buff);
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
