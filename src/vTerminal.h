#pragma once

#include <stdbool.h>

#include "error.h"

/*
    Run a virtual terminal
    params:
        errData: Error history
*/
void runVTerminal(asm_error_t *errData);

/*
    Run a command
    params:
        char *cmd: the command to run
        asm_error_t *errData: Error history
    return:
        bool: if the command have been executed
*/
bool runCmd(char *cmd, asm_error_t *errData);