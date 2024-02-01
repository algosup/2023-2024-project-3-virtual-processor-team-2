/*
    This file is the builder of the project
    It will read the instruction list and build the program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "builder.h"

void build(instList_t *nodeList, labelList_t *labelList){
    // read the list of instructions
    instNode_t *currNode = nodeList->head;
    while (currNode != NULL)
    {
        // Check if node is an operation
        // Build operation

        // Check if node is an action
         if(currNode->inst == INST_ACT){
            buildActNode(currNode);
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

void buildActNode(instNode_t *node){
    // Check if it's a comparison
    if(node->nodeType.act->act == ACT_CMP){
        // set comparison goto
    }

}

void buildCmpNode(instNode_t *node){
    // copy the current node
    instNode_t *currNode = node;

    // Search for the next else or end
    while(currNode != NULL){
        if(currNode->inst == INST_ACT){
            if(currNode->nodeType.act->act == ACT_CMP){
                if(currNode->nodeType.act->cmp->statem == CMP_ELSE || currNode->nodeType.act->cmp->statem == CMP_END){
                    break;
                }
            }
        }
        currNode = currNode->next;
    }

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