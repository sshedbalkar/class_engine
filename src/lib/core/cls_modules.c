/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: cls_modules.c
*/

#include "cls_types.h"
#include "cJSON.h"
#include "cls_error.h"
#include "cls_error_ids.h"

typedef struct {
    cls_module_type_t type;
} cls_module_t;

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