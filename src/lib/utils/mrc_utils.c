/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: mrc_utils.c
*/
#include <string.h>
#include "mrc_defines.h"
#include "mrc_utils.h"
#include "mrc_console.h"

unsigned int __id = 0;
static char __str_buffer[MRC_DEFAULT_STR_BUFF_SIZE];

inline unsigned int mrc_util_get_unique_id() { return __id++; }

const char* mrc_construct_str_from_list(void* _list, mrc_fn_ccp_vp_i_t _fn) {
    int _count = 0, _tlen = 0, _size;
    memset(__str_buffer, 0, MRC_DEFAULT_STR_BUFF_SIZE);
    const char* _str = _fn(_list, _count++);
    while (_str != NULL) {
        _size = strlen(_str);
        if (_tlen > 0) {
            __str_buffer[_tlen] = ',';
            ++_tlen;
        }
        if (_size >= MRC_DEFAULT_STR_BUFF_SIZE - _tlen)
            _size = MRC_DEFAULT_STR_BUFF_SIZE - _tlen - 1;
        memcpy(&__str_buffer[_tlen], _str, _size);
        _tlen += _size;
        if ((_tlen + 1) < MRC_DEFAULT_STR_BUFF_SIZE) {
            _str = _fn(_list, _count++);
        } else
            _str = NULL;
    }
    return (const char*)&__str_buffer;
}
