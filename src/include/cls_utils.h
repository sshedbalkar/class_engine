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
extern void cls_util_static_init();
extern void cls_util_static_term();
extern const char* cls_util_construct_str_from_list(void* obj,
                                                    cls_fn_ccp_vp_i_t fn);
extern char* cls_util_get_str_buff();
extern int cls_util_ptr_to_str(void* _ptr);
extern unsigned int cls_util_upper_powerof_two(unsigned int v);
extern unsigned int cls_util_round(double number);
extern unsigned int cls_util_upper_twos_exponent(unsigned int _val);
extern int cls_rand_in_range(int _lower, int _upper);

#endif    // __CLS_UTILS_H