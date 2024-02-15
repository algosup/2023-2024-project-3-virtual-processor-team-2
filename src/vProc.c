/*
    This file is the virtual processor of the project
    It will read the binary file and run instructions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <Windows.h> // we need to check what system is before implementing 
#include "vProc.h"

#define LINE_MAX_BITS 16
#define MAX_STACK_SIZE 2016 // LIFO Storage
#define MAX_PROCESSING_SIZE 2016 
#define MAX_MEMORY_SIZE 8320
#define MAX_GRAPHIC_MEMORY_SIZE 4032

register_t rg0 = {true, 0};
register_t rg1 = {true, 0};
register_t rg2 = {true, 0};
register_t rg3 = {false, 0};
register_t rg4 = {true, 0};
register_t rg5 = {true, 0};
register_t rg6 = {true, 0};
register_t rg7 = {true, 0};


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: Invalid parameter, Usage: %s <binary file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE* file = readBinaryFile(argv[1]);

    char line[LINE_MAX_BITS];
    char operand[6];
    char reg[4];
    char data[9];
    uint16_t currentLine = 1;


    MMU_t stack;
    MMU_t processing;
    MMU_t memory;
    MMU_t graphic;
    cache_t cache;
    virtualProcessor_t virtualProcessor;

    stack.maxSize = MAX_STACK_SIZE;             // Max size of block of stack region
    processing.maxSize = MAX_PROCESSING_SIZE;   // Max size of block of progessing region
    memory.maxSize = MAX_MEMORY_SIZE;           // Max size of block of memory region
    graphic.maxSize = MAX_GRAPHIC_MEMORY_SIZE;  // Max size of block of graphic region
    virtualProcessor.maxSize = (stack.maxSize + processing.maxSize + memory.maxSize + graphic.maxSize);
    virtualProcessor.cache = cache;

    printf("%d kb Available\n", virtualProcessor.maxSize); // Just to avoid useless warning

    int time = 0;
    int lastTime = 0;
    int latentTicks = 0;
    while(fgets(line, sizeof(line) + 1, file)) {
        
        setClock(time, lastTime, latentTicks);

        readBinaryInstruction(&cache, line, operand, reg, data, currentLine, processing);
           
        
    }
    fclose(file);
    exit(EXIT_SUCCESS);
}

FILE* readBinaryFile(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL){
        fprintf(stderr, "Error reading file\n");
        exit(EXIT_FAILURE);
    } else {
        printf("file %s found\n", filename);
    }
    return file;
}

void setClock(int time, int lastTime, int latentTicks){
    Sleep(1000/20); // syntax of sleep depend of the system
        ++latentTicks;
        if(latentTicks >= 20) {
            latentTicks = latentTicks - 20;
            time += 1;
        }

        rg3.value += 1;
        if(lastTime != time) {
            lastTime = time;
            printf("Time: %ds\n", time);
        }
}

void printBinary(uint16_t value) {
    for (int i = 15; i >= 0; --i) {
        putchar((value & (1 << i)) ? '1' : '0');
    }
    putchar('\n');
}


int* parserBinaryFile(char *line, char *operand, char *reg, char *data, uint8_t currentLine){
    
    if(strlen(line) >= LINE_MAX_BITS-2) {
        // Copy the characters 0 or 1 depending the lenght
        memcpy(operand, line, 5);
        memcpy(reg, line + 5, 3);
        memcpy(data, line + 8, 8);
        operand[5] = '\0';
        reg[3] = '\0';
        data[8] = '\0';

        // Store the values copied in int 
        int binOperand = (int)strtol(operand, NULL, 2);
        int binReg = (int)strtol(reg, NULL, 2);
        int binData = (int)strtol(data, NULL, 2);

        //
        static int lineRead[3];
        lineRead[0] = binOperand;
        lineRead[1] = binReg;
        lineRead[2] = binData;

        ++currentLine; 
        // Return array with 3 values
        return lineRead;
    } 
    else {
        fprintf(stderr, "ERROR: Invalid line size, line: %u\n", currentLine);
        exit(EXIT_FAILURE);
    }
     
}


void readBinaryInstruction(cache_t *cache, char *line, char *operand, char *reg, char *data, uint8_t currentLine, MMU_t processing){
    
    int *lineRead = parserBinaryFile(line, operand, reg, data, currentLine);
    printf("%d\n", lineRead[0]);
    printf("%d\n", lineRead[1]);
    printf("%d\n", lineRead[2]);

    attributeOperand(lineRead, &processing);
    attributeRegister(lineRead);
}

void attributeOperand(int *arg, MMU_t *processing){
    
    switch (arg[0]){
    // Define the opCode read in binary
        case 00000:
            opCodeMov(&processing, arg);
            break;
        case 00001:
            opCodeGoto(arg);
            break;
        case 00010:
            opCodeCall(arg);
            break;
        case 00011:
            opCodeInt(arg);
            break;
        case 00100:
            opCodePush(arg);
            break;
        case 00101:
            opCodeXor(arg);
            break;
        case 00110:
            opCodePop(arg);
            break;
        case 00111:
            opCodeDiv(arg);
            break;
        case 01000:
            opCodeAdd(arg);
            break;
        case 01001:
            opCodeSub(arg);
            break;
        case 01010:
            opCodeMul(arg);
            break;
        case 01011:
            opCodeRsh(arg);
            break;
        case 01100:
            opCodeLsh(arg);
            break;
        case 01101:
            opCodeAnd(arg);
            break;
        case 01110:
            opCodeOr(arg);
            break;
        case 01111:
            opCodeNot(arg);
            break;
        case 10000:
            opCodeUseReg(arg);
            break;
        case 10001:
            opCodeUseVar(arg);
            break;
        case 10010:
            opCodeLab(arg);
            break;
        case 10011:
            opCodeVar(arg);
            break;
        case 10100:
            opCodeNeg(arg);
            break;
        case 10101:
            opCodeMod(arg);
            break;
        case 10110:
            opCodeRet(arg);
            break;
        case 10111:
            opCodeMovFromVar(arg);
            break;
        case 11000:
            opCodeMovToVar(arg);
            break;
        case 11001:
            opCodeVarSize(arg);
            break;
        case 11010:
            opCodeVarData(arg);
            break;
        // case 11011:
            
        //     break;
        // case 11100:
            
        //     break;
        // case 11101:
            
        //     break;
        // case 11110:
            
        //     break;
        // case 11111:
            
        //     break;
        default:
            break;
    }
}

void attributeRegister(int *arg){
    
    switch (arg[1]){
    // Define the register read in binary
        case 000:
            rg0;
            break;
        case 001:
            rg1;
            break;
        case 010:
            rg2;
            break;
        case 011:
            rg3;
            break;
        case 100:
            rg4;
            break;
        case 101:
            rg5;
            break;
        case 110:
            rg6;
            break;
        case 111:
            rg7;
            break;
    }
}

void opCodeMov(MMU_t *processing, int *arg){
    if(arg[1] == rgX){
        rgX.value = arg[2];
    } else {
        var.id = arg[2];
    }
}
void opCodeGoto(int *arg){}

// start:                         ins   reg   value
//     mov rg0, 5              -> 00000 000 0000 0101 00000 000 0000 0101 
//     mov rg1, rg0            -> 00000 010 0000 0101
//     + rg1, 10               -> 01000 010 0000 1010
//     - rg1, 3                -> 01001 011 0000 0011
//     mov rg2, 2              -> 00000 100 0000 0010
//     * rg1, rg2              -> 01010 010 0000 0010
//     > rg1, 50   || int 8 || -> 00011 000 0001 1000
//     goto greater_than       -> 00001-
//     < rg1, 50   || int 6 || -> 00011 000 0001 0110
//     goto less_than
//     == rg1, 50  || int 10 ||-> 00011 000 0001 1010
//     goto equal_to

// greater_than:
//     ; Code for greater than
//     ; You can replace this with your desired code
//     jmp exit_program

// less_than:
//     ; Code for less than
//     ; You can replace this with your desired code
//     jmp exit_program

// equal_to:
//     ; Code for equal to
//     ; You can replace this with your desired code
//     jmp exit_program

// exit_program:
//     mov ax, 0x4C00  ; Exit code
//     int 0x21        ; DOS syscall for exit

