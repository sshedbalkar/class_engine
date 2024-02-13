/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_engine_terminal_ui.c
 */

#include <argp.h>
#include "mrc_engine_main.h"
#include "mrc_engine_terminal_ui.h"
#include "mrc_graphics_terminal_ui_p.h"
#include "mrc_console.h"

static int parse_opt(int key, char* arg, struct argp_state* state) {
    mrc_engine_t* eng = state->input;
    switch (key) {
        case 'e':
            int i, total = mrc_vector_total(&eng->modules);
            mrc_print("Current modules in the engine: %d\n", total);
            for (i = 0; i < total; ++i) {
                mrc_print(
                    "%s, ",
                    mrc_module_type_t_to_string(
                        ((mrc_obj_static_t*)mrc_vector_get(&eng->modules, i))
                            ->type));
            }
            break;
        case 501:
            mrc_print("merci_engine option: 501");
            break;
    }
    return 0;
}

static struct argp_option options[] = {
    {"mrc1", 'e', "NUM", OPTION_ARG_OPTIONAL, "Interact with Merci Engine"},
    {"mrc2", 501, 0, OPTION_HIDDEN, "Engine module option 2"},
    {0}};

static struct argp_child children_parsers[] = {
    {&graphics_argp, 0, "Basic Graphics options:", 5}, {0}};

struct argp engine_argp = {
    options, parse_opt, 0,
    "Interact with the Engine module of the Merci Engine.\v"
    "Merci Engine is still a WIP.",
    children_parsers};