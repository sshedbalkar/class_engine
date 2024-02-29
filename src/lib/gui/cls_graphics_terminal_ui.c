/*
Copyright (c) Santosh Shedbalkar
Year: 2024 -
All rights reserved
*/
#include "cls_graphics.h"
#include "cls_graphics_terminal_ui_p.h"
#include "cls_ui_terminal_ui_p.h"
#include "cls_console.h"

static int parse_opt(int key, char* arg, struct argp_state* state) {
    (void)arg;
    (void)state;
    switch (key) {
        case 800:
            cls_print("cls_graphics option: 800");
            break;
        case 801:
            cls_print("cls_graphics option: 801");
            break;
    }
    return 0;
}

static struct argp_option options[] = {
    {"gra1", 800, "NUM", OPTION_ARG_OPTIONAL, "Interact with Graphics module"},
    {"gra2", 801, "NUM", OPTION_ARG_OPTIONAL, "Graphics module option 7"},
    {0}};

static struct argp_child children_parsers[] = {
    {&ui_argp, 0, "Basic UI options:", 3}, {0}};

struct argp graphics_argp = {
    options, parse_opt, 0,
    "Interact with the Graphics module of the Merci Engine.\v"
    "Graphics module is still a WIP.",
    children_parsers};