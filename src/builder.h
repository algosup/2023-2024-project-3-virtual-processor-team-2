#include "ast.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    Build the program
    params:
        nodeList: pointer to the instruction list
        errData: pointer to the error struct
*/
void buildProgram(instList_t *nodeList, error_t *errData);

/*
    Build a node
    params:
        node: pointer to the instruction node
        errData: pointer to the error struct
*/
void buildNode(instNode_t *node, error_t *errData);

/*
    Build a mov instruction
    params:
        node: pointer to the instruction node
        errData: pointer to the error struct
*/
void buildMov(instNode_t *node, error_t *errData);

/*
    Copy an instruction node
    params:
        node: pointer to the instruction node
    returns:
        instNode_t: copy of the instruction node
*/
instNode_t *copyInstNode(instNode_t *node);

/*
    Check if the string is an unsigned int
    params:
        str: string to be checked
*/
bool isUnsignedInt(char *str);

/*
    Check if the string is a register
    params:
        str: string to be checked
*/
bool isFromReg(char *str);

/*
    Get the register kind
    params:
        str: string to be checked
    returns:
        regKind: kind of the register
*/
enum regKind getRegKind(char *str);

#ifdef __cplusplus
}
#endif