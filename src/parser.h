#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

// Program flags struct
typedef struct {
    bool verbose;
    bool debug;
    bool help;
    bool version;
} flags_t;

/* 
    Parse the program arguments
    params:
        argc: number of arguments
        argv: array of arguments
        errData: error history
    returns:
        flags_t: struct with the flags
*/ 
flags_t parseArgs(int argc, char *argv[], asm_error_t *errData);

/*
    Read the flag and set the flag struct
    params:
        flag: flag to be read
        flags: pointer to the flags struct
        errData: error history
*/
void flagsSet(char *flag, flags_t *flags, asm_error_t *errData);

/*
    Read the file and parse it line by line
    params:
        nodeList: pointer to the instruction list
        filename: name of the file to be parsed
*/
void parseFile(instList_t *nodeList, char *filename, varList_t *varList, asm_error_t *errData);

/*
    Parse a line and return an instruction node
    params:
        line: line to be parsed
        nodeId: id of the node
        lineNb: number of the line
        varList: variable list
        errData: error history
    returns:
        instNode_t: instruction node
*/
instNode_t *parseLine(char *line, long nodeId, long lineNb, varList_t *varList, asm_error_t *errData);

/*
    Read the line and check if it is an operation
    params:
        char*: instruction to be checked
        instNode_t*: pointer to the instruction node
        varList_t: variable list
        error_t*: error history
    returns:
        bool: true if it is an operation
*/
bool isOp(char *inst, instNode_t *newNode, varList_t *varList, asm_error_t *errData);


/*
    Get instruction from line
    params:
        line: line to be parsed
    returns:
        char*: instruction
*/
char* getInst(char *line, long lineNb, asm_error_t *errData);

/*
    Get arguments from an instruction line
    params:
        line: line to be parsed
        lineNb: number of the line
        errData: error history
    returns:
        char**: array of strings (no more than 2)
*/
char **getInstArgs(char *line, long lineNb, asm_error_t *errData);
/*
    Set the arguments of an instruction node
    params:
        node: pointer to the instruction node
        args: array of strings (no more than 2)
*/
void setArgs(instNode_t *node, char **args);

/*
    Check if the argument is a register
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a register
*/
bool isReg(char *arg);

/*
    Convert a string to a register
    params:
        arg: string to be converted
    returns:
        regKind: register
*/
enum regKind strToReg(char *arg);

/*
    Checks if the filename ends by .aop or trows an error
    params:
        filename: name of the file to check
        errData: error history
*/
void checkAOPFile(char* fileName, asm_error_t *errData);
  
/*
    Checks if a line has more than 64 characters or not
    params:
        line: line to check
        fp: file pointer
*/
bool checkLineSize(char* line, FILE *fp);

#ifdef __cplusplus
}
#endif
