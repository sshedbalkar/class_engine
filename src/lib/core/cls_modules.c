/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: cls_modules.c
*/

#include "cls_modules.h"
#include "cJSON.h"
#include "cls_error.h"
#include "cls_error_ids.h"
#include "cls_vector.h"

static cls_vector_t __modules_map;

cJSON* cls_static_module_serialize(cls_obj_static_t* _obj) {
    cJSON* _base = cJSON_CreateObject();
    if (cJSON_AddStringToObject(
            _base, "base", cls_module_type_to_string(_obj->type)) == NULL) {
        cls_error_set(CLS_ERR_ID_JSON_LIB_CONSTRUCTION, CLS_ERROR_RECOVERABLE,
                      "Json construction error");
        cJSON_Delete(_base);
        return NULL;
    }
    return _base;
}

bool_t cls_static_module_deserialize(cls_obj_static_t* _obj, cJSON* _json) {
    (void)_obj;
    (void)_json;
    return CLS_TRUE;
}

cJSON* cls_modules_serialize(cls_vector_t* _vec) {
    cJSON* _mods = cJSON_CreateArray();
    cls_obj_static_t** _module;
    cJSON* _module_json;
    int _i, _c = cls_vector_capacity(_vec);
    for (_i = 0; _i < _c; ++_i) {
        _module = (cls_obj_static_t**)cls_vector_get(_vec, _i);
        if (_module == NULL) {
            cJSON_AddNullToObject(_mods, "null");
        } else {
            _module_json = (*_module)->serialize(_module);
            cJSON_AddItemToArray(_mods, _module_json);
        }
    }
    //
    return _mods;
}

int cls_modules_deserialize(cls_vector_t* _vec, cJSON* _arr) {
    (void)_vec;
    (void)_arr;
    return 0;
}

cls_obj_static_t* cls_modules_static_init() {
    cls_vector_init_capacity(&__modules_map, CLS_MODULES_DEFAULT_MODULE_COUNT);
    return NULL;
}

int cls_modules_static_term() {
    cls_vector_free(&__modules_map);
    return 0;
}

void cls_modules_static_register_module_type(cls_obj_static_t* tHandler) {
    cls_vector_set(&__modules_map, tHandler->type, tHandler);
}

cls_obj_static_t* cls_modules_create_module(cls_module_type_t _type) {
    cls_obj_static_t* mod =
        ((cls_obj_static_t*)cls_vector_get(&__modules_map, _type))->ctor();
    return mod;
}

cls_obj_static_t* cls_modules_add_module(cls_vector_t* eng,
                                         cls_module_type_t type) {
    cls_obj_static_t* _mod = cls_modules_create_module(type);
    cls_vector_add(eng, _mod);
    return _mod;
}

int cls_modules_remove_module(cls_vector_t* eng, cls_module_type_t type) {
    int i, t, count = 0, found = 0;
    cls_obj_static_t** pmod;
    do {
        found = 0;
        t = cls_vector_total(eng);
        for (i = 0; i < t; ++i) {
            pmod = cls_vector_get(eng, i);
            if ((*pmod)->type == type) {
                found = 1;
                (*pmod)->dtor(pmod);
                cls_vector_delete(eng, i);
                i = t;
                ++count;
            }
        }
    } while (found > 0);
    return count;
}

cls_obj_static_t* cls_modules_get_module(cls_vector_t* eng,
                                         cls_module_type_t type) {
    int i, t = cls_vector_total(eng);
    cls_obj_static_t** pmodule;
    for (i = 0; i < t; ++i) {
        pmodule = (cls_obj_static_t**)cls_vector_get(eng, i);
        if ((*pmodule)->type == type) return *pmodule;
    }
    return NULL;
}

void cls_modules_remove_all_modules(cls_vector_t* eng) {
    int i, t = cls_vector_total(eng);
    cls_obj_static_t** pmodule;
    for (i = 0; i < t; ++i) {
        pmodule = (cls_obj_static_t**)cls_vector_get(eng, i);
        if (*pmodule != NULL) (*pmodule)->dtor(pmodule);
    }
}