/*
    This file contains functions for throwing errors assembling errors
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#include "error.h"

const char* errorFile= "errors.log";

asm_error_t *initErrorFile(char *inputFile){
    asm_error_t *errData = malloc(sizeof(asm_error_t));
    errData->errors = 0;
    errData->inputFile = inputFile;
    if(errorFile != NULL){
        FILE *file = fopen(errorFile, "wb");
        if(file == NULL){
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        fclose(file);
    }
    errData->errors = 0;
    return errData;
}

void printErrorSummary(asm_error_t *errData){
    fprintf(stderr, "Error summary:\n");
    fprintf(stderr, "Total errors: %ld\n", errData->errors);
}

// ---------------------------PARSER ERROR--------------------------------------

void errorNoArg(long lineNb, asm_error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "No argument found");
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}

void invalidArg(char *arg, asm_error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];

    sprintf(errDetails, "Invalid argument '%s'", arg);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorTooManyArg(asm_error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];

    sprintf(errDetails, "Too many arguments");

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorLineSize(long lineNb, asm_error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "Line must be under 64 characters");
    sprintf(errLocation, "File %s, line %ld\n\n", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}

void errorfnf(char *filename, asm_error_t *errData){
    char *errType = "Error: File Not Found";
    char errDetails[64];

    sprintf(errDetails, "File '%s' not found", filename);

    displayError(errType, errDetails, NULL, errorFile, errData);

    printErrorSummary(errData); 

    exit(EXIT_FAILURE); 
}

void errorInvalidExt(char *filename, asm_error_t *errData){
    char *errType = "Invalid File Extension Error";
    char errDetails[64];

    sprintf(errDetails, "File '%s' has an invalid extension", filename);

    displayError(errType, errDetails, NULL, errorFile, errData);
    printErrorSummary(errData); 
    exit(EXIT_FAILURE); 
}

void errorInstruction(char *inst, long lineNb, asm_error_t *errData){
	char *errType = "Syntax Error";
	char errDetails[64];
	char errLocation[64];
	sprintf(errDetails, "Instruction \"%s\" not found", inst);
	sprintf(errLocation, "File %s, Line %ld\n\n", errData->inputFile, lineNb);
	displayError(errType, errDetails, errLocation, errorFile, errData);
}

void errorInstructionMissing(long lineNb, asm_error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "No instruction found in the input line");
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
    printErrorSummary(errData); 
    exit(EXIT_FAILURE); 
}


void errorInvalidRegister(char *reg, long lineNb, asm_error_t *errData){
    char *errType = "Register Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "Invalid register '%s'", reg);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}


void errorUnexpectedSymbol(char symbol, long lineNb, asm_error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "'%c' is unexpected", symbol);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}


void errorMissingSymbol(char symbol, long lineNb, asm_error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "'%c' is missing between arguments", symbol);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}


void errorInvalidComparison(long lineNb, asm_error_t *errData){
    char *errType = "Comparison Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "Invalid comparison");
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}


void errorTypeIncompatibility(char *type1, char *type2, long lineNb,  asm_error_t *errData){
    char *errType = "Type Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "%s cannot be compared with %s", type1, type2);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}


void errorSizeIncompatibility(char *var1, char *var2, long lineNb,  asm_error_t *errData){
    char *errType = "Size Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "%s's size is incompatible with %s's size", var1, var2);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}


void errorFilename(const char *filename,  asm_error_t *errData){
    char *errType = "Filename Error";
    char errDetails[64];

    sprintf(errDetails, "The filename '%s' should end by .aop and be at least 5 characters", filename);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorLineCharactersExceed(long lineNb,  asm_error_t *errData){
    char *errType = "Line Characters Exceed Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "The lines of a file shouldn’t exceed 64 characters each");
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}


void errorVarNotExist(long lineNb, char *varName, asm_error_t *errData){
    char *errType = "Non-existent Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "'%s' variable is not defined", varName);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}

void errorVarAlreadyExist(char *varName, long lineNb,  asm_error_t *errData){
    char *errType = "Already Exist Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "'%s' variable is already defined", varName);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}

// ---------------------------------BUILDER ERROR-----------------------------------------

void errorLifoSize( asm_error_t *errData){
    char *errType = "Lifo Size Error";
    char errDetails[64];

    sprintf(errDetails, "Error: comparison lifo isn't empty");

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorBuildComparison( asm_error_t *errData){
    char *errType = "Build Comparison Error";
    char errDetails[64];

    sprintf(errDetails, "Error: unknown comparison statement");

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorLabelDeclaration(long lineNb, char *label, asm_error_t *errData){
    char *errType = "Label Declaration Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "Label %s already declared", label);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}

void errorLabelNotFound(long lineNb, char *label,  asm_error_t *errData){
    char *errType = "Label Not Found Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "Label %s not found", label);
    sprintf(errLocation, "File %s, line %ld", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, errorFile, errData);
}


void errorEmptyLifo( asm_error_t *errData){
    char *errType = "Empty Lifo Error";
    char errDetails[64];

    sprintf(errDetails, "Error: Lifo is empty");

    displayError(errType, errDetails, NULL, errorFile, errData);
}

//-------------------BIN CONVERTER ERROR-------------------------------------

void errorFileDetection(const char *filename,  asm_error_t *errData){
    char *errType = "File Detection Error";
    char errDetails[64];

    sprintf(errDetails, "Error: no such file or directory '%s'", filename);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorFileType(const char *filename,  asm_error_t *errData){
    char *errType = "File Type Error";
    char errDetails[64];

    sprintf(errDetails, "Error: this file '%s' couldn’t be used for bin conversion", filename);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorFileIssues(const char *filename,  asm_error_t *errData){
    char *errType = "File Issues Error";
    char errDetails[64];

    sprintf(errDetails, "Error: the targeted file '%s' contains errors and couldn't be converted properly", filename);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorConversion(const char *variable, const char *issue,  asm_error_t *errData){
    char *errType = "Conversion Error";
    char errDetails[64];

    sprintf(errDetails, "The variable %s %s", variable, issue);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


// ---------RUNNER ERRORS---------

void errorMissingDependencies(const char *details,  asm_error_t *errData){
    char *errType = "Missing Dependencies Error";
    char errDetails[64];

    sprintf(errDetails, "These libraries/components are undefined: %s", details);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorResourceExhaustion( asm_error_t *errData){
    char *errType = "Resource Exhaustion Error";
    char errDetails[64] = "The system doesn't have any resources left.";

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorPathIssues(const char *path,  asm_error_t *errData){
    char *errType = "Path Issues Error";
    char errDetails[64];

    sprintf(errDetails, "Incorrect file paths: %s", path);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorEnvironmentIncompatibility(const char *os,  asm_error_t *errData){
    char *errType = "Environment Incompatibility Error";
    char errDetails[64];

    sprintf(errDetails, "The current operating system '%s' is unable to run this program", os);

    displayError(errType, errDetails, NULL, errorFile, errData);
}


void errorTimeout(const char *program,  asm_error_t *errData){
    char *errType = "Timeout Error";
    char errDetails[64];

    sprintf(errDetails, "The program '%s' didn’t respond anymore", program);

    displayError(errType, errDetails, NULL, errorFile, errData);
}

void displayError(char *errType, char *errDetails, char *errLocation, const char *out, asm_error_t *errData){
	++ errData->errors;
    fprintf(stderr, "Error: %s\n", errType);
    fprintf(stderr, "Details: %s\n", errDetails);
	if(errLocation != NULL){
	    fprintf(stderr, "In: %s\n\n", errLocation);
	}
    if(out != NULL){
        FILE *file = fopen( out, "ab");
        if(file == NULL){
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        // Get current time
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        // Format date
        char date_str[20]; // Sufficiently large buffer to hold formatted date
        strftime(date_str, sizeof(date_str), "%d-%m-%y %H:%M:%S", timeinfo);
		
		fprintf(file, "%s |\tError: %s\n",date_str, errType);
	    fprintf(file, "%s |\tDetails: %s\n",date_str, errDetails);
		if(errLocation != NULL){
		    fprintf(file, "%s |\tIn: %s\n\n",date_str, errLocation);
		}
        fclose(file);
    }
}

void errorMemAlloc(asm_error_t *errData){
    char *errType = "Memory Allocation Error";
    char *errDetails = "Memory allocation failed";

    displayError(errType, errDetails, NULL, errorFile, errData);
    printErrorSummary(errData); 
    exit(EXIT_FAILURE); 
}

