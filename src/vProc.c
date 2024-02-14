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
    char value[9];
    uint16_t currentLine = 1;

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
            memcpy(value, line + 8, 8);
            operand[5] = '\0';
            reg[3] = '\0';
            value[8] = '\0';

            // Add your code here


            printf("%s | %s | %s\n", operand, reg, value);
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

// start:                         ins   reg   value
//     mov rg0, 5              -> 00000 000 0000 0101 
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

