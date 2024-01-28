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
                fprintf(file, "%ld: %d %s\n", node->id, node->nodeType.op->op, printArgs(node));
                break;
            case INST_ACT:
                fprintf(file, "%ld: %d %s\n", node->id, node->nodeType.act->act, printArgs(node));
                break;
            case INST_LABEL:
                fprintf(file, "%ld: %s:\n", node->id, node->nodeType.label);
                break;
            case INST_VAR:
                fprintf(file, "%ld: %s\n", node->id, printArgs(node));
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
        sprintf(arg0, "%d", node->arg0.i_value);
    }
    else if(node->arg0Type == VAR_FLOAT){
        sprintf(arg0, "%f", node->arg0.f_value);
    }
    else if(node->arg0Type == VAR_CHAR){
        sprintf(arg0, "%c", node->arg0.c_value);
    }
    else if(node->arg0Type == VAR_STRING){
        sprintf(arg0, "%s", node->arg0.s_value);
    }
    else if(node->arg0Type == VAR_REG){
        sprintf(arg0, "%d", node->arg0.reg);
    }
    else if(node->arg0Type == VAR_TARGET){
        sprintf(arg0, "%s", node->arg0.target);
    }
    else{
        fprintf(stderr, "Invalid argument type\n");
        exit(EXIT_FAILURE);
    }

    char *arg1 = malloc(sizeof(char) * 128);
    if(node->arg1Type == VAR_INT){
        sprintf(arg1, "%d", node->arg1.i_value);
    }
    else if(node->arg1Type == VAR_FLOAT){
        sprintf(arg1, "%f", node->arg1.f_value);
    }
    else if(node->arg1Type == VAR_CHAR){
        sprintf(arg1, "%c", node->arg1.c_value);
    }
    else if(node->arg1Type == VAR_STRING){
        sprintf(arg1, "%s", node->arg1.s_value);
    }
    else if(node->arg1Type == VAR_REG){
        sprintf(arg1, "%d", node->arg1.reg);
    }
    else if(node->arg1Type == VAR_TARGET){
        sprintf(arg1, "%s", node->arg1.target);
    }
    else{
        fprintf(stderr, "Invalid argument type\n");
        exit(EXIT_FAILURE);
    }

    char *args = malloc(sizeof(char) * 256);
    sprintf(args, "%s, %s", arg0, arg1);

    return args;
}

// void build(instList_t *nodeList, labelList_t *labelList){
//     instNode_t *currNode = nodeList->head;
//     while(currNode != NULL){
//         switch(currNode->inst){
//             case INST_OP:
//                 buildOpNode(currNode, labelList);
//                 break;
//             case INST_ACT:
//                 buildActNode(currNode, labelList);
//                 break;
//             case INST_LABEL:
//                 buildLabelNode(currNode, labelList);
//                 break;
//             case INST_VAR:
//                 buildVarNode(currNode, labelList);
//                 break;
//             default:
//                 fprintf(stderr, "Error building instruction\n");
//                 exit(EXIT_FAILURE);
//         }
//         currNode = currNode->next;
//     }
// }