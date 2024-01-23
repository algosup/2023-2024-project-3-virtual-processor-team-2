#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#include "parser.h"


flags_t parseArgs(int argc, char *argv[]){
    if(argc > 3){
        fprintf(stderr, "Too many arguments\n Try 'iat2 --help' for more information\n");
        exit(EXIT_FAILURE);
    }

    // Create the flags struct
    flags_t flags = {false, false, false, false};

    // Check if it's a flag or a file
    if(argv[1][0]=='-'){
        flagsReader(argv[1], &flags);
        return flags;
    }
    else{
        // Check if the second arg is flag
        if(argc == 3){
            if(argv[2][0]=='-'){
                flagsReader(argv[2], &flags);
                return flags;
            }
            else{
                fprintf(stderr, "Invalid flag\n Try 'iat2 --help' for more information\n");
                exit(EXIT_FAILURE);
            }
        }
        else{
            return (flags_t){false, false, false, false};
        }
    }
}

void flagsSet(char *flag, flags_t *flags){
    if(strcmp(flag, "-h") || strcmp(flag, "--help")){
        flags->help = true;
    }
    else if(strcmp(flag, "-v") || strcmp(flag, "--version")){
        flags->version = true;
    }
    else if(strcmp(flag, "-d") || strcmp(flag, "--debug")){
        flags->debug = true;
    }
    else if(strcmp(flag, "-V") || strcmp(flag, "--verbose")){
        flags->verbose = true;
    }
    else{
        fprintf(stderr, "Invalid flag\n Try 'iat2 --help' for more information\n");
        exit(EXIT_FAILURE);
    }
}

void parseFile(instList_t *nodeList, char *filename){
    //TODO: implement
}

instNode_t *parseLine(char *line){
    // TODO: implement
    return NULL;
}
