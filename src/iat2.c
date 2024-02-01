/*
    This file aims to be the main file of the project
    It will call the parser, builder and runner
*/
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "builder.h"
#include "runner.h"
#include "iat2.h"
#include "debug.h"

#define VERSION "0.0.2"

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

    // run parser
    parseFile(instList, argv[1]);

    if(flags.debug) {
        printInstList(instList, "../others/parsing.log");
        printVarList(varList, "../others/parsing.log");
        printLabelList(labelList, "../others/parsing.log");
    }

    
    // run builder
    build(instList, labelList);

    if(flags.debug) {
        printInstList(instList, "../others/building.log");
        printVarList(varList, "../others/building.log");
        printLabelList(labelList, "../others/building.log");
    }

    // run runner
    // TODO: make the function run

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