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
    }
}

void buildNode(instNode_t *node, error_t *errData) {
    switch(node->op){
        case OP_MOV:
            break;
        default:
            // TODO: transform to build error
            errorInstruction("unknown", node, NULL, errData);
            break;
    }
}