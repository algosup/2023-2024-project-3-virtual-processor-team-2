/*
    This file is the builder of the project
    It will read the instruction list and build the program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "builder.h"

void build(instList_t *nodeList, labelList_t *labelList, varList_t *varList){
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
    instNode_t *prevNode = NULL;
    while (currNode != NULL)
    {
        // Check if node is an action
         if(currNode->inst == INST_ACT){
            buildActNode(currNode, lifoCmpNode);
        }

        // Check if node is a label
        if(currNode->inst == INST_LABEL){
            buildLabelNode(currNode, labelList);
        }

        // Check if node is a variable declaration
        if(currNode->inst == INST_VAR){
            addVar(varList, currNode);
            // remove var declaration from list
            if(prevNode == NULL){
                nodeList->head = currNode->next;
            }
            else{
                prevNode->next = currNode->next;
            }
        }

        prevNode = currNode;
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

labelList_t* initLabelList(){
    labelList_t *labelList = malloc(sizeof(labelList_t));
    labelList->size = 10;
    labelList->list = malloc(sizeof(label_t) * labelList->size);
    for(size_t i = 0; i < labelList->size; i++){
        labelList->list[i].name = NULL;
        labelList->list[i].nodeId = -1;
        labelList->list[i].id = -1;
    }
    return labelList;
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

void addVar(varList_t *list, instNode_t *node){
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
        incVarList(list);
    }

    // Add var to the list
    for(size_t i = 0; i < list->size; i++){
        if(list->list[i].name == NULL){
            list->list[i].name = node->arg0.target;
            list->list[i].type = node->arg1Type;
            switch (node->arg1Type)
            {
            case VAR_INT:
                list->list[i].value.i_value = node->arg1.i_value;
                break;
            case VAR_FLOAT:
                list->list[i].value.f_value = node->arg1.f_value;
                break;
            case VAR_CHAR:
                list->list[i].value.c_value = node->arg1.c_value;
                break;
            case VAR_STRING:
                list->list[i].value.s_value = node->arg1.s_value;
                break;
            default:
                fprintf(stderr, "Error: Unknown variable type\n");
                exit(EXIT_FAILURE);
                break;
            }
            break;
        }
        else if(strcmp(list->list[i].name, node->arg0.target) == 0){
            fprintf(stderr, "Variable %s already declared\n", node->arg0.target);
            exit(EXIT_FAILURE);
        }
    }
}

void incVarList(varList_t *list){
    // Increase list size
    list->size *= 2;
    list->list = (var_t *)realloc(list->list, sizeof(var_t) * list->size);
    if(list->list == NULL){
        fprintf(stderr, "Error reallocating memory\n");
        exit(EXIT_FAILURE);
    }

    // Init new memory
    for(size_t i = list->size / 2; i < list->size; i++){
        list->list[i].name = NULL;
    }
}

varList_t *initVarList(){
    varList_t* varList = malloc(sizeof(varList_t));
    varList->size = 10;
    varList->list = malloc(sizeof(var_t) * varList->size);
    // Init variables list
    for(size_t i = 0; i < varList->size; i++){
        varList->list[i].name = NULL;
    }
    return varList;
}