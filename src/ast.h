/*
    This file contain the Abstract Syntax Tree structure
*/

#pragma once

// Variables types
enum varKind{
    VAR_INT,
    VAR_FLOAT,
    VAR_CHAR,
    VAR_STRING,
    VAR_REG,
    VAR_TARGET,
    VAR_CMP,
    VAR_NONE
};

// Instruction types
enum instKind{
    INST_OP,
    INST_ACT,
    INST_LABEL,
    INST_VAR
};

// Operation types
enum opKind{
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_R_SHIFT,
    OP_L_SHIFT,
    OP_B_AND,
    OP_B_OR,
    OP_B_XOR,
    OP_B_NOT,
    OP_B_NEG,
    OP_INC,
    OP_DEC
};

// Action types
enum actKind{
    ACT_MOV,
    ACT_GOTO,
    ACT_CALL,
    ACT_RET,
    ACT_CLOK,
    ACT_DRAW,
    ACT_CMP,
    ACT_EXIT,
    ACT_PUSH,
    ACT_POP,
    ACT_PUSH_A,
    ACT_POP_A,
    ACT_OB1
};

// comparison statements
enum cmpStatem{
    CMP_IF,
    CMP_ELSE,
    CMP_END
};

// Comparison types
enum cmpKind{
    CMP_OR,
    CMP_AND,
    CMP_NOT,
    CMP_XOR,
    CMP_LT, // less than
    CMP_GT, // greater than
    CMP_LTE, // less than or equal
    CMP_GTE, // greater than or equal
    CMP_EQ,
    CMP_NEQ // not equal
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

// Structs for operations nodes
typedef struct opNode{
    enum opKind op;
} opNode_t;

// Structs for comparison nodes
typedef struct cmpNode{
    enum cmpStatem statem;
    enum cmpKind cmp;
    long elseId;
    long endId;
} cmpNode_t;

// Structs for action nodes
typedef struct actNode{
    enum actKind act;
    cmpNode_t *cmp;
} actNode_t;

// Structs for instruction nodes
typedef struct instNode{
    long id;
    long lineNb;
    enum instKind inst;
    union{
        opNode_t *op;
        actNode_t *act;
        char *label;
    } nodeType;
    struct instNode *next;
    enum varKind arg0Type;
    union{
        int i_value;
        float f_value;
        char c_value;
        char * s_value;
        enum regKind reg;
        char * target; // to target variable or label
        }arg0;
    enum varKind arg1Type;
    union{
        int i_value;
        float f_value;
        char c_value;
        char * s_value;
        enum regKind reg;
        char * target;
        }arg1;
    enum regKind targetReg;
} instNode_t;

// Structs for instruction list
typedef struct instList{
    instNode_t *head;
} instList_t;

// Struct for register
typedef struct reg{
    enum regKind name;
    enum varKind type;
    union{
        int i_value;
        float f_value;
        char c_value;
        char * s_value;
        }value;
} reg_t;

// Structs for variable storage
typedef struct var{
    char *name;
    enum varKind type;
    union{
        int i_value;
        float f_value;
        char c_value;
        char * s_value;
        }value;
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