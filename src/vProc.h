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

// Struct of instruction's values
typedef struct{
    unsigned int inst;
    unsigned int reg;
    unsigned int arg;
} instruction_t;

// Struct of carry's values
typedef struct{
    unsigned int nextArg;
    bool isUsed;
} carry_t;

// Struct of variable's values
typedef struct {
    int size;
    int *data;
} vProcVar_t;


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
        carry_t *carry: Carry for action on next instruction
        asm_error_t *errData: Error history
    returns:
        bool: if the instructions have been run
*/
bool run(instruction_t inst, carry_t *carry, asm_error_t *errData);

/*
    Run interrupt operation
    params:
        instruction_t inst: the instruction to redirect to
        carry_t *carry: Carry for action on next instruction
        asm_error_t *errData: Error history
    returns:
        bool: if the instructions have been run
*/
bool runInt(instruction_t inst, carry_t *carry, asm_error_t *errData);

/*
    Get a register
    params:
        int reg: the register to get
    returns:
        register_t *: the register
*/
register_t *getRegister(int reg);

/*
    Add a value to a register
    params:
        register_t *reg: the register to add the value to
        unsigned int arg: the value to add
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been added
*/
bool opAdd(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    Subtract a value to a register
    params:
        register_t *reg: the register to subtract the value to
        unsigned int arg: the value to subtract
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been subtracted
*/
bool opSub(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    Divide a value to a register
    params:
        register_t *reg: the register to divide the value to
        unsigned int arg: the value to divide
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been divided
*/
bool opDiv(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    Multiply a value to a register
    params:
        register_t *reg: the register to multiply the value to
        unsigned int arg: the value to multiply
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been multiplied
*/
bool opMul(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    Modulo a value to a register
    params:
        register_t *reg: the register to modulo the value to
        unsigned int arg: the value to modulo
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been moduloed
*/
bool opMod(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    XOR a value to a register
    params:
        register_t *reg: the register to XOR the value to
        unsigned int arg: the value to XOR
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been XORed
*/
bool opXor(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    AND a value to a register
    params:
        register_t *reg: the register to AND the value to
        unsigned int arg: the value to AND
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been ANDed
*/
bool opAnd(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    OR a value to a register
    params:
        register_t *reg: the register to OR the value to
        unsigned int arg: the value to OR
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been ORed
*/
bool opOr(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    NOT a value to a register
    params:
        register_t *reg: the register to NOT the value to
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been NOTed
*/
bool opNot(register_t *reg, asm_error_t *errData);

/*
    Shift left a value to a register
    params:
        register_t *reg: the register to shift left the value to
        unsigned int arg: the value to shift left
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been shifted left
*/
bool opShl(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    Shift right a value to a register
    params:
        register_t *reg: the register to shift right the value to
        unsigned int arg: the value to shift right
        asm_error_t *errData: Error history
    returns:
        bool: if the value have been shifted right
*/
bool opShr(register_t *reg, unsigned int arg, asm_error_t *errData);

/*
    print a variable data
    params:
        int idx: the index of the variable
*/
void printVar(int idx);

#ifdef __cplusplus
}
#endif