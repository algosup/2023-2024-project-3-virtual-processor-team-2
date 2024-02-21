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
#include "vat2.h"

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

    virtualProcessor_t virtualProcessor;

    int time = 0;
    int lastTime = 0;
    int latentTicks = 0;
    while(fgets(line, sizeof(line) + 1, file)) {
        setClock(time, lastTime, latentTicks);
        readBinaryInstruction(line, operand, reg, data, currentLine);
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


void readBinaryInstruction(char *line, char *operand, char *reg, char *data, uint8_t currentLine){
    
    int *lineRead = parserBinaryFile(line, operand, reg, data, currentLine);
    attributeOperand(lineRead);
}

void attributeOperand(int *arg){
    
    switch (arg[0]){
    // Define the opCode read in binary
        case 00000:
            opCodeMov(arg);
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

register_t attributeRegister(int *arg){
    
    switch (arg[1]){
    // Define the register read in binary
        case 000:
            return rg0;
            break;
        case 001:
            return rg1;
            break;
        case 010:
            return rg2;
            break;
        case 011:
            return rg3;
            break;
        case 100:
            return rg4;
            break;
        case 101:
            return rg5;
            break;
        case 110:
            return rg6;
            break;
        case 111:
            return rg7;
            break;
    }
}


void opCodeMov(int *arg){
    switch (false) {
    case true:
        break;
    case false:
        register_t tmp = attributeRegister(arg);
        tmp.value = arg[2];
        break;
    default:
    }
}

void opCodeGoto(int *arg){}                                    
void opCodeCall(int *arg){}   

// Attribute the specific interaction depending the last 8bits 
void opCodeInt(int *arg){
    int tmp = arg[2];
    switch(tmp) {
        case 00000000:
            intNgr();
            break;
        case 00000001:
            intDraw(arg);
            break;
        case 00000010:
            intOb1(arg);
            break;
        case 00000011:
            intIfOr(arg);
            break;
        case 00000100:
            intIfAnd(arg);
            break;
        case 00000101:
            intIfXor(arg);
            break;
        case 00000110:
            intIfLt(arg);
            break;
        case 00000111:
            intIfLte(arg);
            break;
        case 00001000:
            intIfGt(arg);
            break;
        case 00001001:
            intIfGte(arg);
            break;
        case 00001010:
            intIfEq(arg);
            break;
        case 00001011:
            intIfNeq(arg);
            break;
        case 00001100:
            intPusha(arg);
            break;
        case 00001101:
            intPopa(arg);
            break;
        case 00001110:
            intMovFReg(arg);
            break;
        case 00001111:
            intElse(arg);
            break;
        case 00010000:
            intEnd(arg);
            break;
        default: // Default don't find the second arg 
            exit(EXIT_FAILURE);
            break;
    }
}        
                  
void opCodePush(int *arg){}     

void opCodeXor(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value = tmp.value ^ arg[2];
}       

void opCodePop(int *arg){}  

void opCodeDiv(int *arg){
    register_t tmp = attributeRegister(arg);
    uint16_t value = tmp.value;
    tmp.value = value / arg[2];
}   

void opCodeAdd(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value += arg[2];
}             

void opCodeSub(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value -= arg[2];
}   

void opCodeMul(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value *= arg[2];
}                          

void opCodeRsh(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value = tmp.value >> arg[2];
}        

void opCodeLsh(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value = tmp.value << arg[2];
}                   

void opCodeAnd(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value = tmp.value & arg[2];
} 
                        
void opCodeOr(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value = tmp.value | arg[2];
}      

void opCodeNot(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value = ~tmp.value;
}
                          
void opCodeUseReg(int *arg){}                       
void opCodeUseVar(int *arg){}                       

void opCodeLab(int *arg){
    //get lab id end store it in processing

}     

void opCodeVar(int *arg){}                          
void opCodeNeg(int *arg){}

void opCodeMod(int *arg){
    register_t tmp = attributeRegister(arg);
    tmp.value = tmp.value % arg[2];
}  
                       
void opCodeRet(int *arg){}                          
void opCodeMovFromVar(int *arg){}                   
void opCodeMovToVar(int *arg){}                     
void opCodeVarSize(int *arg){}                      
void opCodeVarData(int *arg){}     

int intNgr(){
    exit(EXIT_SUCCESS);
}

void intDraw(int *arg){
}

void intOb1(int *arg){
}

void intIfOr(int *arg){
}

void intIfAnd(int *arg){
}

void intIfXor(int *arg){
}

void intIfLt(int *arg){
}

void intIfLte(int *arg){
}

void intIfGt(int *arg){
}

void intIfGte(int *arg){
}

void intIfEq(int *arg){
}

void intIfNeq(int *arg){
}

void intPusha(int *arg){
}

void intPopa(int *arg){
}

void intMovFReg(int *arg){
}

void intElse(int *arg){
}

void intEnd(int *arg){
}































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

