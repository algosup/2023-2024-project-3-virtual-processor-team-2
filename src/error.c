/*
    This file contains functions for throwing errors assembling errors
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "error.h"

error_t *initErrorFile(const char* out, char *inputFile){
    error_t *errData = malloc(sizeof(error_t));
    errData->errors = 0;
    errData->inputFile = inputFile;
    if(out != NULL){
        FILE *file = fopen(out, "wb");
        if(file == NULL){
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        fclose(file);
    }
    errData->errors = 0;
    return errData;
}

void errorInstruction(char *inst, instNode_t *node, const char *out, error_t *errData){
	char *errType = "Syntax Error";
	char errDetails[64];
	char errLocation[64];
	sprintf(errDetails, "Instruction \"%s\" not found", inst);
	sprintf(errLocation, "File %s, Line %ld\n\n", errData->inputFile, node->lineNb);
	displayError(errType, errDetails, errLocation, out, errData);
}



void printErrorSummary(error_t *errData){
    fprintf(stderr, "Error summary:\n");
    fprintf(stderr, "Total errors: %ld\n", errData->errors);
}


void displayError(const char *errType, const char *errDetails, char *errLocation, const char *out, error_t *errData){
	++ errData->errors;
    fprintf(stderr, "Error: %s\n", errType);
    fprintf(stderr, "Details: %s\n", errDetails);
	if(errLocation != NULL){
	    fprintf(stderr, "In: %s\n", errLocation);
	}
    if(out != NULL){
        FILE *file = fopen(out, "ab");
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
		    fprintf(file, "%s |\tIn: %s\n",date_str, errLocation);
		}
        fclose(file);
    }
}

void errorNoArg2(const char *out, error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];

    sprintf(errDetails, "No argument found");

    displayError(errType, errDetails, NULL, out, errData);
}


void errorTooManyArg(const char *out, error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];

    sprintf(errDetails, "Too many arguments");

    displayError(errType, errDetails, NULL, out, errData);
}


void errorLineSize(long lineNb, const char *out, error_t *errData){
    char *errType = "Syntax Error";
    char errDetails[64];
    char errLocation[64];

    sprintf(errDetails, "Line must be under 64 characters");
    sprintf(errLocation, "File %s, line %ld\n\n", errData->inputFile, lineNb);

    displayError(errType, errDetails, errLocation, out, errData);
}

void errorfnf(char *filename, const char *out, error_t *errData){
    char *errType = "Error: File Not Found";
    char errDetails[64];

    sprintf(errDetails, "File '%s' not found", filename);

    displayError(errType, errDetails, NULL, out, errData);

    printErrorSummary(errData); 

    exit(EXIT_FAILURE); 
}

void errorInvalidExt(char *filename, const char *out, error_t *errData){
    char *errType = "Invalid File Extension Error";
    char errDetails[64];

    sprintf(errDetails, "File '%s' has an invalid extension", filename);

    displayError(errType, errDetails, NULL, out, errData);
    printErrorSummary(errData); 
    exit(EXIT_FAILURE); 
}

void errorIssues2(char *filename, const char *out, error_t *errData){
    char *errType = "Invalid File Error";
    char errDetails[64];

    sprintf(errDetails, "File '%s' contains too many errors to be used", filename);

    displayError(errType, errDetails, NULL, out, errData);
}

