#pragma once

#include "ast.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    Print ast nodes data
    params:
        nodeList: pointer to the instruction list
        errData: pointer to the error struct
*/
void printAst(instList_t *nodeList, asm_error_t *errData);

/*
    Print the node data
    params:
        node: pointer to the instruction node
        errData: pointer to the error struct
*/
void printNodeData(instNode_t *node, asm_error_t *errData);

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