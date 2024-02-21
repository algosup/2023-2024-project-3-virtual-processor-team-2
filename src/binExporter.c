/*
    This file is a part of the 2at2 project
    It will export the AST to a binary file
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "binExporter.h"
#include "error.h"
#include "debug.h"

void exportToBin(instList_t *nodeList, char *filename, varList_t *varList, asm_error_t *errData){
    // Open the file
    FILE *file = fopen(filename, "wb");

    // Check if the file was opened
    if(file == NULL){
        unknowError("File cannot be opened", errData);
        return;
    }
    instNode_t *node = nodeList->head;
    while(node != NULL){
        // Write the operation
        char *opCode = opToBinCode(node->op);
        if(opCode == NULL){
            errorOpBinConversion(getOpName(node->op), node->lineNb, errData);
            return;
        }
        fwrite(opCode, 1, 5, file);

        // write the reg
        char* regCode = regToBinCode(node->inputReg);
        fwrite(regCode, 1, 3, file);

        // check if the operation has an argument or if it is an interrupt
        if(node->isInter){
            // write the interrupt
            char *interCode = interToBinCode(node->inter);
            if(interCode == NULL){
                errorIntBinConversion(getInterName(node->inter), node->lineNb, errData);
                return;
            }
            fwrite(interCode, 1, 8, file);
        } else {
            // write the argument
            if(node->arg0 != NULL){
                fwrite(stringToBinary(node->arg0, errData), 1, strlen(node->arg0) * 8, file);
            }
            else if(node->arg1 != NULL){
                fwrite(stringToBinary(node->arg1, errData), 1, strlen(node->arg1) * 8, file);
            }
            else {
                fwrite("00000000", 1, 8, file);
            }
        }

        // Move to the next node
        node = node->next;

    }

    // Close the file
    fclose(file);
}

char *opToBinCode(enum opKind op){
    switch (op)
    {
    case OP_MOV:
        return "00000";
    case OP_GOTO:
        return "00001";
    case OP_CALL:
        return "00010";
    case OP_INT:
        return "00011";
    case OP_PUSH:
        return "00100";
    case OP_POP:  
        return "00110";
    case OP_B_XOR:
        return "00101";
    case OP_DIV:
        return "00111";
    case OP_ADD:
        return "01000";
    case OP_SUB:
        return "01001";
    case OP_MUL:
        return "01010";
    case OP_R_SHIFT:
        return "01011";
    case OP_L_SHIFT:
        return "01100";
    case OP_B_AND:
        return "01101";
    case OP_B_OR:
        return "01110";
    case OP_B_NOT:
        return "01111";
    case OP_USE_REG:
        return "10000";
    case OP_USE_VAR:
        return "10001";
    case OP_LAB:
        return "10010";
    case OP_VAR:
        return "10011";
    case OP_MOD:
        return "10101";
    case OP_RET:
        return "10110";
    case OP_MOV_F_VAR:
        return "10111";
    case OP_MOV_T_VAR:
        return "11000";
    case OP_VAR_SIZE:
        return "11001";
    case OP_VAR_DATA:
        return "11010";
    default:
        return NULL;
    }
}

char *regToBinCode(enum regKind reg){
    switch (reg)
    {
    case RG_0:
        return "000";
    case RG_1:
        return "001";
    case RG_2:
        return "010";
    case RG_3:
        return "011";
    case RG_4:
        return "100";
    case RG_5:
        return "101";
    case RG_6:
        return "110";
    case RG_7:
        return "111";
    default:
        return "000";
    }
}

char *interToBinCode(enum interruptKind inter){
    switch (inter)
    {
    case INT_EXIT:
        return "00000000";
    case INT_DRAW:
        return "00000001";
    case INT_OB1:
        return "00000010";
    case INT_OR:
        return "00000011";
    case INT_AND:
        return "00000100";
    case INT_XOR:
        return "00000101";
    case INT_LT:
        return "00000110";
    case INT_LTE:
        return "00000111";
    case INT_GT:
        return "00001000";
    case INT_GTE:
        return "00001001";
    case INT_EQ:
        return "00001010";
    case INT_NEQ:
        return "00001011";
    case INT_PUSHA:
        return "00001100";
    case INT_POPA:
        return "00001101";
    case INT_MOV_F_REG:
        return "00001110";
    case INT_ELSE:
        return "00001111";
    case INT_END:
        return "00010000";
    default:
        return NULL;
    }
}

char *stringToBinary(char *s, asm_error_t *errData) {
    // check if it's a number
    if (s[0] >= '0' && s[0] <= '9') {
        int num = atoi(s);
        char *bin = (char *)malloc(9);
        if (bin == NULL) {
            errorMemAlloc(errData);
        }

        // Fill binary representation with leading zeros
        for (int i = 7; i >= 0; i--) {
            bin[i] = (num >> (7 - i)) & 1 ? '1' : '0';
        }
        bin[8] = '\0'; //
        return bin;
    } else {
        // Convert char to byte
        char *bin = (char *)malloc(strlen(s) * 8 + 1);
        if (bin == NULL) {
            errorMemAlloc(errData);
        }

        // Fill binary representation
        size_t index = 0;
        for (size_t i = 0; i < strlen(s); i++) {
            for (int j = 7; j >= 0; j--) {
                bin[index++] = (s[i] >> j) & 1 ? '1' : '0';
            }
        }
        bin[index] = '\0';
        return bin;
    }
}

