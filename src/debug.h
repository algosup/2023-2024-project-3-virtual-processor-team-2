#pragma once

#include "ast.h"

/*
    Print the instruction list to a file
    params:
        list: pointer to the instruction list
        dest: destination file
*/
void printInstList(instList_t *list, char *dest);

/*
    Print arguments of an instruction node
    params:
        node: pointer to the instruction node
    returns:
        char*: string with the arguments
*/
char *printArgs(instNode_t *node);

/*
    Print the kind of an operation
    params:
        op: operation kind
    returns:
        char*: string with the operation kind
*/
char *printOPKind(enum opKind op);

/*
    Print the kind of an action
    params:
        act: action kind
    returns:
        char*: string with the action kind
*/
char *printACTKind(enum actKind act);

/*
    Print details of comparison node
    params:
        node: pointer to the instruction node
    returns:
        char*: string with the comparison details
*/
char* printCMP(instNode_t *node);

/*
    Print the kind of a comparison
    params:
        cmp: comparison kind
    returns:
        char*: string with the comparison kind
*/
char *printCMPKind(enum cmpKind cmp);

/*
    Print variable list to a file
    params:
        list: pointer to the variable list
        dest: destination file
*/
void printVarList(varList_t *list, char *dest);

/*
    Print label list to a file
    params:
        list: pointer to the label list
        dest: destination file
*/
void printLabelList(labelList_t *list, char *dest);