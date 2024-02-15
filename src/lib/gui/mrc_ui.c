/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#include "mrc_console.h"
#include "mrc_ui.h"
#include "mrc_memory.h"

static mrc_obj_static_t __base = {MRC_GRAPHICS_UI, (mrc_fn_vp_v_t)&mrc_ui_ctor,
                                  (mrc_fn_i_vp_t)&mrc_ui_dtor};

void mrc_ui_init(mrc_ui_t* obj) {
    (void)obj;
    mrc_print("mrc_ui_init");
}
void mrc_ui_test1(mrc_ui_t* obj) {
    (void)obj;
    mrc_print("mrc_ui_test1");
}

mrc_obj_static_t* mrc_ui_static_init() { return &__base; }

static mrc_ui_t* __create() { return (mrc_ui_t*)mrc_alloc(sizeof(mrc_ui_t)); }

mrc_ui_t* mrc_ui_ctor() {
    mrc_ui_t* obj = __create();
    obj->base = &__base;
    return obj;
}

int mrc_ui_dtor(mrc_ui_t* obj) {
    mrc_free(obj);
    return 0;
}