// Instruction types
enum instKind{
    INST_OP,
    INST_ACT,
    INST_LABEL,
    INST_CMP
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