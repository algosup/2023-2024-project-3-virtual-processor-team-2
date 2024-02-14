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

    stack.maxSize = MAX_STACK_SIZE / 8;             // Max size of block of stack region
    processing.maxSize = MAX_PROCESSING_SIZE / 8;   // Max size of block of progessing region
    memory.maxSize = MAX_MEMORY_SIZE / 8;           // Max size of block of memory region
    graphic.maxSize = MAX_GRAPHIC_MEMORY_SIZE / 8;  // Max size of block of graphic region
    virtualProcessor.maxSize = (stack.maxSize + processing.maxSize + memory.maxSize + graphic.maxSize);
    
    int time = 0;
    int lastTime = 0;
    int latentTicks = 0;
    while (fgets(line, sizeof(line)+1, file)) {
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

        if(strlen(line) >= LINE_MAX_BITS-2) {
            printf("%s\n", line);
            memcpy(operand, line, 5);
            memcpy(reg, line + 5, 3);
            memcpy(data, line + 8, 8);
            operand[5] = '\0';
            reg[3] = '\0';
            data[8] = '\0';

            // Add your code here
            int binOperand = (int)strtol(operand, NULL, 2);
            int binReg = (int)strtol(reg, NULL, 2);
            int binData = (int)strtol(data, NULL, 2);

            int *lineRead[] = {binOperand, binReg, binData};

            printf("%d | %d | %d\n", binOperand, binReg, binData);
        } else {
            fprintf(stderr, "ERROR: Invalid line size, line: %u\n", currentLine);
            exit(EXIT_FAILURE);
        }
        ++currentLine;
        
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

void printBinary(uint16_t value) {
    for (int i = 15; i >= 0; --i) {
        putchar((value & (1 << i)) ? '1' : '0');
    }
    putchar('\n');
}


// void readBinaryInstruction(char myChar, cache_t *cache) {
//     switch (!strlen(cache->line)){
//     // Define the opCode read in binary
    
    

//     // parserBinaryLine();

//     case 5:
//         switch (myChar){
//         case 0b00000:
//             // Code for 0b00000
//             break;
//         case 0b00001:
//             // Code for 0b00001
//             break;
//         case 0b00010:
//             // Code for 0b00010
//             break;
//         case 0b00011:
//             // Code for 0b00011
//             break;
//         case 0b00100:
//             // Code for 0b00100
//             break;
//         case 0b00101:
//             // Code for 0b00101
//             break;
//         case 0b00110:
//             // Code for 0b00110
//             break;
//         case 0b00111:
//             // Code for 0b00111
//             break;
//         case 0b01000:
//             // Code for 0b01000
//             break;
//         case 0b01001:
//             // Code for 0b00000
//             break;
//         case 0b01010:
//             // Code for 0b00001
//             break;
//         case 0b01011:
//             // Code for 0b00010
//             break;
//         case 0b01100:
//             // Code for 0b00011
//             break;
//         case 0b01101:
//             // Code for 0b00100
//             break;
//         case 0b01110:
//             // Code for 0b00101
//             break;
//         case 0b01111:
//             // Code for 0b00110
//             break;
//         case 0b10000:
//             // Code for 0b00111
//             break;
//         case 0b10001:
//             // Code for 0b01000
//             break;
//         case 0b10010:
//             // Code for 0b00000
//             break;
//         case 0b10011:
//             // Code for 0b00001
//             break;
//         case 0b10100:
//             // Code for 0b00010
//             break;
//         case 0b10101:
//             // Code for 0b00011
//             break;
//         case 0b10110:
//             // Code for 0b00100
//             break;
//         case 0b10111:
//             // Code for 0b00101
//             break;
//         case 0b11000:
//             // Code for 0b00110
//             break;
//         case 0b11001:
//             // Code for 0b00111
//             break;
//         case 0b11010:
//             // Code for 0b01000
//             break;
//         case 0b11011:
//             // Code for 0b00000
//             break;
//         case 0b11100:
//             // Code for 0b00001
//             break;
//         case 0b11101:
//             // Code for 0b00010
//             break;
//         case 0b11110:
//             // Code for 0b00011
//             break;
//         case 0b11111:
//             // Code for 0b00100
//             break;
//         default:
//             // default value
//             break;
//         }

//     // Define the register read in binary
//     // case 3:
//     //     switch (/*The result of function parserBinaryLine()*/){
//     //     case 0b00000:
//     //         // Code for 0b00000
//     //         break;
//     //     case 0b00001:
//     //         // Code for 0b00001
//     //         break;
//     //     case 0b00010:
//     //         // Code for 0b00010
//     //         break;
//     //     case 0b00011:
//     //         // Code for 0b00011
//     //         break;
//     //     case 0b00100:
//     //         // Code for 0b00100
//     //         break;
//     //     case 0b00101:
//     //         // Code for 0b00101
//     //         break;
//     //     case 0b00110:
//     //         // Code for 0b00110
//     //         break;
//     //     case 0b00111:
//     //         // Code for 0b00111
//     //         break;
//     //     default:
//     //         // default code
//     //         break;
//     //     }
//     //     break;
    
//     // // Get the immediate value from binary
//     // case 8:
//     //     switch (/*The result of function parserBinaryLine()*/){
        
//     //     }
//     //     break;
//     //     default:
//     //         // default code
//     //         break;
//     }
// }

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

