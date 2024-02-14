/*
    This file contain the Abstract Syntax Tree structure
*/

#pragma once

#include <stdbool.h>

// Operation types
enum opKind{
    OP_MOV,
    OP_GOTO,
    OP_CALL,
    OP_INT,
    OP_PUSH,
    OP_B_XOR,
    OP_POP,
    OP_DIV,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_R_SHIFT,
    OP_L_SHIFT,
    OP_B_AND,
    OP_B_OR,
    OP_B_NOT,
    OP_INC,
    OP_DEC,
    OP_LAB,
    OP_VAR,
    OP_MOD,
    OP_RET,
};

// interrupt types
enum interruptKind{
    INT_EXIT,
    INT_DRAW,
    INT_OB1,
    INT_OR,
    INT_AND,
    INT_XOR,
    INT_LT,
    INT_LTE,
    INT_GT,
    INT_GTE,
    INT_EQ,
    INT_NEQ,
    INT_PUSHA,
    INT_POPA,
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
    struct instNode *next;
} instNode_t;

// Structs for instruction list
typedef struct instList{
    instNode_t *head;
} instList_t;

// Structs for variable storage
typedef struct var{
    char *name;
    char * value;
} var_t;

// Structs for variable list
typedef struct varList{
    char* name;
    long id;
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