/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved

File: mrc_utils.c
*/
#include "mrc_utils.h"

static unsigned int __id = 0;
unsigned int mrc_util_get_unique_id() { return __id++; }