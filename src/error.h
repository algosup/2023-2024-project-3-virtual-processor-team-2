#pragma once

#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct errorData{
    long errors;
    char *inputFile;
} error_t;

/*
    Init error file
    params:
        out: Target file
        inputFile: Input file
    returns:
        error_t: Error history
*/
error_t *initErrorFile(const char* out, char *inputFile);

// ---------- Parsing/ Assembling errors ----------

/*
    Throw an error when the given instruction doesn't exist
    params:
        inst: Instruction
        node: Instruction node to get additionnal information
        out: Target file (can be NULL)
        errData: Error history
*/
void errorInstruction(char* inst, instNode_t *node, const char* out, error_t *errData);

/*
    Throw an error when the line size is too big
    params:
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorLineSize(long lineNb, const char* out, error_t *errData);

/*
    Print error summary
    params:
        errData: Error history
        out: Target file (can be NULL)
*/
void printErrorSummary(error_t *errData);

// ---------- Fatal errors ----------


/*
    Throw an error when the file is not found
    params:
        filename: File name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorfnf(char* filename, const char* out, error_t *errData);

/*
    Throw an error when the file extension is invalid
    params:
        filename: File name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorInvalidExt(char* filename, const char* out, error_t *errData);





/*
    Throw an error when there is too many arguments
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorTooManyArg(const char* out, error_t *errData);

/*
    Throw an error when there is no argument
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorNoArg(const char* out, error_t *errData);

/*
    Throw an error when there is a special character missing
    params:
        lineNb: line number
        filename: File name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorSpeCharMiss(long lineNb, const char* out, error_t *errData, char* filename)

/*

*/

#ifdef __cplusplus
}
#endif