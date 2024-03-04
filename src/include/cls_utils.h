/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: cls_utils.h
*/
#ifndef __CLS_UTILS_H
#define __CLS_UTILS_H

#include "cls_types.h"

extern unsigned int cls_util_get_unique_id();
extern const char* cls_util_construct_str_from_list(void* obj,
                                                    cls_fn_ccp_vp_i_t fn);
extern char* cls_util_get_str_buff();
extern int cls_util_ptr_to_str(void* _ptr);

extern unsigned int __id;

#endif    // __CLS_UTILS_H