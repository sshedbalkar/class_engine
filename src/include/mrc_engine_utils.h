/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_engine_utils.h
 */
#ifndef __MRC_ENGINE_UTILS_H
#define __MRC_ENGINE_UTILS_H

struct mrc_engine_t;
typedef struct mrc_engine_t mrc_engine_t;

extern const char* mrc_engine_get_modules_names(mrc_engine_t* eng);
#endif    // __MRC_ENGINE_UTILS_H