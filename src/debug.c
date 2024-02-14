/*
    This file contains functions for debugging the interpreter
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "debug.h"

const char *logFile = "2at2.log";

void printAst(instList_t *nodeList){
    instNode_t *node = nodeList->head;
    while(node != NULL){
        printNodeData(node);
        node = node->next;
    }
}

void printNodeData(instNode_t *node){
    FILE *file = fopen(logFile, "ab");
    if(file == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Get current time
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    // Format date
    char date_str[20];
    strftime(date_str, sizeof(date_str), "%d-%m-%y %H:%M:%S", timeinfo);

    fprintf(file, "%s | Node ID: %ld\n", date_str, node->id);
    fprintf(file, "%s | Line number: %ld\n", date_str, node->lineNb);
    fprintf(file, "%s | Instruction: %s\n", date_str, getOpName(node->op));
    fprintf(file, "%s | Target reg: %d\n", date_str, node->inputReg);
    fprintf(file, "%s | Argument 0: %s\n", date_str, node->arg0);
    fprintf(file, "%s | Argument 1: %s\n", date_str, node->arg1);
    fprintf(file, "\n");
    fclose(file);
}

char *getOpName(enum opKind kind){
    switch(kind){
        case OP_MOV:
            return "MOV";
        case OP_GOTO:
            return "GOTO";
        case OP_CALL:
            return "CALL";
        case OP_INT:
            return "INT";
        case OP_PUSH:
            return "PUSH";
        case OP_B_XOR:
            return "XOR";
        case OP_POP:
            return "POP";
        case OP_DIV:
            return "DIV";
        case OP_ADD:
            return "ADD";
        case OP_SUB:
            return "SUB";
        case OP_MUL:
            return "MUL";
        case OP_R_SHIFT:
            return "R_SHIFT";
        case OP_L_SHIFT:
            return "L_SHIFT";
        case OP_B_AND:
            return "AND";
        case OP_B_OR:
            return "OR";
        case OP_B_NOT:
            return "NOT";
        case OP_INC:
            return "INC";
        case OP_DEC:
            return "DEC";
        case OP_LAB:
            return "LAB";
        case OP_VAR:
            return "VAR";
        case OP_MOD:
            return "MOD";
        case OP_RET:
            return "RET";
        default:
            return "UNKNOWN";
    }
}