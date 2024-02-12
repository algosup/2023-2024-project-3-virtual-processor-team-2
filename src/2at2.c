/*
    This file aims to be the main file of the project
    It will call the parser, builder and runner
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "builder.h"
#include "2at2.h"
#include "debug.h"
#include "error.h"

#define VERSION "0.0.5"

int main(int argc, char *argv[]) {
    // Parse program arguments and get flags
    flags_t flags = parseArgs(argc, argv);

    if (flags.help) {
        printHelp();
    }
    else if (flags.version) {
        printVersion();
    }

    // Init variables list struct
    varList_t *varList = malloc(sizeof(varList_t));
    varList->size = 10;
    varList->list = malloc(sizeof(var_t) * varList->size);
    // Init variables list
    for(size_t i = 0; i < varList->size; i++){
        varList->list[i].name = NULL;
    }

    // Init labels list struct
    labelList_t *labelList = malloc(sizeof(labelList_t));
    labelList->size = 10;
    labelList->list = malloc(sizeof(label_t) * labelList->size);
    for(size_t i = 0; i < labelList->size; i++){
        labelList->list[i].name = NULL;
    }
    // Init instructions list struct
    instList_t *instList = malloc(sizeof(instList_t));
    instList->head = NULL;

    // Init error data history
    error_t *errData = malloc(sizeof(error_t));
    errData->errors = 0;
    errData->inputFile = malloc(sizeof(argv[1])+1);
    strcpy(errData->inputFile, argv[1]);

    // run parser
    parseFile(instList, argv[1], errData);
    
    // run builder
    // TODO: Do Builder

    // run exporter
    // TODO: make the function export to binary

    // Free memory
    free(varList);
    free(labelList);
    free(instList);
    
    exit(EXIT_SUCCESS);
}

void printHelp() {
    printf("Usage: iat2 file [options]\n");
    printf("Options:\n");
    printf("  -h, --help\t\t\tShow this help message and exit\n");
    printf("  -v, --version\t\t\tShow program version and exit\n");
    printf("  -d, --debug\t\t\tShow debug messages\n");
    printf("  -V, --verbose\t\t\tShow verbose messages\n");
    exit(EXIT_SUCCESS);
}

void printVersion() {
    printf("iat2 version %s\n", VERSION);
    exit(EXIT_SUCCESS);
}