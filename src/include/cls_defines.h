/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __CLS_DEFINES_H
#define __CLS_DEFINES_H

#ifndef NULL
#define NULL ((void *)0)
#endif
#define NULL_STR '\0'

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/* Some compilers use a special export keyword */
#ifndef DECLSPEC
#if defined(__WIN32__) || defined(__WINRT__) || defined(__CYGWIN__)
#ifdef DLL_EXPORT
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC
#endif
#elif defined(__OS2__)
#ifdef BUILD_SDL
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC
#endif
#else
#if defined(__GNUC__) && __GNUC__ >= 4
#define DECLSPEC __attribute__((visibility("default")))
#else
#define DECLSPEC
#endif
#endif
#endif

/* By default CLASS uses the C calling convention */
#ifndef CLSCALL
#if (defined(__WIN32__) || defined(__WINRT__)) && !defined(__GNUC__)
#define SDLCALL __cdecl
#elif defined(__OS2__) || defined(__EMX__)
#define CLSCALL _System
#if defined(__GNUC__) && !defined(_System)
#define _System /* for old EMX/GCC compat.  */
#endif
#else
#define CLSCALL
#endif
#endif /* CLSCALL */

#define CLS_DEFAULT_STR_BUFF_SIZE 1024
#define CLS_EVENTS_COUNT_MAX \
    256    // Max number of events in the app (approx), should be greater than
           // or equal, try to be conservative with the estimate
#define CLS_EVENTS_CALLBACKS_PER_EVENT_COUNT 2
#define CLS_DESIRED_FPS 60
#define CLS_DATA_INSTANCES_ESTIMATE 256

#ifdef CLS_DEBUG
#undef HAVE_BUILTIN_TRAP
#ifdef __GNUC__
#define GCC_VERSION \
    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if GCC_VERSION > 40203
#define HAVE_BUILTIN_TRAP
#endif
#else
#ifdef __has_builtin
#if __has_builtin(__builtin_trap)
#define HAVE_BUILTIN_TRAP
#endif
#endif
#endif

#ifdef HAVE_BUILTIN_TRAP
#define CLS_CRASH_ME() __builtin_trap()
#else
#include <stdio.h>
#define CLS_CRASH_ME()          \
    do {                        \
        int *volatile iptr = 0; \
        int i = *iptr;          \
        printf("%d", i);        \
        abort();                \
    } while (0)
#endif
#else
#define CLS_CRASH_ME() \
    do {               \
    } while (0)
#endif
#endif    // __CLS_DEFINES_H