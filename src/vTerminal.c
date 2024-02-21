/*
    This file is part of VAT2.
    This file contains functions related to the virtual terminal.
*/

#include <stdlib.h>
#include <string.h>

#include "vTerminal.h"

void runVTerminal(asm_error_t *errData){
    char *command = (char *)malloc(100 * sizeof(char));
    bool isRunning = true;
    bool isExecuted = false;
    while(isRunning){
        printf("vTerminal > ");
        gets(command);
        if(strcmp(command, "exit") == 0){
            isRunning = false;
        }
        else{
            isRunning = runCmd(command, errData);
        }
    }
    free(command);
    if(!isExecuted){
        errorRuntime("Unknow runtime error", errData);
        printErrorSummary(errData); 
        exit(EXIT_FAILURE); 
    }
    exit(EXIT_SUCCESS);
}

bool runCmd(char *command, asm_error_t *errData){
    if(strcmp(command, "help") == 0){
        printf("Commands:\n");
        printf("exit - to exit the terminal\n");
        printf("clear - to clear the terminal\n");
        printf("help - to display the help\n");
    }
    else if(strcmp(command, "clear") == 0){
        system("clear");
    }
    else{
        //Check if the file is present
        FILE *file = fopen(command, "rb");
        if(file == NULL){
            errorfnf(command, errData);
        }
        // Run program
        char line[16];
        char operand[6];
        char reg[4];
        char data[9];
        uint16_t currentLine = 1;

        int time = 0;
        int lastTime = 0;
        int latentTicks = 0;
        while(fgets(line, sizeof(line) + 1, file)) {
            setClock(time, lastTime, latentTicks);

            instruction_t inst = charBinToInst(line);
            if(!run(inst, errData)){
                fclose(file);
                return false;
            }
        }
        fclose(file);
    }
    return true;
}
