/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_vector.c
 */

#include "cls_vector.h"
#include "cls_memory.h"
#include "cls_console.h"
#include "cJSON.h"
#include <math.h>
#ifdef CLS_DEBUG_LIVE
#include <stdio.h>
#include "cls_defines.h"
#endif

void cls_vector_init(cls_vector_t *v) {
    cls_vector_init_capacity(v, VECTOR_INIT_CAPACITY);
}

void cls_vector_init_capacity(cls_vector_t *v, size_t capacity) {
    v->capacity = capacity;
    v->length = 0;
    if (capacity < 1) return;
    size_t _sz = sizeof(void *) * v->capacity;
    v->items = cls_alloc(_sz);
    cls_memset(v->items, 0, _sz);
}

int cls_vector_total(cls_vector_t *v) { return v->length; }

int cls_vector_capacity(cls_vector_t *v) { return v->capacity; }

static void cls_vector_resize(cls_vector_t *v, size_t capacity) {
#ifdef CLS_DEBUG
    cls_print("cls_vector_resize: %d to %d\n", v->capacity, capacity);
#endif

    void **items = cls_realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

unsigned int cls_vector_add(cls_vector_t *v, void *item) {
    if (v->capacity == v->length) {
        if (v->capacity == 0) v->capacity = 1;
        cls_vector_resize(v, v->capacity * 2);
    }
    v->items[v->length++] = item;
    return v->length;
}

void cls_vector_set(cls_vector_t *v, unsigned int index, void *item) {
    if (index < v->capacity) {
        v->items[index] = item;
        ++v->length;
    }
}

void cls_vector_unset(cls_vector_t *v, unsigned int index) {
    if (index < v->capacity) {
        v->items[index] = NULL;
        --v->length;
    }
}

void cls_vector_replace(cls_vector_t *v, unsigned int index, void *item) {
    if (index < v->capacity) v->items[index] = item;
}

void *cls_vector_get(cls_vector_t *v, unsigned int index) {
    if (index < v->capacity) {
        return v->items[index];
    }
    return NULL;
}

void cls_vector_delete(cls_vector_t *v, unsigned int index) {
    if (index >= v->length) return;
    unsigned int i;
    for (i = index; i < v->length - 1; ++i) {
        v->items[i] = v->items[i + 1];
    }
    --v->length;
#ifdef VECTOR_REALLOC_ON_DELETE
    if (v->length > 0 && v->length == v->capacity / 4)
        cls_vector_resize(v, v->capacity / 2);
#endif
}

void cls_vector_free(cls_vector_t *v) {
    cls_free(v->items);
    v->length = 0;
    v->capacity = 0;
}

void cls_vector_foreach(cls_vector_t *_v, cls_fn_v_vp_ui_vp_t _fn,
                        void *_param) {
    unsigned int _i;
    for (_i = 0; _i < _v->capacity; ++_i) {
        (*_fn)(_v->items[_i], _i, _param);
    }
}

void cls_vector_insert_at(cls_vector_t *_vec, unsigned int _index,
                          void *_data) {
    if (_vec->capacity == _vec->length) {
        if (_vec->capacity == 0) _vec->capacity = 1;
        cls_vector_resize(_vec, _vec->capacity * 2);
    }
    if (_vec->length > 0) {
        int _i;
        for (_i = _vec->length - 1; _i >= (int)_index; --_i) {
            _vec->items[_i + 1] = _vec->items[_i];
        }
    }
    _vec->items[_index] = _data;
    ++_vec->length;
}

// Only works for vectors populated using 'cls_vector_insert_in_asc_order()'
int cls_vector_asc_order_insert_pos(cls_vector_t *_vec, void *_data,
                                    cls_fn_i_vp_vp_t _lessthan_fn) {
    int _left = 0, _right = _vec->length - 1, _mid;
    while (_left <= _right) {
        _mid = floor(((double)(_right + _left)) / 2.0);
        if (_lessthan_fn(_vec->items[_mid], _data) == CLS_TRUE) {
            _left = _mid + 1;
        } else if (_lessthan_fn(_data, _vec->items[_mid]) == CLS_TRUE) {
            _right = _mid - 1;
        } else {
            return -1;
        }
    }
    // We found the index where the data needs to go
    return _left;
}

// Only works for vectors populated using 'cls_vector_insert_in_desc_order()'
int cls_vector_desc_order_insert_pos(cls_vector_t *_vec, void *_data,
                                     cls_fn_i_vp_vp_t _lessthan_fn) {
    int _left = 0, _right = _vec->length - 1, _mid;
    while (_left <= _right) {
        _mid = floor(((double)(_right + _left)) / 2.0);
        if (_lessthan_fn(_vec->items[_mid], _data) == CLS_TRUE) {
            _right = _mid - 1;
        } else if (_lessthan_fn(_data, _vec->items[_mid]) == CLS_TRUE) {
            _left = _mid + 1;
        } else {
            // Data already exists
            return -1;
        }
    }
    // We found the index where the data needs to go
    return _left;
}

// Only works for vectors populated using this method.
int cls_vector_insert_in_asc_order(cls_vector_t *_vec, void *_data,
                                   cls_fn_i_vp_vp_t _lessthan_fn) {
    int _pos = cls_vector_asc_order_insert_pos(_vec, _data, _lessthan_fn);
    if (_pos > -1) {
        cls_vector_insert_at(_vec, _pos, _data);
    }
    return _pos;
}

// Only works for vectors populated using this method.
int cls_vector_insert_in_desc_order(cls_vector_t *_vec, void *_data,
                                    cls_fn_i_vp_vp_t _lessthan_fn) {
    int _pos = cls_vector_desc_order_insert_pos(_vec, _data, _lessthan_fn);
    if (_pos > -1) {
        cls_vector_insert_at(_vec, _pos, _data);
    }
    return _pos;
}

void *cls_vector_pop_back(cls_vector_t *_vec) {
    int _c = _vec->length - 1;
    void *_data = NULL;
    if (_c > -1) {
        _data = _vec->items[_c];
        cls_vector_unset(_vec, _c);
    }
    return _data;
}

cJSON *cls_vector_serialize_compact(cls_vector_t *_vec) {
    cJSON *_itemsJ = cJSON_CreateArray();
#ifdef CLS_DEBUG_LIVE
    cJSON *_ptrJ;
    int _j, _l = _vec->length;
    char *_buff = cls_alloc(16);
    for (_j = 0; _j < _l; ++_j) {
        // if (_vec->items[_j] == NULL) {
        //     cls_print("Len: %d, Cap: %d, inserting null\n", _l,
        //     _vec->capacity); CLS_CRASH_ME();
        // }
        snprintf(_buff, 16, "%p", _vec->items[_j]);
        _ptrJ = cJSON_CreateString(_buff);
        cJSON_AddItemToArray(_itemsJ, _ptrJ);
    }
    cls_free(_buff);
#endif
    //
    return _itemsJ;
}

void cls_vector_serialize_compact_no_alloc(cls_vector_t *_vec, char *_buff,
                                           unsigned int _size) {
    unsigned int _l = _vec->length, _j, _count = 1;
    _buff[0] = '[';
    --_size;
    for (_j = 0; _j < _l; ++_j) {
        _count += snprintf(&_buff[_count], _size - _count - 1, "%p, ",
                           _vec->items[_j]);
    }
    _buff[_count - 2] = ']';
    _buff[_count - 1] = '\0';
}

cJSON *cls_vector_serialize(cls_vector_t *_vec) {
    cJSON *_vecJ = cJSON_CreateObject();
    cJSON_AddNumberToObject(_vecJ, "length", _vec->length);
    cJSON_AddNumberToObject(_vecJ, "capacity", _vec->capacity);
    cJSON_AddItemToObject(_vecJ, "items", cls_vector_serialize_compact(_vec));
    return _vecJ;
}
