/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_engine_utils.h
 */
#ifndef __CLS_ENGINE_UTILS_H
#define __CLS_ENGINE_UTILS_H

struct cls_engine_t;
typedef struct cls_engine_t cls_engine_t;

extern const char* cls_engine_get_modules_names(cls_engine_t* eng);
#endif    // __CLS_ENGINE_UTILS_H