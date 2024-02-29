/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_engine_utils.c
 */

#include "cls_vector.h"
#include "cls_defines.h"
#include "cls_engine_utils.h"
#include "cls_engine_main.h"
#include "cls_console.h"
#include "cls_utils.h"

static const char* __get_next_module_str(void* _obj, int _index) {
    cls_engine_t* _eng = (cls_engine_t*)_obj;
    if (_index < cls_vector_total(&_eng->modules)) {
        return cls_module_type_t_to_string(
            (*(cls_obj_static_t**)cls_vector_get(&_eng->modules, _index))
                ->type);
    }
    return NULL;
}

inline const char* cls_engine_get_modules_names(cls_engine_t* eng) {
    return cls_construct_str_from_list(eng, &__get_next_module_str);
}
