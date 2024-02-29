/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_timer.c
 */

// #define _XOPEN_SOURCE 600
// #include <stdbool.h>
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>

#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include "cls_timer.h"
#include "cls_console.h"
#include "cls_events.h"
#include "cls_list_core_events.h"

// #define SECS_IN_DAY (24 * 60 * 60)
//
// $ ./clock_times x
// CLOCK_REALTIME : 1585985459.446 (18356 days +  7h 30m 59s)
//     resolution:          0.000000001
// CLOCK_TAI      : 1585985496.447 (18356 days +  7h 31m 36s)
//     resolution:          0.000000001
// CLOCK_MONOTONIC:      52395.722 (14h 33m 15s)
//     resolution:          0.000000001
// CLOCK_BOOTTIME :      72691.019 (20h 11m 31s)
//     resolution:          0.000000001

// static void displayClock(clockid_t clock, const char* name, bool showRes) {
//     long days;
//     struct timespec ts;

//     if (clock_gettime(clock, &ts) == -1) {
//         perror("clock_gettime");
//         exit(EXIT_FAILURE);
//     }

//     printf("%-15s: %10jd.%03ld (", name, (intmax_t)ts.tv_sec,
//            ts.tv_nsec / 1000000);

//     days = ts.tv_sec / SECS_IN_DAY;
//     if (days > 0) printf("%ld days + ", days);

//     printf("%2dh %2dm %2ds", (int)(ts.tv_sec % SECS_IN_DAY) / 3600,
//            (int)(ts.tv_sec % 3600) / 60, (int)ts.tv_sec % 60);
//     printf(")\n");

//     if (clock_getres(clock, &ts) == -1) {
//         perror("clock_getres");
//         exit(EXIT_FAILURE);
//     }

//     if (showRes)
//         printf("     resolution: %10jd.%09ld\n", (intmax_t)ts.tv_sec,
//                ts.tv_nsec);
// }

// static int main2(int argc, char *argv[]) {
//     (void)argv;
//     bool showRes = argc > 1;

//     displayClock(CLOCK_REALTIME, "CLOCK_REALTIME", showRes);
// #ifdef CLOCK_TAI
//     displayClock(CLOCK_TAI, "CLOCK_TAI", showRes);
// #endif
//     displayClock(CLOCK_MONOTONIC, "CLOCK_MONOTONIC", showRes);
// #ifdef CLOCK_BOOTTIME
//     displayClock(CLOCK_BOOTTIME, "CLOCK_BOOTTIME", showRes);
// #endif
//     exit(EXIT_SUCCESS);
// }
typedef struct {
    int run_frames;
    int run;
    int pause;
    unsigned int frames;
    timespec t0;
    timespec last_time;
    timespec now;
} __timer_data_t;

static __timer_data_t __timer_data = {0};
static long int __frame_time_ns;

static void __get_time(timespec* ts) {
    if (clock_gettime(CLOCK_MONOTONIC, ts) == -1) {
        cls_print("[ERR]: clock_gettime()");
    }
}

// static unsigned int _count = 0;

static void __timer_loop() {
    while (__timer_data.run_frames) {
        ++__timer_data.frames;
        if (__timer_data.run) {
            if (__timer_data.pause) continue;
            __get_time(&__timer_data.now);
            const timespec diff =
                cls_timer_diff(__timer_data.last_time, __timer_data.now);
            // cls_print("Frame: %d, Diff: %10jd.%09ld\n", __timer_data.frames,
            // diff.tv_sec, diff.tv_nsec);
            if (diff.tv_nsec > __frame_time_ns) {
                __timer_data.last_time.tv_sec = __timer_data.now.tv_sec;
                __timer_data.last_time.tv_nsec = __timer_data.now.tv_nsec;
                // Dispatch timer events
                cls_events_trigger_event(CLS_EVT_TIMER);
                // ++_count;
                // cls_print("TEVENT: %d, Timer: %3jd.%10ld\n", _count,
                //           diff.tv_sec, diff.tv_nsec);
                // if (_count % 5 == 0) {
                //     const timespec diff2 =
                //         cls_timer_diff(__timer_data.t0, __timer_data.now);
                //     cls_print("Elapsed: F: %d, T: %2jd.%09ld\n", _count,
                //               diff2.tv_sec, diff2.tv_nsec);
                //     if (_count >= 5) {
                //         __timer_data.run_frames = 0;
                //     }
                // }
            }
        }
        //  Dispatch frame events
        cls_events_trigger_event(CLS_EVT_FRAME_ENTER);
    }
}

void cls_timer_static_init() {
    __get_time(&__timer_data.t0);
    cls_timer_set_fps(CLS_DESIRED_FPS);
}

void cls_timer_static_term() {}

void cls_timer_stop() {
    __timer_data.run_frames = 0;
    __timer_data.run = 0;
}

void cls_timer_run() {
    __timer_data.run_frames = 1;
    __timer_data.run = 1;
    __timer_loop();
}

void cls_timer_pause() { __timer_data.pause = 1; }

void cls_timer_resume() { __timer_data.pause = 0; }

void cls_timer_toggle() {
    if (__timer_data.pause > 0)
        __timer_data.pause = 0;
    else
        __timer_data.pause = 1;
}

timespec cls_timer_time() { return __timer_data.now; }

timespec cls_timer_diff(const timespec start, const timespec end) {
    timespec delta;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        delta.tv_sec = end.tv_sec - start.tv_sec - 1;
        delta.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        delta.tv_sec = end.tv_sec - start.tv_sec;
        delta.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return delta;
}

void cls_timer_set_fps(unsigned int fps) {
    double _time = 1000000000.0 / ((double)fps);
    __frame_time_ns = (long int)_time;
    cls_print("Frame time: %12.9f, %10ld\n", _time, __frame_time_ns);
}
