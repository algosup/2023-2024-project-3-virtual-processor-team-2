/*
    This file contains functions for throwing errors assembling errors
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "error.h"

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
        strftime(date_str, sizeof(date_str), "%d-%m-%y", timeinfo);
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
        strftime(date_str, sizeof(date_str), "%d-%m-%y", timeinfo);
        fprintf(file, "%s |\tError: syntax error\n", date_str);
        fprintf(file, "%s |\tDetails: line must to be under 64 characters\n", date_str);
        fprintf(file, "%s |\tIn: file %s, line %ld\n\n", date_str, errData->inputFile, lineNb);
        fclose(file);
    }

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
        strftime(date_str, sizeof(date_str), "%d-%m-%y", timeinfo);
        fprintf(file, "%s |\tError: file not found\n", date_str);
        fprintf(file, "%s |\tDetails: file %s not found\n", date_str, filename);
        fclose(file);
    }

    exit(EXIT_FAILURE);
}
