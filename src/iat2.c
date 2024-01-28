/*
    This file aims to be the main file of the project
    It will call the parser, builder and runner
*/

#include <stdlib.h>
#include "runner.h"
#include "iat2.h"

#define VERSION "0.0.1"

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
    varList->size = 0;
    varList->list = NULL;

    // Init labels list struct
    labelList_t *labelList = malloc(sizeof(labelList_t));
    labelList->size = 0;
    labelList->list = NULL;

    // Init instructions list struct
    instList_t *instList = malloc(sizeof(instList_t));
    instList->head = NULL;

    // run parser
    parseFile(instList, argv[1]);

    if(flags.debug) {
        printInstList(instList, "../bin/out0.txt");
        printVarList(varList, "../bin/out0.txt");
        printLabelList(labelList, "../bin/out0.txt");
    }
    // run builder
    // build(instList, labelList);

    // if(flags.debug) {
    //     printInstList(instList, "../bin/out1.txt");
    //     printVarList(varList, "../bin/out1.txt");
    //     printLabelList(labelList, "../bin/out1.txt");
    // }

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