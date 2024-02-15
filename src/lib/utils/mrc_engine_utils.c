/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_engine_utils.c
 */

#include <string.h>
#include "mrc_vector.h"
#include "mrc_defines.h"
#include "mrc_engine_utils.h"
#include "mrc_engine_main.h"
#include "mrc_console.h"

static char __str_buffer[MRC_DEFAULT_STR_BUFF_SIZE];

char* mrc_engine_get_modules_names(mrc_engine_t* eng) {
    int _i, _total = mrc_vector_total(&eng->modules), _tlen = 0, _size;
    const char* _str;
    memset(__str_buffer, 0, MRC_DEFAULT_STR_BUFF_SIZE);
    for (_i = 0; _i < _total; ++_i) {
        _str = mrc_module_type_t_to_string(
            (*(mrc_obj_static_t**)mrc_vector_get(&eng->modules, _i))->type);
        _size = strlen(_str);
        if (_tlen > 0) {
            __str_buffer[_tlen] = ',';
            ++_tlen;
        }
        if (_size >= MRC_DEFAULT_STR_BUFF_SIZE - _tlen)
            _size = MRC_DEFAULT_STR_BUFF_SIZE - _tlen - 1;
        memcpy(&__str_buffer[_tlen], _str, _size);
        _tlen += _size;
        if ((_tlen + 1) == MRC_DEFAULT_STR_BUFF_SIZE) _i = _total;
    }
    __str_buffer[_tlen] = NULL_STR;
    return (char*)&__str_buffer;
}