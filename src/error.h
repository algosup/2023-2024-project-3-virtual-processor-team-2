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

// ---------- Parsing/Assembling errors ----------

/*
    Throw an error when the given instruction doesn't exist
    Throw an error when the given instruction doesn't exist
    params:
        inst: Instruction
        node: Instruction node to get additional information
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

// ---------- Bin converting errors ----------

// ---------- Fatal errors ----------

/*
    Throw an error when the file is not found
    params:
        filename: File name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorfnf(char* filename, const char* out, error_t *errData);
void errorfnf2(char* filename, const char* out, error_t *errData);

/*
    Throw an error when the file extension is invalid
    params:
        filename: File's name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorInvalidExt(char* filename, const char* out, error_t *errData);
void errorInvalidExt2(char* filename, const char* out, error_t *errData);

/*
    Throw an error when the file contains errors
    params:
        filename: File name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorIssues(char* filename, const char* out, error_t *errData);
void errorIssues2(char* filename, const char* out, error_t *errData);

// ---------- Other errors ----------

/*
    Throw an error when there are too many arguments
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorTooManyArg(const char* out, error_t *errData);

/*
    Throw an error when the given instruction doesn't exist
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorNoArg(const char* out, error_t *errData);
void errorNoArg2(const char* out, error_t *errData);

// ---------- Display error messages ----------

/*
    Display error messages depending on the issue
    params:
        errType: Type of error
        errDetails: Details about the error
        errLocation: Location of the error (can be NULL)
        out: Target file (can be NULL)
        errData: Error history
*/
void displayError(const char *errType, const char *errDetails, char *errLocation, const char *out, error_t* errData);

#ifdef __cplusplus
}
#endif
