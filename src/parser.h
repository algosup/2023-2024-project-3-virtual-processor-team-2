#include <stdbool.h>
#include "builder.h" // To get data structures from the builder

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
    returns:
        flags_t: struct with the flags
*/ 
flags_t parseArgs(int argc, char *argv[]);

/*
    Read the flag and set the flag struct
    params:
        flag: flag to be read
        flags: pointer to the flags struct
*/
void flagsSet(char *flag, flags_t *flags);

/*
    Read the file and parse it line by line
    params:
        nodeList: pointer to the instruction list
        filename: name of the file to be parsed
*/
void parseFile(instList_t *nodeList, char *filename);

/*
    Parse a line and return an instruction node
    params:
        line: line to be parsed
    returns:
        instNode_t: instruction node
*/
instNode_t *parseLine(char *line, long nodeId, long lineNb);

/*
    Read the line and check if it is an operation
    params:
        char*: instruction to be checked
        instNode_t*: pointer to the instruction node
    returns:
        bool: true if it is an operation
*/
bool isOp(char *inst, instNode_t *newNode);

/*
    Read the line and check if it is an action
    params:
        char*: instruction to be checked
        instNode_t*: pointer to the instruction node
    returns:
        bool: true if it is an action
*/
bool isAct(char *inst, instNode_t *newNode);

/*
    Read the line and check if it is a declaration for a label or a variable
    params:
        char*: instruction to be checked
        instNode_t*: pointer to the instruction node
    returns:
        bool: true if it is a label
*/
bool isDecla(char *inst, instNode_t *newNode);

/*
    Get instruction from line
    params:
        line: line to be parsed
    returns:
        char*: instruction
*/
char* getInst(char *line);

/*
    Get arguments from an instruction line
    params:
        line: line to be parsed
    returns:
        char**: array of strings (no more than 2)
*/
char** getInstArgs(char *line);

/*
    Set the arguments of an instruction node
    params:
        node: pointer to the instruction node
        args: array of strings (no more than 2)
*/
void setArgs(instNode_t *node, char **args);

/*
    Check if the argument is a number
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a number
*/
bool isInt(char *arg);

/*
    Check if the argument is a binary number
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a binary number
*/
bool isBinary(char *arg);

/*
    Check if the argument is a octal number
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a octal number
*/
bool isOctal(char *arg);

/*
    Check if the argument is a hexadecimal number
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a hexadecimal number
*/
bool isHex(char *arg);

/*
    Check if the argument is a float
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a float
*/
bool isFloat(char *arg);

/*
    Check if the argument is a char
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a char
*/
bool isChar(char *arg);

/*
    Check if the argument is a string
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a string
*/
bool isString(char *arg);

/*
    Check if the argument is a register
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a register
*/
bool isReg(char *arg);

/*
    Check if the argument is a variable or a label
    params:
        arg: argument to be checked
    returns:
        bool: true if it is a variable
*/
bool isTarget(char *arg);

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
*/
void checkAOPFile(char* fileName);