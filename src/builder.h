// Variables types
enum varKind{
    VAR_INT,
    VAR_U_INT,
    VAR_FLOAT,
    VAR_CHAR,
    VAR_U_CHAR,
    VAR_STRING,
};

// Instruction types
enum instKind{
    INST_OP,
    INST_ACT,
    INST_LABEL,
    INST_CMP,
    INST_VAR,
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
    OP_B_NOT
};

// Action types
enum actKind{
    ACT_PRINT,
    ACT_RET,
    ACT_IF,
    ACT_ELSE,
    ACT_MOV,
    ACT_R_CLK,
    ACT_EXIT
};

// Comparison types
enum cmpKind{
    CMP_OR,
    CMP_AND,
    CMP_NOT,
    CMP_XOR,
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
    RG_7,
};

// Structs for operations nodes
typedef struct opNode{
    enum opKind op;
} opNode_t;

// Structs for comparison nodes
typedef struct cmpNode{
    enum cmpKind cmp;
} cmpNode_t;

// Structs for action nodes
typedef struct actNode{
    enum actKind act;
    cmpNode_t *cmp;
} actNode_t;

// Structs for instruction nodes
typedef struct instNode{
    long id;
    enum instKind inst;
    union{
        opNode_t *op;
        actNode_t *act;
        char *label;
    } nodeType;
    struct instNode *next;
    char *arg0;
    char *arg1;
    enum regKind targetReg;
} instNode_t;

// Structs for instruction list
typedef struct instList{
    instNode_t *head;
} instList_t;

// Structs for variable storage
typedef struct var{
    char *name;
    enum varKind type;
    union{
        int i_value;
        unsigned int u_i_value;
        float f_value;
        char c_value;
        unsigned char u_c_value;
        char * s_value;
        }value;
} var_t;

// Structs for variable list
typedef struct varList{
    var_t *list;
} varList_t;

// Structs for label storage
typedef struct label{
    char *name;
    long node_id;
    long id;
} label_t;

// Structs for label list
typedef struct labelList{
    label_t *list;
} labelList_t;

/*
    Print the instruction list to a file
    params:
        list: pointer to the instruction list
        dest: destination file
*/
void printInstList(instList_t *list, char *dest);
