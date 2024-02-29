/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_data_container.h
 */

#ifndef __CLS_DATA_CONTAINER_H
#define __CLS_DATA_CONTAINER_H

extern void cls_data_container_static_init();
extern void cls_data_container_static_term();
extern unsigned int cls_data_container_add(void* _pdata);
extern int cls_data_container_remove(unsigned int _index);
extern void* cls_data_container_get(unsigned int _index);

#endif    // __CLS_DATA_CONTAINER_H