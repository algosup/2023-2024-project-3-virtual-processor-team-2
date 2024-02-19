#pragma once

#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct errorData{
    long errors;
    char *inputFile;
} asm_error_t;

/*
    Init error file
    params:
        out: Target file
        inputFile: Input file
    returns:
        error_t: Error history
*/
asm_error_t *initErrorFile(const char* out, char *inputFile);

/*
    Print error summary
    params:
        errData: Error history
*/
void printErrorSummary(asm_error_t *errData);

// ---------- Parsing/Assembling errors ----------

/*
    Throw an error when the line size is too big
    params:
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorLineSize(long lineNb, const char* out, asm_error_t *errData);

/*
    Throw an error when the given instruction doesn't exist
    params:
        inst: Instruction
        node: Instruction node to get additional information
        out: Target file (can be NULL)
        errData: Error history
*/
void errorInstruction(char* inst, instNode_t *node, const char* out, asm_error_t *errData);


/*
    Throw an error when no instruction is found in the input line
    params:
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorInstructionMissing(long lineNb, const char *out, asm_error_t *errData);

/*
    Throw an error for an invalid register
    params:
        reg: Register
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorInvalidRegister(char *reg, long lineNb, const char *out, asm_error_t *errData);

/*
    Throw an error for an unexpected symbol
    params:
        symbol: Unexpected symbol
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorUnexpectedSymbol(char symbol, long lineNb, const char *out, asm_error_t *errData);

/*
    Throw an error when a symbol is missing between arguments
    params:
        symbol: Missing symbol
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorMissingSymbol(char symbol, long lineNb, const char *out, asm_error_t *errData);

/*
    Throw an error for an invalid comparison
    params:
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorInvalidComparison(long lineNb, const char *out, asm_error_t *errData);

/*
    Throw an error for type incompatibility in comparisons
    params:
        type1: First type
        type2: Second type
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorTypeIncompatibility(char *type1, char *type2, long lineNb, const char *out, asm_error_t *errData);

/*
    Throw an error for size incompatibility in comparisons
    params:
        var1: First variable
        var2: Second variable
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorSizeIncompatibility(char *var1, char *var2, long lineNb, const char *out, asm_error_t *errData);

// ---------- Builder Errors ----------

/*
    Throw an error when the comparison lifo isn't empty
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorLifoSize(const char *out, asm_error_t *errData);

/*
    Throw an error when an unknown comparison statement is encountered
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorBuildComparison(const char *out, asm_error_t *errData);

/*
    Throw an error when a label is already declared
    params:
        label: Label that is already declared
        out: Target file (can be NULL)
        errData: Error history
*/
void errorLabelDeclaration(char *label, const char *out, asm_error_t *errData);

/*
    Throw an error when a label is not found
    params:
        label: Label that is not found
        out: Target file (can be NULL)
        errData: Error history

*/
void errorLabelNotFound(instNode_t *node, char *label, const char *out, asm_error_t *errData);

/*
    Throw an error when the lifo is empty
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorEmptyLifo(const char *out, asm_error_t *errData);

// ---------- Bin Converter Errors ----------

/*
    Throw an error when the specified file is not found
    params:
        filename: Name of the file that was not found
        out: Target file (can be NULL)
        errData: Error history
*/
void errorFileDetection(const char *filename, const char *out, asm_error_t *errData);

/*
    Throw an error when the file type is not suitable for binary conversion
    params:
        filename: Name of the file with the wrong type
        out: Target file (can be NULL)
        errData: Error history
*/
void errorFileType(const char *filename, const char *out, asm_error_t *errData);

/*
    Throw an error when the targeted file contains errors and can't be converted
    params:
        filename: Name of the file containing errors
        out: Target file (can be NULL)
        errData: Error history
*/
void errorFileIssues(const char *filename, const char *out, asm_error_t *errData);

/*
    Throw a conversion error with a specific message
    params:
        variable: Name of the variable causing the error
        issue: Description of the conversion issue
        out: Target file (can be NULL)
        errData: Error history
*/
void errorConversion(const char *variable, const char *issue, const char *out, asm_error_t *errData);


// ---------- Runner Errors ----------

/*
    Throw an error when there are missing dependencies
    params:
        details: Description of the missing dependencies
        out: Target file (can be NULL)
        errData: Error history
*/
void errorMissingDependencies(const char *details, const char *out, asm_error_t *errData);

/*
    Throw an error when the system runs out of resources
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorResourceExhaustion(const char *out, asm_error_t *errData);

/*
    Throw an error for incorrect file paths
    params:
        path: Incorrect file path
        out: Target file (can be NULL)
        errData: Error history
*/
void errorPathIssues(const char *path, const char *out, asm_error_t *errData);

/*
    Throw an error when the current environment is incompatible with the program
    params:
        os: Operating system or environment that is incompatible
        out: Target file (can be NULL)
        errData: Error history
*/
void errorEnvironmentIncompatibility(const char *os, const char *out, asm_error_t *errData);

/*
    Throw a timeout error for a non-responsive program
    params:
        program: Name or description of the program that did not respond
        out: Target file (can be NULL)
        errData: Error history
*/
void errorTimeout(const char *program, const char *out, asm_error_t *errData);


// ---------- Fatal errors ----------

/*
    Throw an error when the file is not found
    params:
        filename: File name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorfnf(char* filename, const char* out, asm_error_t *errData);

/*
    Throw an error when the file extension is invalid
    params:
        filename: File's name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorInvalidExt(char* filename, const char* out, asm_error_t *errData);

// ---------- Other errors ----------

/*
    Throw an error when there are too many arguments
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorTooManyArg(const char* out, asm_error_t *errData);

/*
    Throw an error when at least one argument is missing
    params:
        out: Target file (can be NULL)
        errData: Error history
*/
void errorNoArg(const char* out, asm_error_t *errData);

// ---------- Semantic Errors ----------

/*
    Throw an error for incorrect filename format
    params:
        filename: File's name
        out: Target file (can be NULL)
        errData: Error history
*/
void errorFilename(const char *filename, const char *out, asm_error_t *errData);

/*
    Throw an error when line characters exceed the maximum allowed
    params:
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorLineCharactersExceed(long lineNb, const char *out, asm_error_t *errData);

/*
    Throw an error for using a non-existent variable or register
    params:
        varName: Variable/Register name
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorVarNotExist(const char *varName, long lineNb, const char *out, asm_error_t *errData);

/*
    Throw an error for using a variable that is already declared
    params:
        varName: Variable name
        lineNb: Line number
        out: Target file (can be NULL)
        errData: Error history
*/
void errorVarAlreadyExist(const char *varName, long lineNb, const char *out, asm_error_t *errData);

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
void displayError(const char *errType, const char *errDetails, char *errLocation, const char *out, asm_error_t* errData);

#ifdef __cplusplus
}
#endif
