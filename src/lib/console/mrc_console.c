/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#include <stdio.h>
#include <stdarg.h>
#include "mrc_console.h"

int mrc_print(const char *format, ...) {
    int result;
    va_list args;
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);
    return result;
}