#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#include "parser.h"

#define LINE_MAX_SIZE 64

enum regKind targetReg = RG_0;

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

    // Check the file extension 
    checkAOPFile(filename);

    char line[LINE_MAX_SIZE];
    instNode_t *lastNode = NULL;
    long nodeId = 0;
    long lineNb = 0;

    // read the file line by line
    while(fgets(line, LINE_MAX_SIZE, file)){
        // parse the line
        instNode_t *node = parseLine(line, nodeId, lineNb);

        // continue if the line is empty
        if(node == NULL){
            ++ lineNb;
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
        ++ lineNb;
    }
    // close the file
    fclose(file);
}

instNode_t *parseLine(char *line, long nodeId, long lineNb){

    // check if the line is empty or a comment
    if(line[0] == '\n' || strncmp(line, "//", 2) == 0){
        return NULL;
    }

    // Get the arguments
    char **args = getInstArgs(line);

    if(strncmp(line, "add", 3) == 0 || strncmp(line, "+", 1) == 0){
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
        newNode->targetReg = targetReg;
        return newNode;
    }
    else if(strncmp(line, "sub", 3) == 0 || strncmp(line, "-", 1) == 0){
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
        newNode->targetReg = targetReg;
        return newNode;
    }
    else if(strncmp(line, "mul", 3) == 0 || strncmp(line, "*", 1) == 0){
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
        newNode->targetReg = targetReg;
        return newNode;
    }
    else if(strncmp(line, "div", 3) == 0 || strncmp(line, "/", 1) == 0){
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
        newNode->targetReg = targetReg;
        return newNode;
    }
    else if(strncmp(line, "mod", 3) == 0 || strncmp(line, "%", 1) == 0){
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
        return newNode;
    }
    else if(strncmp(line, "shl", 3) == 0 || strncmp(line, "<<", 2) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_L_SHIFT;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->targetReg = targetReg;
        return newNode;
    }
    else if(strncmp(line, "and", 3) == 0 || strncmp(line, "&", 1) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_AND;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->targetReg = targetReg;
        return newNode;
    }
    else if(strncmp(line, "or", 2) == 0 || strncmp(line, "|", 1) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_OR;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->targetReg = targetReg;
        return newNode;
    }
    else if(strncmp(line, "xor", 3) == 0 || strncmp(line, "^", 1) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_XOR;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->targetReg = targetReg;
        return newNode;
    }
    else if(strncmp(line, "not", 3) == 0 || strncmp(line, "!", 1) == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->id = nodeId;
        // Set type of instruction
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_NOT;
        // Set arguments
        newNode->arg0 = args[0];
        newNode->arg1 = args[1];
        // Set target register
        newNode->targetReg = targetReg;
        return newNode;
    }

    // Trow error if the line is not an instruction
    fprintf(stderr, "\"%s\" Is not a valid instruction. line %ld\n", line, lineNb);
    exit(EXIT_FAILURE);

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
            strcpy(args[i], token);
        }
    }

    return args;
}


void checkAOPFile(char* fileName) {
    size_t size = strlen(fileName);

    if (size < 5 || fileName[size - 4] != '.' || fileName[size - 3] != 'a' || fileName[size - 2] != 'o' || fileName[size - 1] != 'p') {
        // trow error
        fprintf(stderr, "The filename is invalid. Please enter a valid .aop filename.\n");
        exit(EXIT_FAILURE);
    }
}