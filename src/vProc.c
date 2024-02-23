/*
    This file is part of VAT2.
    This file contains the implementation of the virtual processor.
*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "vProc.h"

#define LINE_MAX_BITS 16
#define VAR_LIST_SIZE 256
#define MAX_CALL_STACK 256
#define CLOCK_TICKS 1/20

// variables
vProcVar_t vProcVars[VAR_LIST_SIZE];

int lastVarIdx = 0;

fpos_t cursorPos[MAX_CALL_STACK];
int callStackSize = 0;

// registers
vRegister_t rg0 = {true, 0};
vRegister_t rg1 = {true, 0};
vRegister_t rg2 = {true, 0};
vRegister_t rg3 = {false, 0};
vRegister_t rg4 = {true, 0};
vRegister_t rg5 = {true, 0};
vRegister_t rg6 = {true, 0};
vRegister_t rg7 = {true, 0};

bool readFile(char *filename, asm_error_t *errData){
    //Check if the file is present
        FILE *file = fopen(filename, "rb");
        if(file == NULL){
            errorfnf(filename, errData);
        }
        // Run program
        char line[LINE_MAX_BITS];
        
        // Set as carry for action on next instruction
        carry_t carry = {0, false};

        int time = 0;
        int lastTime = 0;
        int latentTicks = 0;
        while(fgets(line, LINE_MAX_BITS + 1, file)) {
            setClock(time, lastTime, latentTicks);
            instruction_t inst = charBinToInst(line);
            if(!run(inst, &carry, file, filename, errData)){
                fclose(file);
                return false;
            }
        }
        fclose(file);
        return true;
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
    unsigned int instMask = 31; // 0b11111
    unsigned int regMask = 7; // 0b111
    unsigned int argMask = 255; // 0b0000000011111111

    // Extract each field using bitwise AND and shift operations
    instruction.inst = (inst >> 11) & instMask;
    instruction.reg = (inst >> 8) & regMask;
    instruction.arg = inst & argMask;

    return instruction;
}

bool run(instruction_t inst, carry_t *carry, FILE *file, char *filename, asm_error_t *errData){
    vRegister_t *reg;
    fpos_t pos;
    // check if there is a carry
    if(carry->isUsed && inst.inst != 24){
        inst.arg = carry->nextArg;
        carry->isUsed = false;
    }
    switch(inst.inst){
        case 0: //mov
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            reg->value = inst.arg;
            return true;
        case 1: //goto
            pos = searchLabel(inst.arg, filename, errData);
            if(pos == -1){
                return false;
            }
            // goto label
            fsetpos(file, &pos);
            return true;
        case 2: //call
            // get call position
            fgetpos(file, &pos);
            if(!addCallPos(pos)){
                return false;
            }
            // search label
            pos = searchLabel(inst.arg, filename, errData);
            if(pos == -1){
                return false;
            }
            // goto label
            fsetpos(file, &pos);
            return true;
        case 3: //int
            return runInt(inst, carry, errData);
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
            return opNot(reg, errData);
        case 16: //use reg
            return true;
        case 17: //var
            return true;
        case 18: //label
            return true;
        case 19: //var
            if(lastVarIdx >= VAR_LIST_SIZE){
                errorOverflow(errData);
                return false;
            }
            // set var
            vProcVars[inst.arg].data = NULL;
            lastVarIdx = inst.arg; 
            return true;
        case 21: //mod
            reg = getRegister(inst.reg);
            if(reg == NULL){
                return false;
            }
            return opMod(reg, inst.arg, errData);
        case 22: //ret
            // get call next position
            pos = cursorPos[0];
            if(!removeCallPos()){
                return false;
            }
            // go to new position
            fsetpos(file, &pos);
            return true;
        case 23: //mov from var
            // set carry to var data
            if(vProcVars[inst.arg].size > 1){
                carry->nextArg = vProcVars[inst.arg].data[1];
                carry->nextArg <<= 8;
                carry->nextArg |= vProcVars[inst.arg].data[0];
            }
            else{
                carry->nextArg = vProcVars[inst.arg].data[0];
            }
            carry->isUsed = true;
            return true;
        case 24: //mov to var
            // set datas to 0
            if(vProcVars[inst.arg].data == NULL){
                vProcVars[inst.arg].data = malloc(sizeof(int)*inst.arg);
                for(unsigned int i = 0; i < inst.arg; i++){
                    vProcVars[inst.arg].data[i] = 0;
                }
            }
            // mov arg to target var
            if(vProcVars[inst.arg].size > 1){
                vProcVars[inst.arg].data[1] = carry->nextArg >> 8;
                vProcVars[inst.arg].data[0] = carry->nextArg;
                // reset size
                vProcVars[inst.arg].size = 2;
            }
            else{
                vProcVars[inst.arg].data[0] = carry->nextArg;
            }
            // disable carry
            carry->isUsed = false;
            return true;
        case 25: //var size
            vProcVars[lastVarIdx].size = inst.arg;
            vProcVars[lastVarIdx].data = malloc(sizeof(int)*inst.arg);
            // set all data to 0
            for(unsigned int i = 0; i < inst.arg; i++){
                vProcVars[lastVarIdx].data[i] = 0;
            }
            return true;
        case 26: //var data
            // add data to var at fist free position
            for(int i = 0; i < vProcVars[lastVarIdx].size; i++){
                if(vProcVars[lastVarIdx].data[i] == 0){
                    vProcVars[lastVarIdx].data[i] = inst.arg;
                    return true;
                }
            }
            errorOverflow(errData);
            return false;
        default:
            exit(EXIT_FAILURE);
    }
}

bool runInt(instruction_t inst, carry_t *carry, asm_error_t *errData){
    switch(inst.arg){
        case 0: //nigeru
            return false;
        case 1: // draw
            // print reg 0
            printf("%d\n", rg0.value);
            return true;
        case 2: // ob1
            return true;
        case 3: // cmp or
            return true;
        case 4: // cmp and
            return true;
        case 5: // cmp xor
            return true;
        case 6: // cmp less than
            return true;
        case 7: // cmp less than or equal
            return true;
        case 8: // cmp greater than
            return true;
        case 9: // cmp greater than or equal
            return true;
        case 10: // cmp equal
            return true;
        case 11: // cmp not equal
            return true;
        case 12: // pusha
            return true;
        case 13: // popa
            return true;
        case 14: // mov from reg
            // set carry
            carry->nextArg = getRegister(inst.reg)->value;
            carry->isUsed = true;
            return true;
        case 15: // else
            return true;
        case 16: // end
            return true;
        default:
            exit(EXIT_FAILURE);
    }
}

vRegister_t *getRegister(int reg){
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

fpos_t searchLabel(int labId, char *filename, asm_error_t *errData){
    FILE *file = fopen(filename, "rb");
    if(file == NULL){
        errorfnf(filename, errData);
        return 0;
    }
    char line[LINE_MAX_BITS];
    fpos_t pos;
    while(fgets(line, LINE_MAX_BITS + 1, file)) {
        if(line[0] == '1'){
            int inst = (int)strtoul(line, NULL, 2);
            unsigned int instMask = 31; // 0b11111
            unsigned int argMask = 255; // 0b0000000011111111
            
            int instId = (inst >> 11) & instMask;
            int arg = inst & argMask;

            if(instId == 18 && arg == labId){
                fgetpos(file, &pos);
                fclose(file);
                return pos;
            }
        }
    }
    fclose(file);
    return -1;
}


bool opAdd(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value += arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opSub(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value -= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opDiv(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value /= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opMul(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value *= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opMod(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value %= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opXor(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value ^= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opAnd(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value &= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opOr(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value |= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opNot(vRegister_t *reg, asm_error_t *errData){
    if(reg->writable){
        reg->value = ~reg->value;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opShl(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value <<= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool opShr(vRegister_t *reg, unsigned int arg, asm_error_t *errData){
    if(reg->writable){
        reg->value >>= arg;
        return true;
    }
    else{
        errorReadOnly(errData);
        return false;
    }
}

bool addCallPos(fpos_t pos) {
    if (callStackSize >= MAX_CALL_STACK) {
        fprintf(stderr, "Call stack overflow\n");
        return false;
    }

    for (int i = callStackSize; i > 0; i--) {
        cursorPos[i] = cursorPos[i - 1];
    }

    cursorPos[0] = pos;
    ++callStackSize;
    return true;
}

bool removeCallPos() {
    if (callStackSize == 0) {
        fprintf(stderr, "Call stack is empty\n");
        return false;
    }

    for (int i = 0; i < callStackSize - 1; i++) {
        cursorPos[i] = cursorPos[i + 1];
    }

    --callStackSize;
    return true;
}

void printVar(int idx){
    printf("Var %d: ", idx);
    for(int i = 0; i < vProcVars[idx].size; i++){
        printf("%d ", vProcVars[idx].data[i]);
    }
    printf("\n");
}