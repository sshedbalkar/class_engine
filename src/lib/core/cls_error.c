/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_error.c
 */

#include "cls_defines.h"
#include "cls_error.h"
#include "cJSON.h"
#include "cls_utils.h"

static cls_error_t __error;

cls_error_t* cls_error_get_last() { return &__error; }
void cls_error_set(unsigned int _id, cls_error_type_t _type, const char* _msg) {
    __error.id = _id;
    __error.type = _type;
    __error.message = _msg;
}

void cls_error_clear() {
    __error.id = 0;
    __error.type = 0;
    __error.message = NULL_STR;
}

const char* cls_error_serialized() {
    cJSON* _err = cJSON_CreateObject();
    cJSON_AddNumberToObject(_err, "id", __error.id);
    cJSON_AddStringToObject(_err, "type",
                            cls_error_type_to_string(__error.type));
    cJSON_AddStringToObject(_err, "message", __error.message);

    const char* _buff = cls_util_get_str_buff();
    cJSON_PrintPreallocated(_err, (char*)_buff, CLS_DEFAULT_STR_BUFF_SIZE, 1);
    cJSON_Delete(_err);
    return _buff;
}