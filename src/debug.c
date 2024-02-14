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
    fprintf(file, "%s | Is interrupt: %s\n", date_str, node->isInter ? "true" : "false");
    if(node->isInter){
        fprintf(file, "%s | Interrupt: %s\n", date_str, getInterName(node->inter));
    }
    fprintf(file, "%s | Target reg: %d\n", date_str, node->inputReg);
    fprintf(file, "%s | Argument 0: %s\n", date_str, node->arg0);
    fprintf(file, "%s | Argument 1: %s\n", date_str, node->arg1);
    fprintf(file, "%s | Is built: %s\n", date_str, node->isBuilt ? "true" : "false");
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
        case OP_LAB:
            return "LAB";
        case OP_VAR:
            return "VAR";
        case OP_MOD:
            return "MOD";
        case OP_RET:
            return "RET";
        case OP_MOV_F_VAR:
            return "MOV_F_VAR";
        case OP_MOV_T_VAR:
            return "MOV_T_VAR";
        case OP_VAR_SIZE:
            return "VAR_SIZE";
        case OP_VAR_DATA:
            return "VAR_DATA";
        default:
            return "UNKNOWN";
    }
}

char *getInterName(enum interruptKind kind){
    switch(kind){
        case INT_EXIT:
            return "EXIT";
        case INT_DRAW:
            return "DRAW";
        case INT_OB1:
            return "OB1";
        case INT_OR:
            return "OR";
        case INT_AND:
            return "AND";
        case INT_XOR:
            return "XOR";
        case INT_LT:
            return "LT";
        case INT_LTE:
            return "LTE";
        case INT_GT:
            return "GT";
        case INT_GTE:
            return "GTE";
        case INT_EQ:
            return "EQ";
        case INT_NEQ:
            return "NEQ";
        case INT_PUSHA:
            return "PUSHA";
        case INT_POPA:
            return "POPA";
        case INT_MOV_F_REG:
            return "MOV_F_REG";
        case INT_ELSE:
            return "ELSE";
        case INT_END:
            return "END";
        default:
            return "UNKNOWN";
    }
}