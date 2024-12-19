#pragma once

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
        inputFile: Input file
    returns:
        error_t: Error history
*/
asm_error_t *initErrorFile(const char *inputFile);

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
        errData: Error history
*/
void errorLineSize(long lineNb, asm_error_t *errData);

/*
    Throw an error when the given instruction doesn't exist
    params:
        inst: Instruction
        lineNb: Line number
        errData: Error history
*/
void errorInstruction(char *inst, long lineNb, asm_error_t *errData);

/*
    Throw an error when no instruction is found in the input line
    params:
        lineNb: Line number
        errData: Error history
*/
void errorInstructionMissing(long lineNb, asm_error_t *errData);

/*
    Throw an error for an invalid register
    params:
        reg: Register
        lineNb: Line number
        errData: Error history
*/
void errorInvalidRegister(char *reg, long lineNb, asm_error_t *errData);

/*
    Throw an error for an unexpected symbol
    params:
        symbol: Unexpected symbol
        lineNb: Line number
        errData: Error history
*/
void errorUnexpectedSymbol(char symbol, long lineNb, asm_error_t *errData);

/*
    Throw an error when a symbol is missing between arguments
    params:
        symbol: Missing symbol
        lineNb: Line number
        errData: Error history
*/
void errorMissingSymbol(char symbol, long lineNb, asm_error_t *errData);

/*
    Throw an error for an invalid comparison
    params:
        lineNb: Line number
        errData: Error history
*/
void errorInvalidComparison(long lineNb, asm_error_t *errData);

/*
    Throw an error for type incompatibility in comparisons
    params:
        type1: First type
        type2: Second type
        lineNb: Line number
        errData: Error history
*/
void errorTypeIncompatibility(char *type1, char *type2, long lineNb, asm_error_t *errData);

/*
    Throw an error for size incompatibility in comparisons
    params:
        var1: First variable
        var2: Second variable
        lineNb: Line number
        errData: Error history
*/
void errorSizeIncompatibility(char *var1, char *var2, long lineNb, asm_error_t *errData);

// ---------- Builder Errors ----------

/*
    Throw an error when the comparison lifo isn't empty
    params:
        errData: Error history
*/
void errorLifoSize(asm_error_t *errData);

/*
    Throw an error when an unknown comparison statement is encountered
    params:
        errData: Error history
*/
void errorBuildComparison(asm_error_t *errData);

/*
    Throw an error when a label is already declared
    params:
        lineNb: Line number
        label: Label that is already declared
        errData: Error history
*/
void errorLabelDeclaration(long lineNb, char *label, asm_error_t *errData);

/*
    Throw an error when a label is not found
    params:
        label: Label that is not found
        errData: Error history

*/
void errorLabelNotFound(long lineNb, char *label, asm_error_t *errData);

/*
    Throw an error when the lifo is empty
    params:
        errData: Error history
*/
void errorEmptyLifo(asm_error_t *errData);

// ---------- Bin Converter Errors ----------

/*
    Throw an error when the specified file is not found
    params:
        filename: Name of the file that was not found
        errData: Error history
*/
void errorFileDetection(const char *filename, asm_error_t *errData);

/*
    Throw an error when the file type is not suitable for binary conversion
    params:
        filename: Name of the file with the wrong type
        errData: Error history
*/
void errorFileType(const char *filename, asm_error_t *errData);

/*
    Throw an error when the targeted file contains errors and can't be converted
    params:
        filename: Name of the file containing errors
        errData: Error history
*/
void errorFileIssues(const char *filename, asm_error_t *errData);

/*
    Throw a conversion error with a specific message
    params:
        variable: Name of the variable causing the error
        issue: Description of the conversion issue
        errData: Error history
*/
void errorConversion(const char *variable, const char *issue, asm_error_t *errData);


// ---------- Runner Errors ----------

/*
    Throw an error when there are missing dependencies
    params:
        details: Description of the missing dependencies
        errData: Error history
*/
void errorMissingDependencies(const char *details, asm_error_t *errData);

