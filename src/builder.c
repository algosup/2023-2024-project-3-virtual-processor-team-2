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
#include "stringPlus.h"

#define IMMEDIATE_VAL_SIZE 8

void buildProgram(instList_t *nodeList, varList_t *varList, labelList_t *labeList, asm_error_t *errData) {
    instNode_t *node = nodeList->head;
    while(node != NULL){
        buildNode(node, varList, labeList, errData);
        node = node->next;
        while(node != NULL && node->isBuilt){
            node = node->next;
        }
    }
}

void buildNode(instNode_t *node, varList_t *varList, labelList_t *labeList, asm_error_t *errData) {
    switch(node->op){
        case OP_MOV:
            buildMov(node, varList, errData);
            break;
        case OP_GOTO:
            buildGoto(node, labeList, errData);
            break;
        case OP_CALL:
            buildCall(node, labeList, errData);
            break;
        case OP_INT:
            node->isBuilt = buildIntOpe(node, errData);
            break;
        case OP_B_NOT:
            // Check if input register is register 3
            if(node->inputReg == RG_3){
                // error read only reg
                errorReadOnly(errData);
            }
            node->isBuilt = true;
            break;
        case OP_B_XOR: case OP_DIV: case OP_ADD: case OP_SUB: case OP_MUL: case OP_R_SHIFT: case OP_L_SHIFT: case OP_B_AND: case OP_B_OR: case OP_MOD:
            buildOperation(node, varList, errData);
            break;
        case OP_PUSH:
            node->isBuilt = true;
            break;
        case OP_RET:
            node->isBuilt = true;
            break;
        case OP_VAR:
            buildVar(node, varList, errData);
            break;
        case OP_LAB:
            buildLabel(node, labeList, errData);
            break;       
        case OP_POP:
            node->isBuilt = true;
            break;
        default:
            unknowError("Operation code not found during build", errData);
            node->isBuilt = true;
            break;
    }
}

void buildVar(instNode_t *node, varList_t *varList, asm_error_t *errData){
    // copy variable value
    char *varData = (char *)malloc(sizeof(char) * (strlen(node->arg1) + 1));
    strcpy(varData, node->arg1);
;
    int varId = isVarExist(varList, node->arg0);
    if(varId == -1){
        errorVarNotExist(node->lineNb, node->arg0, errData);
    }
    // set arg0 as id
    node->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
    sprintf(node->arg0, "%d", varId);

    node->arg1 = NULL;
    node->isBuilt = true;

    // get the datasize of the variable
    int dataSize = getVarDatasize(varData);
    if(dataSize > 1){
        // add the null terminator
        dataSize++;
    }

    // create a new node
    instNode_t *newNode = createEmptyInstNode(errData);
    newNode->id = node->id;
    newNode->lineNb = node->lineNb;
    newNode->op = OP_VAR_SIZE;
    newNode->inputReg = RG_0;

    newNode->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
    sprintf(newNode->arg0, "%d", dataSize);

    newNode->isBuilt = true;
    newNode->next = node->next;
    node->next = newNode;

    if(dataSize == 1){
        // create a new node
        instNode_t *dataNode = createEmptyInstNode(errData);
        dataNode->id = node->id;
        dataNode->lineNb = node->lineNb;
        dataNode->op = OP_VAR_DATA;
        dataNode->inputReg = RG_0;

        dataNode->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
        sprintf(dataNode->arg0, "%s", varData);

        dataNode->isBuilt = true;
        dataNode->next = newNode->next;
        newNode->next = dataNode;

        return;
    }
    else{
        // add the null terminator
        // create a new node
        instNode_t *nullNode = createEmptyInstNode(errData);
        nullNode->id = node->id;
        nullNode->lineNb = node->lineNb;
        nullNode->op = OP_VAR_DATA;
        nullNode->inputReg = RG_0;

        nullNode->arg0 = malloc(IMMEDIATE_VAL_SIZE + 1 * sizeof(char));
        sprintf(nullNode->arg0, "%c", '\0');

        nullNode->isBuilt = true;
        nullNode->next = newNode->next;
        newNode->next = nullNode;

        // Reverse iteration over varData to create nodes
        for (int i = dataSize - 1; i >= 0; i--) {
            // create a new node
            instNode_t *dataNode = createEmptyInstNode(errData);
            dataNode->id = node->id;
            dataNode->lineNb = node->lineNb;
            dataNode->op = OP_VAR_DATA;
            dataNode->inputReg = RG_0;

            dataNode->arg0 = malloc(IMMEDIATE_VAL_SIZE + 1 * sizeof(char));
            sprintf(dataNode->arg0, "%c", varData[i]);

            dataNode->isBuilt = true;
            dataNode->next = newNode->next;
            newNode->next = dataNode;
        }
    }
}

