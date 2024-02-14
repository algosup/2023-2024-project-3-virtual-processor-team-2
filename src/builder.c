/*
    This file is the builder of the project
    It will read the instruction list and optimize or change them
    to make the program able to be translated to binary code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "builder.h"

void buildProgram(instList_t *nodeList, error_t *errData) {
    instNode_t *node = nodeList->head;
    while(node != NULL){
        buildNode(node, errData);
        node = node->next;
        while(node != NULL && node->isBuilt){
            node = node->next;
        }
    }
}

void buildNode(instNode_t *node, error_t *errData) {
    switch(node->op){
        case OP_MOV:
            buildMov(node, errData);
            break;
        default:
            // TODO: transform to build error
            // errorInstruction("unknown", node, NULL, errData);
            node->isBuilt = true;
            break;
    }
}

void buildMov(instNode_t *node, error_t *errData){
    // check if it's mov to reg
    if(node->arg0 == NULL){
        // check if it's val -> reg
        if(isUnsignedInt(node->arg1)){
            return;
        }
        // check if it's reg -> reg
        if (isFromReg(node->arg1)){
            // Create a new node
            instNode_t *newNode = copyInstNode(node);
            
            return;
        }
        // check if it's var -> reg
    }
    // check if it's reg -> var
    // check if it's value -> var
    // check if it's var -> var
    return;
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

bool isUnsignedInt(char *str){
    for(size_t i = 0; i < strlen(str); i++){
        if(str[i] < '0' || str[i] > '9'){
            return false;
        }
    }
    return true;
}

bool isFromReg(char *str){
    if(strlen(str) != 3){
        return false;
    }
    if(str[0] != 'R' && str[0] != 'r'){
        return false;
    }
    if(str[1] < 'G' || str[1] > 'g'){
        return false;
    }
    if(str[2] < '0' || str[2] > '7'){
        return false;
    }
    return true;
}

enum regKind getRegKind(char *str) {
    if (str == NULL || str[0] != 'r' || str[1] != 'g' || str[2] < '0' || str[2] > '7' || str[3] != '\0') {
        fprintf(stderr, "Error: invalid register format\n");
        exit(EXIT_FAILURE);
    }

    switch (str[2]) {
    case '0':
        return RG_0;
    case '1':
        return RG_1;
    case '2':
        return RG_2;
    case '3':
        return RG_3;
    case '4':
        return RG_4;
    case '5':
        return RG_5;
    case '6':
        return RG_6;
    case '7':
        return RG_7;
    default:
        fprintf(stderr, "Error: unknown register\n");
        exit(EXIT_FAILURE);
    }
}