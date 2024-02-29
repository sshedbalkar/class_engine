/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/

#ifndef __CLS_CONSOLE_H
#define __CLS_CONSOLE_H

#include "cls_types.h"
#include "cls_defines.h"

struct JsonNode;
typedef struct JsonNode JsonNode;

typedef struct {
    // Has to be the first property
    cls_obj_static_t* base;
} cls_console_t;

extern DECLSPEC int CLSCALL cls_print(const char* format, ...);

extern cls_obj_static_t* cls_console_static_init();

extern int cls_console_static_term();

extern cls_console_t* cls_console_ctor();

extern int cls_console_dtor(cls_console_t* obj);

extern JsonNode* cls_console_serz(cls_console_t* _obj);
extern void cls_console_dsrz(cls_console_t* _obj, JsonNode* _json);

#endif    //__CLS_CONSOLE_H
