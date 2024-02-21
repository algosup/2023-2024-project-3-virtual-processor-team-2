/*
    This file is part of VAT2.
    This file contains the implementation of the virtual processor.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "vProc.h"
#include "vMem.h"

#define LINE_MAX_BITS 16

#define CACHE_SIZE 504
#define CACHE_BLOCK_SIZE 8
#define CACHE_DEFAULT_VALUE "00000000"

#define CLOCK_TICKS 1/20

// registers
register_t rg0 = {true, 0};
register_t rg1 = {true, 0};
register_t rg2 = {true, 0};
register_t rg3 = {false, 0};
register_t rg4 = {true, 0};
register_t rg5 = {true, 0};
register_t rg6 = {true, 0};
register_t rg7 = {true, 0};

char cache[CACHE_SIZE][CACHE_BLOCK_SIZE];

void initCache(){
    // Cache memory
    for(int i=0; i<CACHE_SIZE; i++){
        strcpy(cache[i], CACHE_DEFAULT_VALUE);
    }
}

void setClock(int time, int lastTime, int latentTicks){
    sleep(CLOCK_TICKS);
        ++latentTicks;
        if(latentTicks >= 20) {
            latentTicks = latentTicks - 20;
            time += 1;
        }

        rg3.value += 1;
        if(lastTime != time) {
            lastTime = time;
        }
}

instruction_t charBinToInst(char *bin){
    int inst = (int)strtoul(bin, NULL, 2);
    instruction_t instruction = {0, 0, 0};

    // Define masks for each field
    unsigned int instMask = 0b11111;
    unsigned int regMask = 0b111;
    unsigned int argMask = 0b0000000011111111;

    // Extract each field using bitwise AND and shift operations
    instruction.inst = (inst >> 11) & instMask;
    instruction.reg = (inst >> 8) & regMask;
    instruction.arg = inst & argMask;

    return instruction;
}

bool run(instruction_t inst, asm_error_t *errData){
    register_t *reg;
    switch(inst.inst){
        case 0: //mov
            return true;
        case 1: //goto
            return true;
        case 2: //call
            return true;
        case 3: //int
            return true;
        case 4: //push
            return true;
        case 5: //xor
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opXor(reg, inst.arg, errData);
        case 6: //pop
            return true;
        case 7: //div
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opDiv(reg, inst.arg, errData);
        case 8: //add
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opAdd(reg, inst.arg, errData);
        case 9: //sub
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opSub(reg, inst.arg, errData);
        case 10: //mul
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opMul(reg, inst.arg, errData);
        case 11: //right shift
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opShr(reg, inst.arg, errData);
        case 12: //left shift
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opShl(reg, inst.arg, errData);
        case 13: //and
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opAnd(reg, inst.arg, errData);
        case 14: //or
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opOr(reg, inst.arg, errData);
        case 15: //not
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opNot(reg, inst.arg, errData);
        case 16: //use reg
            return true;
        case 17: //var
            return true;
        case 18: //label
            return true;
        case 19: //var
            return true;
        case 21: //mod
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opMod(reg, inst.arg, errData);
        case 22: //ret
            return true;
        case 23: //mov from var
            return true;
        case 24: //mov to var
            return true;
        case 25: //var size
            return true;
        case 26: //var data
            return true;
        default:
            errorInstruction("Unknown instruction", 0, errData);
            return false;
    }
}

register_t *getRegister(int reg){
    switch(reg){
        case 0:
            return &rg0;
        case 1:
            return &rg1;
        case 2:
            return &rg2;
        case 3:
            return &rg3;
        case 4:
            return &rg4;
        case 5:
            return &rg5;
        case 6:
            return &rg6;
        case 7:
            return &rg7;
        default:
            return NULL;
    }
}

bool opAdd(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value += arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opSub(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value -= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opDiv(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value /= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opMul(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value *= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opMod(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value %= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opXor(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value ^= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opAnd(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value &= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opOr(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value |= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opNot(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value = ~reg->value;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opShl(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value <<= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opShr(register_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value >>= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}