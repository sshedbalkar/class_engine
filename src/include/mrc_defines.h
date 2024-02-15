/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __MRC_DEFINES_H
#define __MRC_DEFINES_H

#ifndef NULL
#define NULL 0
#endif
#define NULL_STR '\0'

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#define MRC_DEFAULT_STR_BUFF_SIZE 1024
#endif    // __MRC_DEFINES_H