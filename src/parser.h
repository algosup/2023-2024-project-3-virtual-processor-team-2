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
instNode_t *parseLine(char *line, long nodeId);

/*
    Compare the first len characters of two strings
    params:
        line: line to be compared
        string: string to be compared
        len: number of characters to be compared
    returns:
        bool: true if the strings are same, false otherwise
*/
bool cmpStringFirst(char *line, char *string, int len);

/*
    Get arguments from an instruction line
    params:
        line: line to be parsed
    returns:
        char**: array of strings (no more than 2)
*/
char** getInstArgs(char *line);

/*
    Remove spaces from a string
    params:
        str: string to be parsed
*/
void rmSpaces(char *str);

/*
    Checks if the filename ends by .aop or not.
    params:
        filename: name of the file to check
    returns:
        boolean: true or false
*/
bool checkAOPFile(char* fileName);