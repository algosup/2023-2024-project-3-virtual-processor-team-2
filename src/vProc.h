#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

// Struct of register's values
typedef struct {
    bool writable;
    uint16_t value;
} register_t;

typedef struct{
    unsigned int inst;
    unsigned int reg;
    unsigned int arg;
} instruction_t;


/*
    Initialize the cache
    params:
        None
*/
void initCache();

/*
    Set the speed of the clock based on ticks
    params:
        int time: Time passed when the application is running
        int lastTime: The last time that the clock have been updated
        int latentTicks:
*/
void setClock(int time, int lastTime, int latentTicks);


/*
    Convert a binary string to an instruction
    params:
        char *bin: the binary string
    returns:
        instruction_t: the instruction parsed
*/
instruction_t charBinToInst(char *bin);

/*
    Run an instruction
    params:
        instruction_t inst: the instruction to redirect to
        asm_error_t *errData: Error history
    returns:
        bool: if the instructions have been run
*/
bool run(instruction_t inst, asm_error_t *errData);

#ifdef __cplusplus
}
#endif