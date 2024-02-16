/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_timer.h
 */
#ifndef __MRC_TIMER_H
#define __MRC_TIMER_H

#include <time.h>
#include "mrc_defines.h"

typedef struct timespec timespec;

extern void mrc_timer_static_init();
extern void mrc_timer_static_term();
extern void mrc_timer_run();
extern void mrc_timer_pause();
extern void mrc_timer_resume();
extern void mrc_timer_toggle();
extern timespec mrc_timer_time();
extern timespec mrc_timer_diff(const timespec start, const timespec end);
extern void mrc_timer_set_fps(unsigned int fps);

#endif    // __MRC_TIMER_H