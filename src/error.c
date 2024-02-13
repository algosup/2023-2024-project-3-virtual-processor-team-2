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
        fprintf(file, "%s |\tError: invalid file\n", date_str);
        fprintf(file, "%s |\tDetails: file %s contains too much errors to be used\n", date_str, filename);
        fclose(file);
    }
    printErrorSummary(errData);
    exit(EXIT_FAILURE);

}

// void displayFileError(char* filename, const char* out, error_t *errData, int errorNumber);
