/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: mrc_utils.h
*/
#ifndef __MRC_UTILS_H
#define __MRC_UTILS_H

#include "mrc_types.h"

extern unsigned int mrc_util_get_unique_id();
extern const char* mrc_construct_str_from_list(void* obj, mrc_fn_ccp_vp_i_t fn);

#endif    // __MRC_UTILS_H