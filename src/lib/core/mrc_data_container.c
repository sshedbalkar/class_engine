/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_data_container.c
 */

#include "mrc_defines.h"
#include "mrc_vector.h"

static mrc_vector_t __data_map;

void mrc_data_container_static_init() {
    mrc_vector_init_capacity(&__data_map, MRC_DATA_INSTANCES_ESTIMATE);
}

void mrc_data_container_static_term() { mrc_vector_free(&__data_map); }

unsigned int mrc_data_container_add(void* _pdata) {
    unsigned int _i, _c = __data_map.capacity;
    for (_i = 0; _i < _c; ++_i) {
        if (mrc_vector_get(&__data_map, _i) == NULL) {
            mrc_vector_set(&__data_map, _i, _pdata);
            return _i;
        }
    }
    return mrc_vector_add(&__data_map, _pdata);
}

int mrc_data_container_remove(unsigned int _index) {
    mrc_vector_unset(&__data_map, _index);
    return 0;
}
void* mrc_data_container_get(unsigned int _index) {
    return mrc_vector_get(&__data_map, _index);
}