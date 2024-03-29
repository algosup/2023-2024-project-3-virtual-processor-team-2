/*
    This file contain the Abstract Syntax Tree structure
*/

#pragma once

#include "error.h"

#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

// Operation types
enum opKind{
    OP_MOV,
    OP_GOTO,
    OP_CALL,
    OP_INT,
    OP_PUSH,
    OP_POP,
    OP_B_XOR,
    OP_DIV,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_R_SHIFT,
    OP_L_SHIFT,
    OP_B_AND,
    OP_B_OR,
    OP_B_NOT,
    OP_MOD,
    OP_USE_REG,
    OP_USE_VAR,
    OP_LAB,
    OP_VAR,
    OP_RET,
    OP_MOV_F_VAR,
    OP_MOV_T_VAR,
    OP_VAR_SIZE,
    OP_VAR_DATA,
};

// interrupt types
enum interruptKind{
    INT_EXIT,
    INT_DRAW,
    INT_OB1,
    INT_LT,
    INT_LTE,
    INT_GT,
    INT_GTE,
    INT_EQ,
    INT_NEQ,
    INT_PUSHA,
    INT_POPA,
    INT_MOV_F_REG,
};

// Register names
enum regKind{
    RG_0,
    RG_1,
    RG_2,
    RG_3,
    RG_4,
    RG_5,
    RG_6,
    RG_7
};


// Structs for instruction nodes
typedef struct instNode{
    long id;
    long lineNb;
    enum opKind op;
    bool isInter;
    enum interruptKind inter;
    char * arg0;
    char * arg1;
    enum regKind inputReg;
    bool isBuilt;
    struct instNode *next;
} instNode_t;

// Structs for instruction list
typedef struct instList{
    instNode_t *head;
} instList_t;

// Structs for variable storage
typedef struct var{
    int id;
    int size;
    char *name;
    char * value;
} var_t;

// Structs for variable list
typedef struct varList{
    size_t size;
    var_t *list;
} varList_t;

// Structs for label storage
typedef struct label{
    char *name;
    long nodeId;
    long id;
} label_t;

// Structs for label list
typedef struct labelList{
    size_t size;
    label_t *list;
} labelList_t;

/*
    given a string, return the code of the interrupt
    params:
        kind: interrupt type
        errData: error history
    returns:
        char *: code of the interrupt
*/
char *getIntCode(enum interruptKind kind, asm_error_t *errData);

/*
    Create an empty variable list
    returns:
        varList_t: pointer to the variable list
*/
varList_t *createEmptyVarList();

/*
    Add a variable to the list
    params:
        varList: pointer to the variable list
        name: name of the variable
        value: value of the variable
        lineNb: number of the line
        errData: error history
    returns:
        bool: true if the variable was added
*/
bool addVar(varList_t *varList, char *name, char *value, long lineNb, asm_error_t *errData);


/*
    Check if a variable exists in the list
    params:
        varList: pointer to the variable list
        name: name of the variable
    returns:
        int: id of the variable or -1 if it does not exist
*/
int isVarExist(varList_t *varList, char *name);

/*
    Copy an instruction node
    params:
        node: pointer to the instruction node
        errData: error history
    returns:
        instNode_t: copy of the instruction node
*/
instNode_t *copyInstNode(instNode_t *node, asm_error_t *errData);

/*
    Create an empty instruction list
    returns:
        instList_t: pointer to the instruction list
*/
instList_t *createEmptyInstList();

/*
    Create an empty instruction node
    params:
        errData: error history
    returns:
        instNode_t: pointer to the instruction node
*/
instNode_t *createEmptyInstNode(asm_error_t *errData);

/*
    Create an empty label list
    returns:
        labelList_t: pointer to the label list
*/
labelList_t *createEmptyLabelList();

/*
    Add a label to the list
    params:
        labelList: pointer to the label list
        name: name of the label
        nodeId: id of the node
        lineNb: number of the line
        errData: error history
    returns:
        int: id of the label or -1 if it does not exist
*/
int addLabel(labelList_t *labelList, char *name, long nodeId, long lineNb, asm_error_t *errData);

/*
    Check if a label exists in the list
    params:
        labelList: pointer to the label list
        name: name of the label
    returns:
        int: id of the label or -1 if it does not exist
*/
int isLabelExist(labelList_t *labelList, char *name);

#ifdef __cplusplus
}
#endif