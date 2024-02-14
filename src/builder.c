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

void buildProgram(instList_t *nodeList, varList_t *varList, labelList_t *labeList, error_t *errData) {
    instNode_t *node = nodeList->head;
    while(node != NULL){
        buildNode(node, varList, labeList, errData);
        node = node->next;
        while(node != NULL && node->isBuilt){
            node = node->next;
        }
    }
}

void buildNode(instNode_t *node, varList_t *varList, labelList_t *labeList, error_t *errData) {
    switch(node->op){
        case OP_MOV:
            buildMov(node, varList, errData);
            break;
        case OP_VAR:
            buildVar(node, varList, errData);
            break;
        default:
            // TODO: transform to build error
            // errorInstruction("unknown", node, NULL, errData);
            node->isBuilt = true;
            break;
    }
}

void buildVar(instNode_t *node, varList_t *varList, error_t *errData){
    // try to add the variable to the list
    addVar(varList, node->arg0, node->arg1);
    node->isBuilt = true;
}

void buildMov(instNode_t *node, varList_t *varList, error_t *errData){
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
            
            // set the node
            node->op = OP_INT;
            node->isInter = true;
            node->inter = INT_MOV_F_REG;
            node->inputReg = getRegKind(node->arg1);
            node->arg0 = NULL;
            node->arg1 = NULL;
            node->isBuilt = true;
            node->next = newNode;

            // set the new node
            newNode->arg0 = NULL;
            newNode->arg1 = NULL;
            newNode->isBuilt = true;

            return;
        }
        // if it's var -> reg
        else{
            // check if the variable is in the list
            int varId = isVarExist(varList, node->arg1);
            if(varId == -1){
                // TODO: throw error
            }

            // Create a new node
            instNode_t *newNode = copyInstNode(node);
            
            // set the node
            node->op = OP_MOV_F_VAR;
            node->isInter = false;
            node->inputReg = RG_0;
            char buffer[5];
            sprintf(buffer, "%d", varId);
            node->arg0 = (char *)malloc(sizeof(char) * 5);
            // check if the memory is allocated
            if(node->arg0 == NULL){
                // TODO: throw memory alloc error
                exit(EXIT_FAILURE);
            }
            strcpy(node->arg0, buffer);
            node->arg1 = NULL;
            node->isBuilt = true;
            node->next = newNode;

            // set the new node
            newNode->arg0 = NULL;
            newNode->arg1 = NULL;
            newNode->isBuilt = true;

            return;
        }
    }
    else{
        // check if it's reg -> var
        // check if it's value -> var
        // check if it's var -> var
    }
    return;
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