void buildLabel(instNode_t *node, labelList_t *labelList, asm_error_t *errData){
    // try to add the label to the list
    int labId = isLabelExist(labelList, node->arg0);
    if(labId == -1){
        errorLabelNotFound(node->lineNb, node->arg0, errData);
    }

    // set arg0 as id
    node->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
    sprintf(node->arg0, "%d", labId);

    node->isBuilt = true;
}

void buildMov(instNode_t *node, varList_t *varList, asm_error_t *errData){
    // check if it's mov to reg
    if(node->arg0 == NULL){
        // check if it's val -> reg
        if(isUnsignedInt(node->arg1)){
            node->arg0 = node->arg1;
            node->arg1 = NULL;
            return;
        }
        // check if it's reg -> reg
        if (isFromReg(node->arg1)){
            // Create a new node
            instNode_t *newNode = copyInstNode(node, errData);
            
            // set the node
            node->op = OP_INT;
            node->isInter = true;
            node->inter = INT_MOV_F_REG;
            node->inputReg = getRegKind(node->arg1, node->lineNb, errData);
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
                errorVarNotExist(node->lineNb, node->arg1, errData);
            }

            // Create a new node
            instNode_t *newNode = copyInstNode(node, errData);
            
            // set the node
            node->op = OP_MOV_F_VAR;
            node->isInter = false;
            node->inputReg = RG_0;
            node->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
            sprintf(node->arg0, "%d", varId);
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
        if(node->arg1 != NULL && isFromReg(node->arg1)){
            // check if the variable is in the list
            int varId = isVarExist(varList, node->arg0);
            if(varId == -1){
                errorVarNotExist(node->lineNb, node->arg0, errData);
            }
            // Create a new node
            instNode_t *newNode = copyInstNode(node, errData);
            
            // set the node
            node->op = OP_INT;
            node->isInter = true;
            node->inter = INT_MOV_F_REG;
            node->inputReg = getRegKind(node->arg1, node->lineNb, errData);
            node->arg0 = NULL;
            node->arg1 = NULL;
            node->isBuilt = true;
            node->next = newNode;

            // set the new node
            newNode->op = OP_MOV_T_VAR;
            newNode->isInter = false;
            newNode->inputReg = RG_0;

            newNode->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
            sprintf(newNode->arg0, "%d", varId);

            newNode->arg1 = NULL;
            newNode->isBuilt = true;

            return;
        }
        // check if it's value -> var
        else if(isUnsignedInt(node->arg1)){
            // check if the variable is in the list
            int varId = isVarExist(varList, node->arg0);
            if(varId == -1){
                errorVarNotExist(node->lineNb, node->arg0, errData);
            }

            // Create a new node
            instNode_t *newNode = copyInstNode(node, errData);
            
            // set the node
            node->op = OP_MOV_T_VAR;
            node->isInter = false;
            node->inputReg = RG_0;

            node->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
            sprintf(node->arg0, "%d", varId);

            node->arg1 = NULL;
            node->isBuilt = true;
            node->next = newNode;

            // set the new node
            newNode->op = OP_MOV;
            newNode->inputReg = RG_0;
            newNode->arg0 = newNode->arg1;
            newNode->arg1 = NULL;
            newNode->isBuilt = true;
            return;
        }
        // check if it's var -> var
        else{
            // Create a new node
            instNode_t *newNode = copyInstNode(node, errData);

            // set the new node
            // check if the variable is in the list
            int varId = isVarExist(varList, node->arg0);
            if(varId == -1){
                errorVarNotExist(node->lineNb, node->arg0, errData);
            }
            newNode->op = OP_MOV_T_VAR;
            newNode->isInter = false;
            newNode->inputReg = RG_0;

            newNode->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
            sprintf(newNode->arg0, "%d", varId);

            newNode->arg1 = NULL;
            newNode->isBuilt = true;
            
            // set the node
            // check if the variable is in the list
            varId = isVarExist(varList, node->arg1);
            if(varId == -1){
                errorVarNotExist(node->lineNb, node->arg1, errData);
            }

            node->op = OP_MOV_F_VAR;
            node->isInter = false;
            node->inputReg = RG_0;

            node->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
            sprintf(node->arg0, "%d", varId);

            node->arg1 = NULL;
            node->isBuilt = true;
            node->next = newNode;
            return;
        }
    }
    unknowError("Mov build is failed", errData);

    return;
}

