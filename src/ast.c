/*
    this file is used to define the functions of the ast.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "ast.h"
#include "stringPlus.h"


char *getIntCode(enum interruptKind kind, asm_error_t *errData){
    switch(kind){
        case INT_EXIT:
            return "0";
        case INT_DRAW:
            return "1";
        case INT_OB1:
            return "2";
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
        default:
            errorIntCodeNotSupported(kind, errData);
            return NULL;
    }
}

varList_t *createEmptyVarList(){
    // Init variables list struct
    varList_t *varList = malloc(sizeof(varList_t));
    varList->size = 10;
    varList->list = malloc(sizeof(var_t) * varList->size);
    // Init variables list
    for(size_t i = 0; i < varList->size; i++){
        varList->list[i].name = NULL;
    }
    return varList;
}

bool addVar(varList_t *varList, char *name, char *value, long lineNb, asm_error_t *errData){
    // check if the variable already exists
    for(size_t i = 0; i < varList->size; i++){
        if (varList->list[i].name == NULL){
            continue;
        }
        if(strcmp(varList->list[i].name, name) == 0){
            errorVarAlreadyExist(name, lineNb, errData);
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
            varList->list[i].value = cleanString(value, errData);
            return true;
        }
    }
    unknowError("On variable declaration", errData);
    return false;
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

instList_t *createEmptyInstList(){
    instList_t *instList = malloc(sizeof(instList_t));
    instList->head = NULL;
    return instList;
}

instNode_t *copyInstNode(instNode_t *node, asm_error_t *errData){
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    if(newNode == NULL){
        errorMemAlloc(errData);
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

instNode_t *createEmptyInstNode(asm_error_t *errData) {
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    if (newNode == NULL) {
        errorMemAlloc(errData);
    }
    newNode->id = -1;
    newNode->lineNb = -1;
    newNode->isInter = false;
    newNode->arg0 = NULL;
    newNode->arg1 = NULL;
    newNode->isBuilt = false;
    newNode->next = NULL;

    return newNode;
}


labelList_t *createEmptyLabelList(){
    labelList_t *labelList = malloc(sizeof(labelList_t));
    labelList->size = 10;
    labelList->list = malloc(sizeof(label_t) * labelList->size);
    for(size_t i = 0; i < labelList->size; i++){
        labelList->list[i].name = NULL;
    }
    return labelList;
}

int addLabel(labelList_t *labelList, char *name, long nodeId, long lineNb, asm_error_t *errData){
    // check if the label already exists
    for(size_t i = 0; i < labelList->size; i++){
        if (labelList->list[i].name == NULL){
            continue;
        }
        if(strcmp(labelList->list[i].name, name) == 0){
            errorLabelDeclaration(lineNb, name, errData);
        }
    }

    // check if the list is full
    bool isFull = true;
    for(size_t i = 0; i < labelList->size; i++){
        if(labelList->list[i].name == NULL){
            isFull = false;
            break;
        }
    }
    if(isFull){
        // double the size of the list
        labelList->size *= 2;
        labelList->list = realloc(labelList->list, sizeof(label_t) * labelList->size);
        for(size_t i = labelList->size / 2; i < labelList->size; i++){
            labelList->list[i].name = NULL;
        }
    }

    // add the label
    for(size_t i = 0; i < labelList->size; i++){
        if(labelList->list[i].name == NULL){
            labelList->list[i].name = name;
            labelList->list[i].nodeId = nodeId;
            labelList->list[i].id = i;
            return i;
        }
    }

    unknowError("On label declaration", errData);
    return -1;
}

int isLabelExist(labelList_t *labelList, char *name){
    for(size_t i = 0; i < labelList->size; i++){
        if(labelList->list[i].name == NULL){
            continue;
        }
        if(strcmp(labelList->list[i].name, name) == 0){
            return labelList->list[i].id;
        }
    }
    return -1;
}