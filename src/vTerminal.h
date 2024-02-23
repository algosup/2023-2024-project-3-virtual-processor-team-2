#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "error.h"
#include "vProc.h"

#ifdef __cplusplus
extern "C" {
#endif


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

#ifdef __cplusplus
}
#endif
