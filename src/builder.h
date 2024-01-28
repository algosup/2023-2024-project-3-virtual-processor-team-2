// Variables types
enum varKind{
    VAR_INT,
    VAR_FLOAT,
    VAR_CHAR,
    VAR_STRING,
    VAR_REG,
    VAR_TARGET,
};

// Instruction types
enum instKind{
    INST_OP,
    INST_ACT,
    INST_LABEL,
    INST_CMP,
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
    ACT_IF,
    ACT_ELSE,
    ACT_EXIT,
    ACT_PUSH,
    ACT_POP,
    ACT_PUSH_A,
    ACT_POP_A,
    ACT_OB1
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
    Read nodes from the instruction list and build the program
    params:
        nodeList: pointer to the instruction list
        labelList: pointer to the label list    
*/
void build(instList_t *nodeList, labelList_t *labelList);