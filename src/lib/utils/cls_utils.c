/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: cls_utils.c
*/
#include <string.h>
#include <stdio.h>
#include "cls_defines.h"
#include "cls_utils.h"
#include "cls_console.h"

unsigned int __id = 0;
static char __str_buffer[CLS_DEFAULT_STR_BUFF_SIZE];

inline unsigned int cls_util_get_unique_id() { return __id++; }

const char* cls_util_construct_str_from_list(void* _list,
                                             cls_fn_ccp_vp_i_t _fn) {
    int _count = 0, _tlen = 0, _size;
    memset(__str_buffer, 0, CLS_DEFAULT_STR_BUFF_SIZE);
    const char* _str = _fn(_list, _count++);
    while (_str != NULL) {
        _size = strlen(_str);
        if (_tlen > 0) {
            __str_buffer[_tlen] = ',';
            ++_tlen;
        }
        if (_size >= CLS_DEFAULT_STR_BUFF_SIZE - _tlen)
            _size = CLS_DEFAULT_STR_BUFF_SIZE - _tlen - 1;
        memcpy(&__str_buffer[_tlen], _str, _size);
        _tlen += _size;
        if ((_tlen + 1) < CLS_DEFAULT_STR_BUFF_SIZE) {
            _str = _fn(_list, _count++);
        } else
            _str = NULL;
    }
    return (const char*)&__str_buffer;
}

char* cls_util_get_str_buff() { return &__str_buffer; }

int cls_util_ptr_to_str(void* _ptr) {
    return snprintf(&__str_buffer, CLS_DEFAULT_STR_BUFF_SIZE, "%p", _ptr);
}