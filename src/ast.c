/*
    this file is used to define the functions of the ast.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "ast.h"

char *getIntCode(enum interruptKind kind){
    switch(kind){
        case INT_EXIT:
            return "0";
        case INT_DRAW:
            return "1";
        case INT_OB1:
            return "2";
        case INT_OR:
            return "3";
        case INT_AND:
            return "4";
        case INT_XOR:
            return "5";
        case INT_LT:
            return "6";
        case INT_LTE:
            return "7";
        case INT_GT:
            return "8";
        case INT_GTE:
            return "9";
        case INT_EQ:
            return "10";
        case INT_NEQ:
            return "11";
        case INT_PUSHA:
            return "12";
        case INT_POPA:
            return "13";
        case INT_MOV_F_REG:
            return "14";
        case INT_ELSE:
            return "15";
        case INT_END:
            return "16";
        default:
            // TODO: transform to error
            exit(EXIT_FAILURE);
    }
}

bool addVar(varList_t *varList, char *name, char *value){
    // check if the variable already exists
    for(size_t i = 0; i < varList->size; i++){
        if (varList->list[i].name == NULL){
            continue;
        }
        if(strcmp(varList->list[i].name, name) == 0){
            // TODO: add error variable already exists
            return false;
        }
    }
    // check if the list is full
    bool isFull = true;
    for(size_t i = 0; i < varList->size; i++){
        if(varList->list[i].name == NULL){
            isFull = false;
            break;
        }
    }
    if(isFull){
        // double the size of the list
        varList->size *= 2;
        varList->list = realloc(varList->list, sizeof(var_t) * varList->size);
        for(size_t i = varList->size / 2; i < varList->size; i++){
            varList->list[i].name = NULL;
        }
    }
    // add the variable
    for(size_t i = 0; i < varList->size; i++){
        if(varList->list[i].name == NULL){
            // create id
            varList->list[i].id = i;
            varList->list[i].name = name;
            varList->list[i].value = value;
            return true;
        }
    }
    // TODO: throw error
    exit(EXIT_FAILURE);
}

int isVarExist(varList_t *varList, char *name){
    for(size_t i = 0; i < varList->size; i++){
        if(varList->list[i].name == NULL){
            continue;
        }
        if(strcmp(varList->list[i].name, name) == 0){
            return i;
        }
    }
    return -1;
}

instNode_t *copyInstNode(instNode_t *node){
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    if(newNode == NULL){
        // TODO: thorw memory alloc error
        exit(EXIT_FAILURE);
    }
    newNode->id = node->id;
    newNode->lineNb = node->lineNb;
    newNode->op = node->op;
    newNode->isInter = node->isInter;
    newNode->inter = node->inter;
    newNode->arg0 = node->arg0;
    newNode->arg1 = node->arg1;
    newNode->inputReg = node->inputReg;
    newNode->next = node->next;
    return newNode;
}