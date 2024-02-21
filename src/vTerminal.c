/*
    This file is part of virtual processor
    This file conatain all functions related to the virtual terminal
*/

#include <stdio.h>
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
            isExecuted = isRunning = false;
        }
        else{
            runCmd(command);
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

        fclose(file);
    }
    return true;
}