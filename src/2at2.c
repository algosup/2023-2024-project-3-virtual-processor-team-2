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
#include "binExporter.h"

#define VERSION "0.2.0"
#define BIN_NAME "bin.2at2"

int main(int argc, char *argv[]) {
    // Init error data history
    asm_error_t *errData = initErrorFile(argv[1]);

    // ---------- Parse arguments ----------
    // Parse program arguments and get flags
    flags_t flags = parseArgs(argc, argv, errData);

    if (flags.help) {
        printHelp();
    }
    else if (flags.version) {
        printVersion();
    }

    fprintf(stderr, "[\t5%%\t] Parsing arguments successfully\n");

    // ---------- Init data ----------

    // Init variables list struct
    varList_t *varList = createEmptyVarList();

    // Init labels list struct
    labelList_t *labelList = createEmptyLabelList();
    
    // Init instructions list struct
    instList_t *instList = createEmptyInstList();

    fprintf(stderr, "[\t10%%\t] Data initialized successfully\n");

    // ---------- Parse ----------

    // run parser
    parseFile(instList, argv[1], varList, errData);

    if(flags.debug){
        printAst(instList);
    }

    // Stop if there are errors
    if(errData->errors > 0){
        printErrorSummary(errData);
        free(errData);
        free(varList);
        free(labelList);
        free(instList);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "[\t45%%\t] File parsed successfully\n");

    // ---------- Build ----------
    
    // run builder
    buildProgram(instList, varList, labelList, errData);

    if(flags.debug){
        printAst(instList);
    }
    
    // Stop if there are errors
    if(errData->errors > 0){
        printErrorSummary(errData);
        free(errData);
        free(varList);
        free(labelList);
        free(instList);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "[\t70%%\t] File built successfully\n");


    // ---------- Assemble ----------

    // run exporter
    exportToBin(instList, BIN_NAME, varList, errData);

    // Stop if there are errors
    if(errData->errors > 0){
        printErrorSummary(errData);
        free(errData);
        free(varList);
        free(labelList);
        free(instList);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "[\t95%%\t] File assembled successfully\n");

    // ---------- Print error summary ----------

    // Free memory
    free(varList);
    free(labelList);
    free(instList);

    fprintf(stderr, "[\t100%%\t] Work success\n");

    printErrorSummary(errData);

    // Free error data
    free(errData);

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