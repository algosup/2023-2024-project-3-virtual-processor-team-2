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
    // init lifo for if/else statements
    lifoCmpNode_t *lifoCmpNode = (lifoCmpNode_t *)malloc(sizeof(lifoCmpNode_t));
    if(lifoCmpNode == NULL){
        fprintf(stderr, "Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    lifoCmpNode->list = NULL;
    lifoCmpNode->size = 0;

    // read the list of instructions
    instNode_t *currNode = nodeList->head;
    while (currNode != NULL)
    {
        // Check if node is an operation
        // Build operation

        // Check if node is an action
         if(currNode->inst == INST_ACT){
            buildActNode(currNode, lifoCmpNode);
        }

        // Check if node is a label
        if(currNode->inst == INST_LABEL){
            buildLabelNode(currNode, labelList);
        }

        currNode = currNode->next;
    }

    // Check if lifo is empty
    if(lifoCmpNode->size != 0){
        fprintf(stderr, "Error: Comparison Lifo is not empty\n");
        exit(EXIT_FAILURE);
    }
    
}

void buildActNode(instNode_t *node, lifoCmpNode_t *lifo){
    // Check if it's a comparison
    if(node->nodeType.act->act == ACT_CMP){
        buildCmpNode(node, lifo);
    }

}

void buildCmpNode(instNode_t *node, lifoCmpNode_t *lifo){
    // Check kind of statement
    switch (node->nodeType.act->cmp->statem)
    {
    case CMP_IF:
        // add to lifo
        pushCmpLifo(lifo, node->nodeType.act->cmp);
        break;
    case CMP_ELSE:
        // set else goto
        lifo->list[0]->elseId = node->id;
        break;
    case CMP_END:
        // set end goto
        lifo->list[0]->endId = node->id;
        // remove from lifo
        popCmpLifo(lifo);
        break;
    default:
        fprintf(stderr, "Error: Unknown comparison statement\n");
        exit(EXIT_FAILURE);
        break;
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

void pushCmpLifo(lifoCmpNode_t *lifo, cmpNode_t *node){
    // resize lifo to add new node
    lifo->size++;
    // realloc lifo with node as new head
    cmpNode_t **newLifo = (cmpNode_t **)malloc(sizeof(cmpNode_t *) * lifo->size);
    if(newLifo == NULL){
        fprintf(stderr, "Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    newLifo[0] = node;
    for(size_t i = 1; i < lifo->size; i++){
        newLifo[i] = lifo->list[i - 1];
    }
    free(lifo->list);
    lifo->list = newLifo;
}

cmpNode_t *popCmpLifo(lifoCmpNode_t *lifo){
    // Check if lifo is empty
    if(lifo->size == 0){
        fprintf(stderr, "Error: Lifo is empty\n");
        exit(EXIT_FAILURE);
    }

    // resize lifo to remove node
    lifo->size--;
    // realloc lifo without node as new head
    cmpNode_t **newLifo = (cmpNode_t **)malloc(sizeof(cmpNode_t *) * lifo->size);
    if(newLifo == NULL){
        fprintf(stderr, "Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    cmpNode_t *node = lifo->list[0];
    for(size_t i = 0; i < lifo->size; i++){
        newLifo[i] = lifo->list[i + 1];
    }
    free(lifo->list);
    lifo->list = newLifo;

    return node;
}