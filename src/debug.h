#pragma once

#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    Print ast nodes data
    params:
        nodeList: pointer to the instruction list
*/
void printAst(instList_t *nodeList);

/*
    Print the node data
    params:
        node: pointer to the instruction node
*/
void printNodeData(instNode_t *node);

/*
    Return text corresponding to instruction kind
    params:
        kind: instruction kind
    returns:
        char*: text corresponding to instruction kind
*/
char *getOpName(enum opKind kind);

/*
    Return text corresponding to interrupt kind
    params:
        kind: interrupt kind
    returns:
        char*: text corresponding to interrupt kind
*/
char *getInterName(enum interruptKind kind);

#ifdef __cplusplus
}
#endif