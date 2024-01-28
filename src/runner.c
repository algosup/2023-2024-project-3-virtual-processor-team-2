#include <stdio.h>
#include <stdlib.h>

#include "runner.h"

void nodeReader(instList_t *nodeList, varList_t *varList, labelList_t *labelList){
    instNode_t *node = nodeList->head;
    while(node != NULL){
        runNode(node, varList, labelList);
        node = node->next;
    }
}

void runNode(instNode_t *node, varList_t *varList, labelList_t *labelList){
    switch(node->inst){
        case INST_OP:
            runOpNode(node, varList, labelList);
            break;
        case INST_ACT:
            runActNode(node, varList, labelList);
            break;
        case INST_LABEL:
            runLabelNode(node, labelList);
            break;
        default:
            fprintf(stderr, "Invalid instruction\n");
            exit(EXIT_FAILURE);
    }
}

void runOpNode(instNode_t *node, varList_t *varList, labelList_t *labelList){
    switch(node->nodeType.op->op){
        case OP_ADD:
            opAdd(node, varList);
            break;
        case OP_SUB:
            break;
        case OP_MUL:
            break;
        case OP_DIV:
            break;
        case OP_MOD:
            break;
        default:
            fprintf(stderr, "Invalid operation\n");
            exit(EXIT_FAILURE);
    }
}

void runActNode(instNode_t *node, varList_t *varList, labelList_t *labelList){
    // TODO: implement
}

void runLabelNode(instNode_t *node, labelList_t *labelList){
    // TODO: implement
}

void opAdd(instNode_t *node, varList_t *varList){
    // TODO: implement
}

// TODO: implement other operations (sub, mul, div, mod, rshift, lshift, and, or, xor, not, neg, inc, dec)

// TODO: implement actions (mov, goto, draw, call, ret, push, pop, pusha, popa, ngr, ob1, clok, if, else)