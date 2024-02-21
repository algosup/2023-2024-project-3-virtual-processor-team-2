/*
    This file is the virtual processor of the project
    It will read the binary file and run instructions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "vTerminal.h"


int main() {
    asm_error_t *errData = initErrorFile("errors.log", "test.log");

    runVTerminal(errData);
    exit(EXIT_SUCCESS);
}



