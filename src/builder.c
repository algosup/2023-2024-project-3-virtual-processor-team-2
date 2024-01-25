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
                fprintf(file, "%ld: %d %s %s\n", node->id, node->nodeType.op->op, node->arg0, node->arg1);
                break;
            case INST_ACT:
                fprintf(file, "%ld: %d %s\n", node->id, node->nodeType.act->act, node->arg0);
                break;
            case INST_LABEL:
                fprintf(file, "%ld: %s:\n", node->id, node->nodeType.label);
                break;
            default:
                fprintf(stderr, "Invalid instruction\n");
                exit(EXIT_FAILURE);
        }
        node = node->next;
    }
    fclose(file);
}