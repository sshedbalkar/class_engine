/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __MRC_DEFINES_H
#define __MRC_DEFINES_H

#ifndef NULL
#define NULL ((void *)0)
#endif
#define NULL_STR '\0'

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#define MRC_DEFAULT_STR_BUFF_SIZE 1024
#define MRC_EVENTS_COUNT_MAX \
    256    // Max number of events in the app (approx), should be greater than
           // or equal, try to be conservative with the estimate
#define MRC_EVENTS_CALLBACKS_PER_EVENT_COUNT 2
#define MRC_DESIRED_FPS 60
#define MRC_DATA_INSTANCES_ESTIMATE 256
#endif    // __MRC_DEFINES_H