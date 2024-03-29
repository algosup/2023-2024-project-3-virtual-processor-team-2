#include "ast.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    Build the program
    params:
        nodeList: pointer to the instruction list
        varList: pointer to the variable list
        labeList: pointer to the label list
        errData: pointer to the error struct
*/
void buildProgram(instList_t *nodeList, varList_t *varList, labelList_t *labeList, asm_error_t *errData);

/*
    Build a node
    params:
        node: pointer to the instruction node
        varList: pointer to the variable list
        labeList: pointer to the label list
        errData: pointer to the error struct
*/
void buildNode(instNode_t *node, varList_t *varList, labelList_t *labeList, asm_error_t *errData);

/*
    Build a variable
    params:
        node: pointer to the instruction node
        varList: pointer to the variable list
        errData: pointer to the error struct
*/
void buildVar(instNode_t *node, varList_t *varList, asm_error_t *errData);

/*
    Build a label
    params:
        node: pointer to the instruction node
        labelList: pointer to the label list
        errData: pointer to the error struct
*/
void buildLabel(instNode_t *node, labelList_t *labelList, asm_error_t *errData);

/*
    Build a mov instruction
    params:
        node: pointer to the instruction node
        varList: pointer to the variable list
        errData: pointer to the error struct
*/
void buildMov(instNode_t *node, varList_t *varList, asm_error_t *errData);

/*
    Build a goto instruction
    params:
        node: pointer to the instruction node
        labelList: pointer to the label list
        errData: pointer to the error struct
*/
void buildGoto(instNode_t *node, labelList_t *labelList, asm_error_t *errData);

/*
    Build a call instruction
    params:
        node: pointer to the instruction node
        labelList: pointer to the label list
        errData: pointer to the error struct
*/
void buildCall(instNode_t *node, labelList_t *labelList, asm_error_t *errData);

/*
    Build an operation (add, xor, etc.)
    params:
        node: pointer to the instruction node
        varList: pointer to the variable list
        errData: pointer to the error struct
*/
void buildOperation(instNode_t *node, varList_t *varList, asm_error_t *errData);

/*
    Get the register kind
    params:
        str: string to be checked
        lineNb: line number
        errData: pointer to the error struct
    returns:
        regKind: kind of the register
*/
enum regKind getRegKind(char *str, long lineNb, asm_error_t *errData);

/*
    Get the data size of a variable in bytes
    params:
        str: string to be checked
    returns:
        int: data size
*/
int getVarDatasize(char *str);

/*
    build interrupt operation
    params:
        node: pointer to the instruction node
        errData: pointer to the error struct
    returns:
        bool: true if the operation was built
*/
bool buildIntOpe(instNode_t *node, asm_error_t *errData);

#ifdef __cplusplus
}
#endif