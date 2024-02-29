/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: cls_engine_terminal_ui.c
 */

#include <argp.h>
#include "cls_engine_main.h"
#include "cls_engine_terminal_ui.h"
#include "cls_graphics_terminal_ui_p.h"
#include "cls_console.h"
#include "cls_engine_utils.h"

static int parse_opt(int key, char* arg, struct argp_state* state) {
    cls_engine_t* eng = state->input;
    (void)arg;
    switch (key) {
        case 'e':
            cls_print("Current modules in the engine: %d\n",
                      cls_vector_total(&eng->submodules));
            cls_print("%s", cls_engine_get_modules_names(eng));
            cls_print("\n");
            break;
        case 501:
            cls_print("class_engine option: 501");
            break;
    }
    return 0;
}

static struct argp_option options[] = {
    {"mrc1", 'e', "NUM", OPTION_ARG_OPTIONAL, "Interact with Merci Engine"},
    {"mrc2", 501, 0, OPTION_HIDDEN, "Engine module option 2"},
    {0}};

static struct argp_child children_parsers[] = {
    {&graphics_argp, 0, "Basic Graphics options:", 4}, {0}};

struct argp engine_argp = {
    options, parse_opt, 0,
    "Interact with the Engine module of the Merci Engine.\v"
    "Merci Engine is still a WIP.",
    children_parsers};