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