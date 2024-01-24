#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#include "parser.h"

#define LINE_MAX_SIZE 64

enum regKind target_reg = RG_0;

flags_t parseArgs(int argc, char *argv[]){
    if(argc > 3){
        fprintf(stderr, "Too many arguments\n Try 'iat2 --help' for more information\n");
        exit(EXIT_FAILURE);
    }

    // Create the flags struct
    flags_t flags = {false, false, false, false};

    // Check if it's a flag or a file
    if(argv[1][0]=='-'){
        flagsSet(argv[1], &flags);
        return flags;
    }
    else{
        // Check if the second arg is flag
        if(argc == 3){
            if(argv[2][0]=='-'){
                flagsSet(argv[2], &flags);
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
    if(strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0){
        flags->help = true;
    }
    else if(strcmp(flag, "-v") == 0 || strcmp(flag, "--version") == 0){
        flags->version = true;
    }
    else if(strcmp(flag, "-d") == 0 || strcmp(flag, "--debug") == 0){
        flags->debug = true;
    }
    else if(strcmp(flag, "-V") == 0 || strcmp(flag, "--verbose") == 0) {
        flags->verbose = true;
    }
    else{
        fprintf(stderr, "Invalid flag\n Try 'iat2 --help' for more information\n");
        exit(EXIT_FAILURE);
    }
}

void parseFile(instList_t *nodeList, char *filename){
    // check if the file exists
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char line[LINE_MAX_SIZE];
    instNode_t *lastNode = NULL;
    long nodeId = 0;

    // read the file line by line
    while(fgets(line, LINE_MAX_SIZE, file)){
        // parse the line
        instNode_t *node = parseLine(line, nodeId);

        // continue if the line is empty
        if(node == NULL){
            continue;
        }

        // add the node to the list
        if(nodeList->head == NULL){
            nodeList->head = node;
        }
        else{
            lastNode->next = node;
        }
        lastNode = node;
        ++ nodeId;
    }
    // close the file
    fclose(file);
}

instNode_t *parseLine(char *line, long nodeId){

    // check if the line is empty or a comment
    if(line[0] == '\n' || strcmp(line, "//") == 0){
        return NULL;
    }

    // Get the arguments
    char **args = getInstArgs(line);

    // Check if the line is an operation
    if(cmpStringFirst(line, "add ", 4) == 0 || cmpStringFirst(line, "+ ", 2) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_ADD;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->target_reg = target_reg;
        return newNode;
    }
    else if(cmpStringFirst(line, "sub ", 4) == 0 || cmpStringFirst(line, "- ", 2) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_SUB;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->target_reg = target_reg;
        return newNode;
    }
    else if(cmpStringFirst(line, "mul ", 4) == 0 || cmpStringFirst(line, "* ", 2) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_MUL;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->target_reg = target_reg;
        return newNode;
    }
    else if(cmpStringFirst(line, "div ", 4) == 0 || cmpStringFirst(line, "/ ", 2) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_DIV;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->target_reg = target_reg;
        return newNode;
    }
    else if(cmpStringFirst(line, "mod ", 4) == 0 || cmpStringFirst(line, "% ", 2) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_MOD;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->target_reg = target_reg;
        return newNode;
    }
    // TODO: add operations for r shift, l shift, binary and, binary or, binary xor, binary not

    return NULL;
}

bool cmpStringFirst(char *line, char *string, int len){
    for(int i = 0; i < len; i++){
        // check if the strings are ended
        if(line[i] == '\n' || line[i] == '\0' || string[i] == '\0'){
            return false;
        }
        if(line[i] != string[i]){
            return false;
        }
    }
    return true;
}

char **getInstArgs(char *line) {
    char **args = (char **)malloc(2 * sizeof(char *));
    if (!args) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Remove the instruction name
    char *token = strtok((char *)line, " ");
    if (!token) {
        fprintf(stderr, "Invalid input format\n");
        exit(EXIT_FAILURE);
    }

    // Get the arguments
    for (int i = 0; i < 2; i++) {
        token = strtok(NULL, ",");
        if (!token) {
            args[i] = NULL;
        } else {
            // Allocate memory for the argument and copy it
            args[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
            if (!args[i]) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            // Remove spaces
            rmSpaces(token);
            strcpy(args[i], token);
        }
    }

    return args;
}

void rmSpaces(char* str) {
    char* buffer = str;
    do {
        while (*buffer == ' ') {
            ++buffer;
        }
    } while (*str++ = *buffer++);
}