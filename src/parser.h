#include <stdio.h>
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
    Checks if the filename ends by .aop or trows an error
    params:
        filename: name of the file to check
*/
void checkAOPFile(char* fileName);

/*
    Checks if a line has more than 64 characters or not
    params:
        line: line to check
        fp: file pointer
*/
bool checkLineSize(char* line, FILE *fp);