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

        static int lineRead[3];
        lineRead[0] = binOperand;
        lineRead[1] = binReg;
        lineRead[2] = binData;
        ++currentLine; 
        // Return array with 3 values
        printf("lineread in: %d\n", lineRead[1]);
        return lineRead;
    } 
    else {
        fprintf(stderr, "ERROR: Invalid line size, line: %u\n", currentLine);
        exit(EXIT_FAILURE);
    }
     
}


int *readBinaryInstruction(char *line, char *operand, char *reg, char *data, uint8_t currentLine){
    
    int *lineRead = parserBinaryFile(line, operand, reg, data, currentLine);
    printf("lineread semi in: %d\n", lineRead[1]);
    return lineRead;
}

void attributeOperand(int *arg, register_t currentRegister){
    switch (arg[0]){
    // Define the opCode read in binary
        case 00000:
            opCodeMov(arg, currentRegister);
            break;
        case 00001:
            opCodeGoto(arg, currentRegister);
            break;
        case 00010:
            opCodeCall(arg, currentRegister);
            break;
        case 00011:
            opCodeInt(arg, currentRegister);
            break;
        case 00100:
            opCodePush(arg, currentRegister);
            break;
        case 00101:
            opCodeXor(arg, currentRegister);
            break;
        case 00110:
            opCodePop(arg, currentRegister);
            break;
        case 00111:
            opCodeDiv(arg, currentRegister);
            break;
        case 01000:
            opCodeAdd(arg, currentRegister);
            break;
        case 01001:
            opCodeSub(arg, currentRegister);
            break;
        case 01010:
            opCodeMul(arg, currentRegister);
            break;
        case 01011:
            opCodeRsh(arg, currentRegister);
            break;
        case 01100:
            opCodeLsh(arg, currentRegister);
            break;
        case 01101:
            opCodeAnd(arg, currentRegister);
            break;
        case 01110:
            opCodeOr(arg, currentRegister);
            break;
        case 01111:
            opCodeNot(arg, currentRegister);
            break;
        case 10000:
            opCodeUseReg(arg, currentRegister);
            break;
        case 10001:
            opCodeUseVar(arg, currentRegister);
            break;
        case 10010:
            opCodeLab(arg, currentRegister);
            break;
        case 10011:
            opCodeVar(arg, currentRegister);
            break;
        case 10100:
            opCodeNeg(arg, currentRegister);
            break;
        case 10101:
            opCodeMod(arg, currentRegister);
            break;
        case 10110:
            opCodeRet(arg, currentRegister);
            break;
        case 10111:
            opCodeMovFromVar(arg, currentRegister);
            break;
        case 11000:
            opCodeMovToVar(arg, currentRegister);
            break;
        case 11001:
            opCodeVarSize(arg, currentRegister);
            break;
        case 11010:
            opCodeVarData(arg, currentRegister);
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
            printf("Test0");
            return rg0;
            break;
        case 001:
            printf("Test1");
            return rg1;
            break;
        case 010: 
            printf("Test2");
            return rg2;
            break;
        case 011:
            printf("Test3");
            return rg3;
            break;
        case 100:
            printf("Test4");
            return rg4;
            break;
        case 101:
            printf("Test5");
            return rg5;
            break;
        case 110:
            printf("Test6");
            return rg6;
            break;
        case 111:
            printf("Test7");
            return rg7;
            break;
        default:
            printf("defiakl");
            exit(EXIT_FAILURE);
    }
}

void opCodeMov(int *arg, register_t currentRegister){
    // switch () {
    // case true:
    //     break;
    // case false:
        currentRegister.value = arg[2];
    //     break;
    // default:
    // }
}

void opCodeGoto(int *arg, register_t currentRegister){}                                    
void opCodeCall(int *arg, register_t currentRegister){}   

