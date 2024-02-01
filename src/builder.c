/*
    This file is the builder of the project
    It will read the instruction list and build the program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "builder.h"

void printInstList(instList_t *list, char *dest){
    FILE *file = fopen(dest, "w");
    if(file == NULL){
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    instNode_t *node = list->head;
    while(node != NULL){
        switch(node->inst){
            case INST_OP:
                fprintf(file, "%ld(OP): %s %s\n", node->id, printOPKind(node->nodeType.op->op), printArgs(node));
                break;
            case INST_ACT:
                if(node->nodeType.act->act != ACT_CMP){
                    fprintf(file, "%ld(ACT): %s %s\n", node->id, printACTKind(node->nodeType.act->act), printArgs(node));
                    break;
                }
                else{
                    fprintf(file, "%ld(ACT): %s %s\n", node->id, printCMP(node), printArgs(node));
                    break;
                }
            case INST_LABEL:
                fprintf(file, "%ld(LAB): %s\n", node->id, node->arg0.target);
                break;
            case INST_VAR:
                fprintf(file, "%ld(VAR): %s\n", node->id, printArgs(node));
                break;
            default:
                fprintf(stderr, "Invalid instruction\n");
                exit(EXIT_FAILURE);
        }
        node = node->next;
    }
    fclose(file);
}

char *printArgs(instNode_t *node){
    char *arg0 = malloc(sizeof(char) * 128);
    // get type of arguments
    if(node->arg0Type == VAR_INT){
        sprintf(arg0, "%d(int)", node->arg0.i_value);
    }
    else if(node->arg0Type == VAR_FLOAT){
        sprintf(arg0, "%f(float)", node->arg0.f_value);
    }
    else if(node->arg0Type == VAR_CHAR){
        sprintf(arg0, "%c(char)", node->arg0.c_value);
    }
    else if(node->arg0Type == VAR_STRING){
        sprintf(arg0, "%s(string)", node->arg0.s_value);
    }
    else if(node->arg0Type == VAR_REG){
        sprintf(arg0, "%d(reg)", node->arg0.reg);
    }
    else if(node->arg0Type == VAR_TARGET){
        sprintf(arg0, "%s(target)", node->arg0.target);
    }
    else{
        sprintf(arg0, "(none)");
    }

    char *arg1 = malloc(sizeof(char) * 128);
    if(node->arg1Type == VAR_INT){
        sprintf(arg1, "%d(int)", node->arg1.i_value);
    }
    else if(node->arg1Type == VAR_FLOAT){
        sprintf(arg1, "%f(float)", node->arg1.f_value);
    }
    else if(node->arg1Type == VAR_CHAR){
        sprintf(arg1, "%c(char)", node->arg1.c_value);
    }
    else if(node->arg1Type == VAR_STRING){
        sprintf(arg1, "%s(string)", node->arg1.s_value);
    }
    else if(node->arg1Type == VAR_REG){
        sprintf(arg1, "%d(reg)", node->arg1.reg);
    }
    else if(node->arg1Type == VAR_TARGET){
        sprintf(arg1, "%s(target)", node->arg1.target);
    }
    else{
        sprintf(arg1, "(none)");
    }

    char *args = malloc(sizeof(char) * 256);
    sprintf(args, "%s, %s", arg0, arg1);

    return args;
}

char *printOPKind(enum opKind op){
    switch(op){
        case OP_ADD:
            return "ADD";
        case OP_SUB:
            return "SUB";
        case OP_MUL:
            return "MUL";
        case OP_DIV:
            return "DIV";
        case OP_MOD:
            return "MOD";
        case OP_R_SHIFT:
            return "R_SHIFT";
        case OP_L_SHIFT:
            return "L_SHIFT";
        case OP_B_AND:
            return "B_AND";
        case OP_B_OR:
            return "B_OR";
        case OP_B_XOR:  
            return "B_XOR";
        case OP_B_NOT:
            return "B_NOT";
        case OP_B_NEG:
            return "B_NEG";
        case OP_INC:
            return "INC";
        case OP_DEC:
            return "DEC";
        default:
            fprintf(stderr, "Invalid operation\n");
            exit(EXIT_FAILURE);
    }
}

char *printACTKind(enum actKind act){
    switch(act){
        case ACT_MOV:
            return "MOV";
        case ACT_GOTO:
            return "GOTO";
        case ACT_CALL:
            return "CALL";
        case ACT_RET:
            return "RET";
        case ACT_CLOK:
            return "CLOK";
        case ACT_DRAW:
            return "DRAW";
        case ACT_CMP:
            return "DRAW";
        case ACT_EXIT:
            return "EXIT";
        case ACT_PUSH:
            return "PUSH";
        case ACT_POP:
            return "POP";
        case ACT_PUSH_A:
            return "PUSH_A";
        case ACT_POP_A:
            return "POP_A";
        case ACT_OB1:
            return "OB1";
        default:
            fprintf(stderr, "Invalid action\n");
            exit(EXIT_FAILURE);
    }
}

char* printCMP(instNode_t *node){
    char *cmp = malloc(sizeof(char) * 128);
    if(node->nodeType.act->cmp->statem == CMP_IF){
        sprintf(cmp, "IF");
    }
    else if(node->nodeType.act->cmp->statem == CMP_ELSE){
        sprintf(cmp, "ELSE");
    }
    else if(node->nodeType.act->cmp->statem == CMP_END){
        sprintf(cmp, "END");
    }
    else{
        fprintf(stderr, "Invalid comparison\n");
        exit(EXIT_FAILURE);
    }
    sprintf(cmp, "%s %s", cmp, printCMPKind(node->nodeType.act->cmp->cmp));
    return cmp;
}

char *printCMPKind(enum cmpKind cmp){
    switch(cmp){
        case CMP_OR:
            return "OR";
        case CMP_AND:
            return "AND";
        case CMP_NOT:
            return "NOT";
        case CMP_XOR:
            return "XOR";
        case CMP_LT:
            return "LT";
        case CMP_GT:
            return "GT";
        case CMP_LTE:
            return "LTE";
        case CMP_GTE:
            return "GTE";
        case CMP_EQ:
            return "EQ";
        case CMP_NEQ:
            return "NEQ";
        default:
            fprintf(stderr, "Invalid comparison\n");
            exit(EXIT_FAILURE);
    }

}

void printVarList(varList_t *list, char *dest){
    FILE *file = fopen(dest, "a");
    if(file == NULL){
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    for(size_t i = 0; i < list->size; i++){
        if(list->list[i].name == NULL){
            continue;
        }
        switch(list->list[i].type){
            case VAR_INT:
                fprintf(file, "%s: %d(INT)\n", list->list[i].name, list->list[i].value.i_value);
                break;
            case VAR_FLOAT:
                fprintf(file, "%s: %f(FLOAT)\n", list->list[i].name, list->list[i].value.f_value);
                break;
            case VAR_CHAR:
                fprintf(file, "%s: %c(CHAR)\n", list->list[i].name, list->list[i].value.c_value);
                break;
            case VAR_STRING:
                fprintf(file, "%s: %s(STRING)\n", list->list[i].name, list->list[i].value.s_value);
                break;
            default:
                fprintf(stderr, "Invalid variable type\n");
                exit(EXIT_FAILURE);
        }
    }
    
    fclose(file);
}

void printLabelList(labelList_t *list, char *dest){
    FILE *file = fopen(dest, "a");
    if(file == NULL){
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "\n\nLABELS:\n");
    for(size_t i = 0; i < list->size; i++){
        if(list->list[i].name == NULL){
            continue;
        }
        fprintf(file, "(NAME): %s, (ID)%ld, (NODE ID): %ld\n", list->list[i].name, list->list[i].id, list->list[i].nodeId);
    }
    fclose(file);
}

void build(instList_t *nodeList, labelList_t *labelList){
    // read the list of instructions
    instNode_t *currNode = nodeList->head;
    while (currNode != NULL)
    {
        // Check if node is an operation
        // Build operation

        // Check if node is an action
         if(currNode->inst == INST_ACT){
            buildActNode(currNode, labelList);
        }

        // Check if node is a label
        if(currNode->inst == INST_LABEL){
            buildLabelNode(currNode, labelList);
        }

        currNode = currNode->next;
    }
    
}

void buildOpNode(instNode_t *node){
}

void buildActNode(instNode_t *node, labelList_t *labelList){

}

void buildLabelNode(instNode_t *node, labelList_t *labelList){
    // Check if label is already in the list
    for(size_t i = 0; i < labelList->size; i++){
        if(labelList->list[i].name == NULL){
            continue;
        }
        else if(strcmp(labelList->list[i].name, node->arg0.target) == 0){
            fprintf(stderr, "Label %s already declared\n", node->arg0.target);
            exit(EXIT_FAILURE);
        }
    }
    // Add label to the list
    addLabel(labelList, node->arg0.target, node->id);
}

void addLabel(labelList_t *list, char *name, long nodeId){
    // Check if list is full
    bool full = true;
    for(size_t i = 0; i < list->size; i++){
        if(list->list[i].name == NULL){
            full = false;
            break;
        }
    }
    if(full){
        // Increase list size
        incLabelList(list);
    }

    // Add label to the list
    for(size_t i = 0; i < list->size; i++){
        if(list->list[i].name == NULL){
            list->list[i].name = name;
            list->list[i].nodeId = nodeId;
            list->list[i].id = (long)i;
            break;
        }
    }
}

void incLabelList(labelList_t *list){
    // Increase list size
    list->size *= 2;
    list->list = (label_t *)realloc(list->list, sizeof(label_t) * list->size);
    if(list->list == NULL){
        fprintf(stderr, "Error reallocating memory\n");
        exit(EXIT_FAILURE);
    }

    // Init new memory
    for(size_t i = list->size / 2; i < list->size; i++){
        list->list[i].name = NULL;
    }
}