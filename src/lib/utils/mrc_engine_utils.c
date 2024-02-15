/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_engine_utils.c
 */

#include "mrc_vector.h"
#include "mrc_defines.h"
#include "mrc_engine_utils.h"
#include "mrc_engine_main.h"
#include "mrc_console.h"
#include "mrc_utils.h"

static const char* __get_next_module_str(void* _obj, int _index) {
    mrc_engine_t* _eng = (mrc_engine_t*)_obj;
    if (_index < mrc_vector_total(&_eng->modules)) {
        return mrc_module_type_t_to_string(
            (*(mrc_obj_static_t**)mrc_vector_get(&_eng->modules, _index))
                ->type);
    }
    return NULL;
}

inline const char* mrc_engine_get_modules_names(mrc_engine_t* eng) {
    return mrc_construct_str_from_list(eng, &__get_next_module_str);
}
