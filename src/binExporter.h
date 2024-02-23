#include <stdio.h>
#include "ast.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    Export the AST to a binary file
    params:
        nodeList: pointer to the instruction list
        filename: name of the file
        errData: pointer to the error struct    
*/
void exportToBin(instList_t *nodeList, char *filename, asm_error_t *errData);

/*
    Convert an operation to its binary code
    params:
        op: operation to convert
    returns:
        binary code of the operation
*/
char *opToBinCode(enum opKind op);

/*
    Convert a register to its binary code
    params:
        reg: register to convert
    returns:
        binary code of the register
*/
char *regToBinCode(enum regKind reg);

/*
    Convert an interrupt to its binary code
    params:
        inter: interrupt to convert
    returns:
        binary code of the interrupt
*/
char *interToBinCode(enum interruptKind inter);

/*
    Convert a string to its binary code
    params:
        s: string to convert
        errData: pointer to the error struct
    returns:
        binary code of the string

*/
char *stringToBinary(char *s, asm_error_t *errData);
#ifdef __cplusplus
}
#endif
