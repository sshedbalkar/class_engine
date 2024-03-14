/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_data_container.c
 */

#include "cls_defines.h"
#include "cls_vector.h"
#include "cls_data_container.h"

static cls_vector_t __data_map;

void cls_data_container_static_init() {
    cls_vector_init_capacity(&__data_map, CLS_DATA_INSTANCES_ESTIMATE);
}

void cls_data_container_static_term() { cls_vector_free(&__data_map); }

unsigned int cls_data_container_add(void* _pdata) {
    unsigned int _i, _c = __data_map.capacity;
    for (_i = 0; _i < _c; ++_i) {
        if (cls_vector_get(&__data_map, _i) == NULL) {
            cls_vector_set(&__data_map, _i, _pdata);
            return _i;
        }
    }
    return cls_vector_add(&__data_map, _pdata);
}

int cls_data_container_remove(unsigned int _index) {
    cls_vector_unset(&__data_map, _index);
    return 0;
}
void* cls_data_container_get(unsigned int _index) {
    return cls_vector_get(&__data_map, _index);
}