/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_data_container.h
 */

#ifndef __MRC_DATA_CONTAINER_H
#define __MRC_DATA_CONTAINER_H

extern void mrc_data_container_static_init();
extern void mrc_data_container_static_term();
extern unsigned int mrc_data_container_add(void* _pdata);
extern int mrc_data_container_remove(unsigned int _index);
extern void* mrc_data_container_get(unsigned int _index);

#endif    // __MRC_DATA_CONTAINER_H