/*
    Throw an error when the system runs out of resources
    params:
        errData: Error history
*/
void errorResourceExhaustion(asm_error_t *errData);

/*
    Throw an error for incorrect file paths
    params:
        path: Incorrect file path
        errData: Error history
*/
void errorPathIssues(const char *path, asm_error_t *errData);

/*
    Throw an error when the current environment is incompatible with the program
    params:
        os: Operating system or environment that is incompatible
        errData: Error history
*/
void errorEnvironmentIncompatibility(const char *os, asm_error_t *errData);

/*
    Throw a timeout error for a non-responsive program
    params:
        program: Name or description of the program that did not respond
        errData: Error history
*/
void errorTimeout(const char *program, asm_error_t *errData);


// ---------- Fatal errors ----------

/*
    Throw an error when the file is not found
    params:
        filename: File name
        errData: Error history
*/
void errorfnf(char* filename, asm_error_t *errData);

/*
    Throw an error when the file extension is invalid
    params:
        filename: File's name
        errData: Error history
*/
void errorInvalidExt(char* filename, asm_error_t *errData);

// ---------- Other errors ----------

/*
    Throw an error when there are too many arguments
    params:
        errData: Error history
*/
void errorTooManyArg(asm_error_t *errData);

/*
    Throw an error when at least one argument is missing
    params:
        lineNb: Line number
        errData: Error history
*/
void errorNoArg(long lineNb, asm_error_t *errData);

/*
    Throw an error when an argument is invalid
    params:
        arg: Invalid argument
        errData: Error history
*/
void invalidArg(char *arg, asm_error_t *errData);

// ---------- Semantic Errors ----------

/*
    Throw an error for incorrect filename format
    params:
        filename: File's name
        errData: Error history
*/
void errorFilename(const char *filename, asm_error_t *errData);

/*
    Throw an error when line characters exceed the maximum allowed
    params:
        lineNb: Line number
        errData: Error history
*/
void errorLineCharactersExceed(long lineNb, asm_error_t *errData);

/*
    Throw an error for using a non-existent variable or register
    params:
        varName: Variable/Register name
        lineNb: Line number
        errData: Error history
*/
void errorVarNotExist(long lineNb, char *varName, asm_error_t *errData);

/*
    Throw an error for using a variable that is already declared
    params:
        varName: Variable name
        lineNb: Line number
        errData: Error history
*/
void errorVarAlreadyExist(char *varName, long lineNb, asm_error_t *errData);

/*
    Exit the program when memory allocation fails
    params:
        errData: Error history
*/
void errorMemAlloc(asm_error_t *errData);

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
void displayError(char *errType, char *errDetails, char *errLocation, const char *out, asm_error_t* errData);

/*
    Display error messages for unsupported interrupt codes
    params:
        code: Invalid instruction code
        errData: Error history
*/
void errorIntCodeNotSupported(long code, asm_error_t *errData);

/*
    Display error messages for unkwown errors
    params:
        details: Details about the error
        errData: Error history
*/
void unknownError(char *details, asm_error_t *errData);

/*
    Display error messages for binary conversion issues
    params:
        instName: Name of the instruction
        lineNb: Line number
        errData: Error history
*/
void errorOpBinConversion(char *instName, long lineNb, asm_error_t *errData);

/*
    Display error messages for binary conversion issues
    params:
        instName: Name of the instruction
        lineNb: Line number
        errData: Error history
*/
void errorIntBinConversion(char *instName, long lineNb, asm_error_t *errData);

/*
    Display error messages for runtime issues
    params:
        details: Details about the error
        errData: Error history
*/
void errorRuntime(char *details, asm_error_t *errData);

/*
    Display error messages for read-only register
    params:
        errData: Error history
*/
void errorReadOnly(asm_error_t *errData);

/*
    Display error messages for overflow issues
    params:
        errData: Error history
*/
void errorOverflow(asm_error_t *errData);

/*
    Display error messages for invalid if statement
    params:
        lineNb: Line number
        errData: Error history
*/
void errorIfInt(long lineNb, asm_error_t *errData);

#ifdef __cplusplus
}
#endif