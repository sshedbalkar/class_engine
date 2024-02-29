/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_timer.h
 */
#ifndef __CLS_TIMER_H
#define __CLS_TIMER_H

#include <time.h>
#include "cls_defines.h"

typedef struct timespec timespec;

extern void cls_timer_static_init();
extern void cls_timer_static_term();
extern void cls_timer_run();
extern void cls_timer_pause();
extern void cls_timer_resume();
extern void cls_timer_toggle();
extern void cls_timer_stop();
extern timespec cls_timer_time();
extern timespec cls_timer_diff(const timespec start, const timespec end);
extern void cls_timer_set_fps(unsigned int fps);

#endif    // __CLS_TIMER_H