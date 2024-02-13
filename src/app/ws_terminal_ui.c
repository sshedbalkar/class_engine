/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: ws_terminal_ui.c
 */

#include <argp.h>
#include "ws_main.h"
#include "ws_terminal_ui.h"
#include "mrc_engine_terminal_ui.h"
#include "mrc_console.h"

const char *argp_program_bug_address = PROGRAM_BUG_EMAIL_CONTACT;
const char *argp_program_version = APP_VERSION;

static int parse_opt(int key, char *arg, struct argp_state *state) {
    // ws_app_t *app = state->input;
    //  int total = mrc_vector_total(&app->engine->modules);
    //  mrc_print("WS Current modules in the engine: %d\n", total);
    switch (key) {
        case 700:
            mrc_print("WordScape Option: 700");
            break;
        case 701:
            mrc_print("WordScape option: 701");
            break;
    }
    return 0;
}

static struct argp_option options[] = {
    {"ws1", 700, "NUM", OPTION_ARG_OPTIONAL, "Interact with WordScape game"},
    {"ws2", 701, "NUM", OPTION_ARG_OPTIONAL, "WordScape option 2"},
    {0}};

static struct argp_child children_parsers[] = {
    {&engine_argp, 0, "Basic Merci Engine options:", 5}, {0}};

static struct argp ws_argp = {
    options, parse_opt, 0,
    "Interact with the Engine module of the WordScape game.\v"
    "WordScape is still a WIP.",
    children_parsers};

int ws_parse_args(int argc, char **argv, ws_app_t *app) {
    return argp_parse(&ws_argp, argc, argv, 0, 0, app->engine);
}
