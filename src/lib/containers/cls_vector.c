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
#ifdef DEBUG_ON
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
    if (index < v->capacity) return v->items[index];
    return NULL;
}

void cls_vector_delete(cls_vector_t *v, unsigned int index) {
    if (index >= v->length) return;

    // v->items[index] = NULL;
    // int i;
    // for (i = 0; i < v->length - 1; i++) {
    //     v->items[i] = v->items[i + 1];
    //     v->items[i + 1] = NULL;
    // }
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
    unsigned int _i;
    for (_i = _vec->length - 1; _i > _index; --_i) {
        _vec->items[_i + 1] = _vec->items[_i];
    }
    _vec->items[_index] = _data;
    ++_vec->length;
}

// Only works for vectors populated using 'cls_vector_insert_in_asc_order()'
int cls_vector_asc_order_insert_pos(cls_vector_t *_vec, void *_data,
                                    cls_fn_i_vp_vp_t _lessthan_fn) {
    size_t _left = 0, _right = _vec->length - 1, _mid = 0;
    while (_left <= _right) {
        _mid = _left + (_right - _left) / 2;
        if (_lessthan_fn(_vec->items[_mid], _data) == CLS_TRUE) {
            _left = _mid + 1;
        } else if (_lessthan_fn(_data, _vec->items[_mid]) == CLS_TRUE) {
            _right = _mid - 1;
        } else {
            // Data already exists
            return -1;
        }
    }
    // We found the index where the data needs to go
    return _mid;
}

// Only works for vectors populated using 'cls_vector_insert_in_desc_order()'
int cls_vector_desc_order_insert_pos(cls_vector_t *_vec, void *_data,
                                     cls_fn_i_vp_vp_t _lessthan_fn) {
    size_t _left = 0, _right = _vec->length - 1, _mid = 0;
    while (_left <= _right) {
        _mid = _left + (_right - _left) / 2;
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
    return _mid;
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
    int _c = _vec->length;
    void *_data = NULL;
    if (_c > 0) {
        _data = cls_vector_get(_vec, _c);
        cls_vector_unset(_vec, _c);
    }
    return _data;
}