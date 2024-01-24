#include <stdlib.h>

#include "parser.h"
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

    // Init labels list struct
    labelList_t *labelList = malloc(sizeof(labelList_t));

    // Init instructions list struct
    instList_t *instList = malloc(sizeof(instList_t));

    // run parser
    parseFile(instList, argv[1]);

    // run builder
    // TODO: make the function build

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