void buildGoto(instNode_t *node, labelList_t *labelList, asm_error_t *errData){
    // check if the label is in the list
    int labId = isLabelExist(labelList, node->arg0);
    if(labId == -1){
        errorLabelNotFound(node->lineNb, node->arg0, errData);
    }

    // change arg0 to id
    node->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
    sprintf(node->arg0, "%d", labId);

    node->arg1 = NULL;
    node->isBuilt = true;
    return;
}

void buildCall(instNode_t *node, labelList_t *labelList, asm_error_t *errData){
    // check if the label is in the list
    int labId = isLabelExist(labelList, node->arg0);
    if(labId == -1){
        errorLabelNotFound(node->lineNb, node->arg0, errData);
        return;
    }

    // change arg0 to id
    node->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
    sprintf(node->arg0, "%d", labId);

    node->arg1 = NULL;
    node->isBuilt = true;

    return;
}

void buildOperation(instNode_t *node, varList_t *varList, asm_error_t *errData){
    // check if the second argument is an unsigned int
    if(node->arg1 != NULL && isUnsignedInt(node->arg1)){
        // pass argument 1 to arg0
        node->arg0 = node->arg1;
        node->arg1 = NULL;
        return;
    }
    // check if the second argument is a register
    else if(node->arg1 != NULL && isFromReg(node->arg1)){
        // Create a new node
        instNode_t *newNode = copyInstNode(node, errData);
        
        // set the node
        node->op = OP_INT;
        node->isInter = true;
        node->inter = INT_MOV_F_REG;
        node->inputReg = getRegKind(node->arg1, node->lineNb, errData);
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
    // check if the second argument is a variable
    else if(node->arg1 != NULL){
        // check if the variable is in the list
        int varId = isVarExist(varList, node->arg1);
        if(varId == -1){
            errorVarNotExist(node->lineNb, node->arg1, errData);
        }

        // Create a new node
        instNode_t *newNode = copyInstNode(node, errData);

        // set the node
        node->op = OP_MOV_F_VAR;
        node->isInter = false;
        node->inputReg = RG_0;

        node->arg0 = malloc(IMMEDIATE_VAL_SIZE+1 * sizeof(char));
        sprintf(node->arg0, "%d", varId);

        node->arg1 = NULL;
        node->isBuilt = true;
        node->next = newNode;

        // set the new node
        newNode->arg0 = NULL;
        newNode->arg1 = NULL;
        newNode->isBuilt = true;

        return;
    }
    unknowError("Operation connot be built", errData);
    return;
}

enum regKind getRegKind(char *str, long lineNb, asm_error_t *errData) {
    if (str == NULL || str[0] != 'r' || str[1] != 'g' || str[2] < '0' || str[2] > '7' || str[3] != '\0') {
        errorInvalidRegister(str, lineNb, errData);
        return RG_0;
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
        errorInvalidRegister(str, lineNb, errData);
        return RG_0;
    }
}

int getVarDatasize(char *str){
    // check if the string is a number
    if(isUnsignedInt(str)){
        return 1;
    }
    else{
        return (int)strlen(str);
    }
}

bool buildIntOpe(instNode_t *node, asm_error_t *errData){
    switch (node->inter)
    {
    case INT_LT: case INT_GT: case INT_LTE: case INT_GTE: case INT_EQ: case INT_NEQ:
        // check if next node is a goto
        if(node->next == NULL || node->next->op != OP_GOTO){
            errorIfInt(node->lineNb, errData);
            return false;
        }
        return true;    
    default:
        return true;
    }
}