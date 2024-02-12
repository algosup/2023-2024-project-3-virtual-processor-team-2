/*
    This file aims to be the parser of the project
    It will parse the file and create the instruction list
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "stringPlus.h"
#include "parser.h"

#define LINE_MAX_SIZE 64

const char* errorFile= "errors.log";

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

void parseFile(instList_t *nodeList, char *filename, error_t *errData){
    // check if the file exists
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        errorfnf(filename, errorFile, errData);
    }

    // Check the file extension 
    checkAOPFile(filename, errData);

    char line[LINE_MAX_SIZE];
    instNode_t *lastNode = NULL;
    long nodeId = 0;
    long lineNb = 1;

    // read the file line by line
    while(fgets(line, LINE_MAX_SIZE, file)){
            // Check if one of the file's line doesn't exceed 64 characters
        if (!checkLineSize(line, file)){
            errorLineSize(lineNb, errorFile, errData);
        }

        // parse the line
        instNode_t *node = parseLine(line, nodeId, lineNb, errData);

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

instNode_t *parseLine(char *line, long nodeId, long lineNb, error_t *errData){
    // check if the line is empty or a comment
    if(line[0] == '\n' || strncmp(line, "//", 2) == 0){
        return NULL;
    }

    instNode_t *newNode = malloc(sizeof(instNode_t));
    newNode->id = nodeId;
    newNode->lineNb = lineNb;
    newNode->isInter = false;

    newNode->next = NULL;

    // Get the instruction
    char *inst = getInst(line);
    
    // Get the arguments
    char **args = getInstArgs(line);

    // Set arguments
    setArgs(newNode, args);

    newNode->isInter = false;
        
    bool isThatKind = false;
    // Set the instruction
    isThatKind = isOp(inst, newNode, errData);
    if(isThatKind){
        return newNode;
    }

    // Trow error if the line is not an instruction
    errorInstruction(inst, newNode, errorFile, errData);
    return newNode;
}

bool isOp(char *inst, instNode_t *newNode, error_t *errData){
    if(strcmp(inst, "mov") == 0){
        newNode->op = OP_MOV;
    }
    else if(strcmp(inst, "goto") == 0){
        newNode->op = OP_GOTO;
    }
    else if(strcmp(inst, "call") == 0){
        newNode->op = OP_CALL;
    }
    else if(strcmp(inst, "int") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
    }
    else if(strcmp(inst, "push") == 0){
        newNode->op = OP_PUSH;
    }
    else if(strcmp(inst, "xor") == 0 || strcmp(inst, "^") == 0){
        newNode->op = OP_B_XOR;
    }
    else if(strcmp(inst, "pop") == 0){
        newNode->op = OP_POP;
    }
    else if(strcmp(inst, "div") == 0 || strcmp(inst, "/") == 0){
        newNode->op = OP_DIV;
    }
    else if(strcmp(inst, "add") == 0 || strcmp(inst, "+") == 0){
        newNode->op = OP_ADD;
    }
    else if(strcmp(inst, "sub") == 0 || strcmp(inst, "-") == 0){
        newNode->op = OP_SUB;
    }
    else if(strcmp(inst, "mul") == 0 || strcmp(inst, "*") == 0){
        newNode->op = OP_MUL;
    }
    else if(strcmp(inst, "shr") == 0 || strcmp(inst, ">>") == 0){
        newNode->op = OP_R_SHIFT;
    }
    else if(strcmp(inst, "shl") == 0 || strcmp(inst, "<<") == 0){
        newNode->op = OP_L_SHIFT;
    }
    else if(strcmp(inst, "and") == 0 || strcmp(inst, "&") == 0){
        newNode->op = OP_B_AND;
    }
    else if(strcmp(inst, "or") == 0 || strcmp(inst, "|") == 0){
        newNode->op = OP_B_OR;
    }
    else if(strcmp(inst, "not") == 0 || strcmp(inst, "!") == 0){
        newNode->op = OP_B_NOT;
    }
    else if(strcmp(inst, "inc") == 0 || strcmp(inst, "++") == 0){
        newNode->op = OP_INC;
    }
    else if(strcmp(inst, "dec") == 0 || strcmp(inst, "--") == 0){
        newNode->op = OP_DEC;
    }
    else if(strcmp(inst, "lab") == 0){
        newNode->op = OP_LAB;
    }
    else if(strcmp(inst, "var") == 0){
        newNode->op = OP_VAR;
    }
    else if(strcmp(inst, "mod") == 0 || strcmp(inst, "%") == 0){
        newNode->op = OP_MOD;
    }
    else{
        errorInstruction(inst, newNode, errorFile, errData);
        return false;
    }
    return true;
}


char *getInst(char *line) {
    char *buffer = malloc((strlen(line) + 1) * sizeof(char));
    if (!buffer) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(buffer, line);
    
    char *inst = strtok(buffer, " ");
    
    if (inst == NULL) {
        fprintf(stderr, "No instruction found in the input line\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    return cleanString(inst);
}

char **getInstArgs(char *line) {
    char **args = malloc(2 * sizeof(char *));
    if (!args) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Remove the instruction name
    char *token = strtok(line, " ");
    if (!token) {
        fprintf(stderr, "Invalid input format\n");
        free(args); // Free allocated memory before exit
        exit(EXIT_FAILURE);
    }

    // Get the arguments
    for (int i = 0; i < 2; i++) {
        token = strtok(NULL, ",");
        if (!token) {
            args[i] = NULL;
        } else {
            // Allocate memory for the argument and copy it
            args[i] = malloc(strlen(token) + 1);
            if (!args[i]) {
                fprintf(stderr, "Memory allocation error\n");
                for (int j = 0; j < i; j++) {
                    free(args[j]); // Free previously allocated memory
                }
                free(args); // Free args array
                exit(EXIT_FAILURE);
            }
            strcpy(args[i], cleanString(token));
        }
    }

    return args;
}

void setArgs(instNode_t *node, char **args){
    if(isReg(args[0])){
        node->inputReg = strToReg(args[0]);
        if(args[1] != NULL){
            node->arg = malloc(sizeof(args[1])+1);
            strcpy(node->arg, args[1]);
            return;
        }
    }
    else if(args[0] != NULL){
        node->arg = malloc(sizeof(args[0])+1);
        strcpy(node->arg, args[0]);
    }
}

bool isInt(char *arg) {
    // Check if the argument is a number
    size_t size = strlen(arg);
    for (size_t i = 0; i < size; i++) {
        if (arg[i] < '0' || arg[i] > '9') {
            return false;
        }
    }

    return true;
}

bool isBinary(char *arg) {
    // Check if the argument is a binary number
    size_t size = strlen(arg);
    if (size < 3 || arg[0] != '0' || arg[1] != 'b') {
        return false;
    }

    for (size_t i = 2; i < size; i++) {
        if (arg[i] != '0' && arg[i] != '1') {
            return false;
        }
    }

    return true;
}

bool isOctal(char *arg) {
    // Check if the argument is a octal number
    size_t size = strlen(arg);
    if (size < 3 || arg[0] != '0' || arg[1] != 'o') {
        return false;
    }

    for (size_t i = 2; i < size; i++) {
        if (arg[i] < '0' || arg[i] > '7') {
            return false;
        }
    }

    return true;
}

bool isHex(char *arg) {
    // Check if the argument is a hexadecimal number
    size_t size = strlen(arg);
    if (size < 3 || arg[0] != '0' || arg[1] != 'x') {
        return false;
    }

    for (size_t i = 2; i < size; i++) {
        if ((arg[i] < '0' || arg[i] > '9') && (arg[i] < 'a' || arg[i] > 'f') && (arg[i] < 'A' || arg[i] > 'F')) {
            return false;
        }
    }

    return true;
}

bool isFloat(char *arg) {
    // Check if the argument is a float
    size_t size = strlen(arg);
    bool dot = false;
    for (size_t i = 0; i < size; i++) {
        if (arg[i] < '0' || arg[i] > '9') {
            if (arg[i] == '.' && !dot) {
                dot = true;
            } else {
                return false;
            }
        }
    }

    return true;
}

bool isChar(char *arg) {
    // Check if the argument is a char
    size_t size = strlen(arg);
    if (size != 3 || arg[0] != '\'' || arg[2] != '\'') {
        return false;
    }

    return true;
}

bool isString(char *arg) {
    // Check if the argument is a string
    size_t size = strlen(arg);
    if (size < 3 || arg[0] != '"' || arg[size - 1] != '"') {
        return false;
    }

    return true;
}

bool isReg(char *arg) {
    // Check if the argument is a register
    if (strlen(arg) != 3 || arg[0] != 'r' || arg[1] != 'g' || arg[2] < '0' || arg[2] > '7') {
        return false;
    }

    return true;
}

bool isTarget(char *arg) {
    // Check if the argument contain other characters than letters, numbers and underscores
    for (size_t i = 0; i < strlen(arg); i++) {
        if ((arg[i] < 'a' || arg[i] > 'z') && (arg[i] < 'A' || arg[i] > 'Z') && (arg[i] < '0' || arg[i] > '9') && arg[i] != '_') {
            return false;
        }
    }

    return true;
}

enum regKind strToReg(char *arg) {
    // Convert a string to a register
    switch (arg[2]) {
        case '0':
            return RG_0;
        case '1':
            return RG_1;
        case '2':
            return RG_2;
        case '3':
            return RG_3;
        case '4':
            return RG_4;
        case '5':
            return RG_5;
        case '6':
            return RG_6;
        case '7':
            return RG_7;
        default:
            fprintf(stderr, "Invalid register\n");
            exit(EXIT_FAILURE);
    }
}

void checkAOPFile(char* fileName, error_t *errData) {
    size_t size = strlen(fileName);
    //Check if the filename ends by ".aop" and contains at least 5 characters
    if (size < 5 || fileName[size - 4] != '.' || fileName[size - 3] != 'a' || fileName[size - 2] != 'o' || fileName[size - 1] != 'p') {
        // throw error
       errorInvalidExt(fileName, errorFile, errData);
    }
}

bool checkLineSize(char* line, FILE *fp){
    if (strchr(line, '\n') != NULL){
            // the line contains an '\n'
            return true;
        }
        else if (fgets(line, LINE_MAX_SIZE, fp) == NULL){
            // It's the last line at the end of the file
            return true;
        }
        else{
            // Throws an error when the characters limit isn't respected
            return false;
        }
}