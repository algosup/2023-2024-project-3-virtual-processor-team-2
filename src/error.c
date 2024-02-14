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

void errorInstruction(char* inst, instNode_t *node, const char* out, error_t *errData){
    ++ errData->errors;
    fprintf(stderr, "Error: syntax error\n");
    fprintf(stderr, "Details: %s instruction is not recognized\n", inst);
    fprintf(stderr, "In: file %s, line %ld\n\n", errData->inputFile, node->lineNb);
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
        fprintf(file, "%s |\tError: syntax error\n", date_str);
        fprintf(file, "%s |\tDetails: %s instruction is not recognized\n", date_str, inst);
        fprintf(file, "%s |\tIn: file %s, line %ld\n\n", date_str, errData->inputFile, node->lineNb);
        fclose(file);
    }
}

void errorLineSize(long lineNb, const char* out, error_t *errData){
    ++ errData->errors;
    fprintf(stderr, "Error: syntax error\n");
    fprintf(stderr, "Details: line must to be under 64 characters\n");
    fprintf(stderr, "In: file %s, line %ld\n\n", errData->inputFile, lineNb);
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
        fprintf(file, "%s |\tError: syntax error\n", date_str);
        fprintf(file, "%s |\tDetails: line must to be under 64 characters\n", date_str);
        fprintf(file, "%s |\tIn: file %s, line %ld\n\n", date_str, errData->inputFile, lineNb);
        fclose(file);
    }

}

void printErrorSummary(error_t *errData){
    fprintf(stderr, "Error summary:\n");
    fprintf(stderr, "Total errors: %ld\n", errData->errors);
}

void errorfnf(char* filename, const char* out, error_t *errData){
    ++ errData->errors;
    fprintf(stderr, "Error: file not found\n");
    fprintf(stderr, "Details: file %s not found\n", filename);
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
        fprintf(file, "%s |\tError: file not found\n", date_str);
        fprintf(file, "%s |\tDetails: file %s not found\n", date_str, filename);
        fclose(file);
    }
    printErrorSummary(errData);
    exit(EXIT_FAILURE);
}

void errorInvalidExt(char* filename, const char* out, error_t *errData){
    ++ errData->errors;
    fprintf(stderr, "Error: invalid file extension\n");
    fprintf(stderr, "Details: file %s has an invalid extension\n", filename);
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
        fprintf(file, "%s |\tError: invalid file extension\n", date_str);
        fprintf(file, "%s |\tDetails: file %s has an invalid extension\n", date_str, filename);
        fclose(file);
    }
    printErrorSummary(errData);
    exit(EXIT_FAILURE);
}

void errorIssues(char* filename, const char* out, error_t *errData){
    ++ errData->errors;
    fprintf(stderr, "Error: invalid file\n");
    fprintf(stderr, "Details: file %s contains too much errors to be used\n", filename);
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
        fprintf(file, "%s |\tError: syntax error\n", date_str);
        fprintf(file, "%s |\tDetails: too many arguments\n Try 'iat2 --help' for more information\n", date_str);
        fprintf(file, "%s |\tIn: file %s, line %ld\n\n", date_str, errData->inputFile);
        fclose(file);
    }
    exit(EXIT_FAILURE);
}

void errorNoArg(const char* out, error_t *errData){
    ++ errData->errors;
    fprintf(stderr, "Error: syntax error\n");
    fprintf(stderr, "Details: no argument found\n Try 'iat2 --help' for more information\n");
    fprintf(stderr, "In: file %s, line %ld\n\n", errData->inputFile);
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
        fprintf(file, "%s |\tError: syntax error\n", date_str);
        fprintf(file, "%s |\tDetails: too many arguments\n Try 'iat2 --help' for more information\n", date_str);
        fprintf(file, "%s |\tIn: file %s, line %ld\n\n", date_str, errData->inputFile);
        fclose(file);
    }
    exit(EXIT_FAILURE);
}

void displayFileError(char* filename, const char* out, error_t *errData, int errorNumber){
    ++ errData->errors;
    const char* text1;
    const char* text2;

    // Determine error message based on errorNumber
    switch (errorNumber) {
        case 0:
            text1 = "Error: file not found\n";
            text2 = "Details: file %s not found\n";
            break;
        case 1:
            text1 = "Error: invalid file extension\n";
            text2 = "Details: file %s has an invalid extension\n";
            break;
        default:
            fprintf(stderr, "Invalid error number\n");
            return;
    }
    
    // Print error message to stderr
    fprintf(stderr, "%s", text1);
    fprintf(stderr, text2, filename);

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
        fprintf(file, "%s | %s", date_str, text1);
        fprintf(file, text2, filename);
        fclose(file);
    }
    printErrorSummary(errData);
    exit(EXIT_FAILURE);
}

void displaySyntaxError(const char* inst, instNode_t *node, char* filename, long lineNb, const char* out, error_t *errData, int errorNumber){
    ++ errData->errors;
    const char* text1;
    const char* text2;

    // Determine error message based on errorNumber
    switch (errorNumber) {
        case 0:
            text1 = "Error: syntax error\n";
            text2 = "Details: %s instruction is not recognized\n";
            break;
        case 1:
            text1 = "Error: syntax error\n";
            text2 = "Details: line must to be under 64 characters\n";
            break;
        default:
            fprintf(stderr, "Invalid error number\n");
            return;
    }
    
    // Print error message to stderr
    fprintf(stderr, "%s", text1);
    if (errorNumber == 0)
        fprintf(stderr, text2, inst);
    else
        fprintf(stderr, "%s", text2);
    fprintf(stderr, "In: file %s, line %ld\n\n", inputFile, lineNb);

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
        // Write error message to file
        fprintf(file, "%s | %s", date_str, text1);
        if (errorNumber == 0)
            fprintf(file, text2, inst);
        else
            fprintf(file, "%s", text2);
        fprintf(file, "In: file %s, line %ld\n\n", inputFile, lineNb);
        fclose(file);
    }
    printErrorSummary(errData);
    exit(EXIT_FAILURE);
}
