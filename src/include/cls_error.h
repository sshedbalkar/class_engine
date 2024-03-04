/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_error.h
 */
#ifndef __CLS_ERROR_H
#define __CLS_ERROR_H

typedef enum {
    CLS_ERROR_RECOVERABLE = 0,
    CLS_ERROR_FATAL,
    //
    CLS_ERROR_COUNT
} cls_error_type_t;

typedef struct {
    unsigned int id;
    unsigned int type;
    const char* message;
} cls_error_t;

extern cls_error_t* cls_error_get_last();
extern void cls_error_set(unsigned int _id, cls_error_type_t _type,
                          const char* _msg);
extern void cls_error_clear();
extern const char* cls_error_serialized();
extern const char* cls_error_type_to_string(cls_error_type_t _type);

#endif    // __CLS_ERROR_H