/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#include "mrc_ui.h"
#include "mrc_ui_terminal_ui_p.h"
#include "mrc_console.h"

static int parse_opt(int key, char* arg, struct argp_state* state) {
    switch (key) {
        case 900:
            mrc_print("mrc_ui option: 900");
            break;
        case 901:
            mrc_print("mrc_ui option: 901");
            break;
    }
    return 0;
}

static struct argp_option options[] = {
    {"ui", 900, "NUM", OPTION_ARG_OPTIONAL, "Interact with the UI module"},
    {"ui2", 901, "NUM", OPTION_ARG_OPTIONAL, "UI Module option 6"},
    {0}};

struct argp ui_argp = {options, parse_opt, 0,
                       "Interact with the UI module of the Merci Engine.\v"
                       "UI module is still a WIP.",
                       0};
