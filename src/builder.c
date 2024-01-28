#include <stdio.h>
#include <stdlib.h>

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
                fprintf(file, "%ld(ACT): %s %s\n", node->id, printACTKind(node->nodeType.act->act), printArgs(node));
                break;
            case INST_LABEL:
                fprintf(file, "%ld(LAB): %s:\n", node->id, node->nodeType.label);
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
        fprintf(stderr, "Invalid argument type\n");
        exit(EXIT_FAILURE);
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
        fprintf(stderr, "Invalid argument type\n");
        exit(EXIT_FAILURE);
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
        case ACT_IF:
            return "IF";
        case ACT_ELSE:
            return "ELSE";
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

void build(instList_t *nodeList, labelList_t *labelList){
    // TODO: make the function build
}