// Attribute the specific interaction depending the last 8bits 
void opCodeInt(int *arg, register_t currentRegister){
    int tmp = arg[2];
    switch(tmp) {
        case 00000000:
            intNgr();
            break;
        case 00000001:
            intDraw(arg, currentRegister);
            break;
        case 00000010:
            intOb1(arg, currentRegister);
            break;
        case 00000011:
            intIfOr(arg, currentRegister);
            break;
        case 00000100:
            intIfAnd(arg, currentRegister);
            break;
        case 00000101:
            intIfXor(arg, currentRegister);
            break;
        case 00000110:
            intIfLt(arg, currentRegister);
            break;
        case 00000111:
            intIfLte(arg, currentRegister);
            break;
        case 00001000:
            intIfGt(arg, currentRegister);
            break;
        case 00001001:
            intIfGte(arg, currentRegister);
            break;
        case 00001010:
            intIfEq(arg, currentRegister);
            break;
        case 00001011:
            intIfNeq(arg, currentRegister);
            break;
        case 00001100:
            intPusha(arg, currentRegister);
            break;
        case 00001101:
            intPopa(arg, currentRegister);
            break;
        case 00001110:
            intMovFReg(arg, currentRegister);
            break;
        case 00001111:
            intElse(arg, currentRegister);
            break;
        case 00010000:
            intEnd(arg, currentRegister);
            break;
        default: // Default don't find the second arg 
            exit(EXIT_FAILURE);
            break;
    }
}        
                  
void opCodePush(int *arg, register_t currentRegister){}     

void opCodeXor(int *arg, register_t currentRegister){
    currentRegister.value = currentRegister.value ^ arg[2];
}       

void opCodePop(int *arg, register_t currentRegister){}  

void opCodeDiv(int *arg, register_t currentRegister){
    currentRegister.value = currentRegister.value / arg[2];
}   

void opCodeAdd(int *arg, register_t currentRegister){
        currentRegister.value += arg[2];
}             

void opCodeSub(int *arg, register_t currentRegister){
        currentRegister.value -= arg[2];
}   

void opCodeMul(int *arg, register_t currentRegister){
        currentRegister.value *= arg[2];
}                          

void opCodeRsh(int *arg, register_t currentRegister){
        currentRegister.value = currentRegister.value >> arg[2];
}        

void opCodeLsh(int *arg, register_t currentRegister){
        currentRegister.value = currentRegister.value << arg[2];
}                   

void opCodeAnd(int *arg, register_t currentRegister){
        currentRegister.value = currentRegister.value & arg[2];
} 
                        
void opCodeOr(int *arg, register_t currentRegister){
        currentRegister.value = currentRegister.value | arg[2];
}      

void opCodeNot(int *arg, register_t currentRegister){
        currentRegister.value = ~currentRegister.value;
}
                          
void opCodeUseReg(int *arg, register_t currentRegister){}                       
void opCodeUseVar(int *arg, register_t currentRegister){}                       

void opCodeLab(int *arg, register_t currentRegister){
    //get lab id end store it in processing

}     

void opCodeVar(int *arg, register_t currentRegister){}                          
void opCodeNeg(int *arg, register_t currentRegister){}

void opCodeMod(int *arg, register_t currentRegister){
        currentRegister.value = currentRegister.value % arg[2];
}  
                       
void opCodeRet(int *arg, register_t currentRegister){}                          
void opCodeMovFromVar(int *arg, register_t currentRegister){}                   
void opCodeMovToVar(int *arg, register_t currentRegister){}                     
void opCodeVarSize(int *arg, register_t currentRegister){}                      
void opCodeVarData(int *arg, register_t currentRegister){}     




int intNgr(){
    exit(EXIT_SUCCESS);
}

void intDraw(int *arg, register_t currentRegister){
}

void intOb1(int *arg, register_t currentRegister){
}

void intIfOr(int *arg, register_t currentRegister){
}

void intIfAnd(int *arg, register_t currentRegister){
}

void intIfXor(int *arg, register_t currentRegister){
}

void intIfLt(int *arg, register_t currentRegister){
}

void intIfLte(int *arg, register_t currentRegister){
}

void intIfGt(int *arg, register_t currentRegister){
}

void intIfGte(int *arg, register_t currentRegister){
}

void intIfEq(int *arg, register_t currentRegister){
}

void intIfNeq(int *arg, register_t currentRegister){
}

void intPusha(int *arg, register_t currentRegister){
}

void intPopa(int *arg, register_t currentRegister){
}

void intMovFReg(int *arg, register_t currentRegister){
}

void intElse(int *arg, register_t currentRegister){
}

void intEnd(int *arg, register_t currentRegister){
}