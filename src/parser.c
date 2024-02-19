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
#define MAX_ARGS 2

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
        // TODO: throw error
    }
}

void parseFile(instList_t *nodeList, char *filename, varList_t *varList, asm_error_t *errData){
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
        instNode_t *node = parseLine(line, nodeId, lineNb, varList, errData);
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

instNode_t *parseLine(char *line, long nodeId, long lineNb, varList_t *varList, asm_error_t *errData){
    // check if the line is empty or a comment
    if(line[0] == '\n' || strncmp(cleanString(line), "//", 2) == 0){
        return NULL;
    }

    instNode_t *newNode = createEmptyInstNode();
    newNode->id = nodeId;
    newNode->lineNb = lineNb;

    // Get the instruction
    char *inst = getInst(line);
    
    // Get the arguments
    char **args = getInstArgs(line);


    // Set arguments
    setArgs(newNode, args);

    newNode->isInter = false;
        
    bool isThatKind = false;
    // Set the instruction
    isThatKind = isOp(inst, newNode, varList, errData);
    if(isThatKind){
        return newNode;
    }

    // Trow error if the line is not an instruction
    errorInstruction(inst, newNode, errorFile, errData);
    return newNode;
}

bool isOp(char *inst, instNode_t *newNode, varList_t *varList, asm_error_t *errData){
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
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }

    }
    else if(strcmp(inst, "pop") == 0){
        newNode->op = OP_POP;
    }
    else if(strcmp(inst, "div") == 0 || strcmp(inst, "/") == 0){
        newNode->op = OP_DIV;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "add") == 0 || strcmp(inst, "+") == 0){
        newNode->op = OP_ADD;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "sub") == 0 || strcmp(inst, "-") == 0){
        newNode->op = OP_SUB;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "mul") == 0 || strcmp(inst, "*") == 0){
        newNode->op = OP_MUL;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "shr") == 0 || strcmp(inst, ">>") == 0){
        newNode->op = OP_R_SHIFT;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "shl") == 0 || strcmp(inst, "<<") == 0){
        newNode->op = OP_L_SHIFT;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "and") == 0 || strcmp(inst, "&") == 0){
        newNode->op = OP_B_AND;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "or") == 0 || strcmp(inst, "|") == 0){
        newNode->op = OP_B_OR;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "not") == 0 || strcmp(inst, "!") == 0){
        newNode->op = OP_B_NOT;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "inc") == 0 || strcmp(inst, "++") == 0){
        newNode->op = OP_ADD;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
        newNode->arg1 = "1";
    }
    else if(strcmp(inst, "dec") == 0 || strcmp(inst, "--") == 0){
        newNode->op = OP_SUB;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
        newNode->arg1 = "1";
    }
    else if(strcmp(inst, "lab") == 0){
        newNode->op = OP_LAB;
    }
    else if(strcmp(inst, "var") == 0){
        newNode->op = OP_VAR;
        // add var to varList
        addVar(varList, newNode->arg0, newNode->arg1);
    }
    else if(strcmp(inst, "mod") == 0 || strcmp(inst, "%") == 0){
        newNode->op = OP_MOD;
        // check if first argument is null
        if(newNode->arg0 == NULL){
            // TODO: throw error
        }
    }
    else if(strcmp(inst, "ret") == 0){
        newNode->op = OP_RET;
        newNode->arg0 = "0";
        newNode->arg1 = "0";
    }
    else if(strcmp(inst, "ngr") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "0";
    }
    else if(strcmp(inst, "draw") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "1";
    }
    else if(strcmp(inst, "ob1") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "2";
    }
    else if(strcmp(inst, "or") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "3";
    }
    else if(strcmp(inst, "if_and") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "4";
    }
    else if(strcmp(inst, "if_xor") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "5";
    }
    else if(strcmp(inst, "if_lt") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "6";
    }
    else if(strcmp(inst, "if_lte") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "7";
    }
    else if(strcmp(inst, "if_gt") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "8";
    }
    else if(strcmp(inst, "if_gte") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "9";
    }
    else if(strcmp(inst, "if_eq") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "10";
    }
    else if(strcmp(inst, "if_neq") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "11";
    }
    else if(strcmp(inst, "pusha") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "12";
    }
    else if(strcmp(inst, "popa") == 0){
        newNode->op = OP_INT;
        newNode->isInter = true;
        newNode->arg0 = "13";
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
    char **args = malloc(MAX_ARGS * sizeof(char *));
    // init args to NULL
    for (int i = 0; i < MAX_ARGS; i++) {
        args[i] = NULL;
    }
    if (!args) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    char *buffer = malloc((strlen(line) + 1) * sizeof(char));
    if (!buffer) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(buffer, line);
    char *token = strtok(buffer, " ");
    if (token == NULL) {
        // TODO: throw error
        fprintf(stderr, "Invalid input format\n");
        free(args); // Free allocated memory before exit

    }

    for (int i = 0; i < MAX_ARGS; i++) {
        token = strtok(NULL, ",");
        if (!token) {
            if (i == 0) {
                // TODO: throw error
                fprintf(stderr, "Invalid input format: missing argument\n");
                return args;
            }
            args[i] = NULL;
        } else {
            args[i] = malloc(strlen(token) + 1);
            if (!args[i]) {
                // TODO: throw error
                fprintf(stderr, "Memory allocation error\n");
                // Free previously allocated memory
                for (int j = 0; j < i; j++) {
                    free(args[j]);
                }
                free(args); // Free args array
            }
            strcpy(args[i], cleanString(token));
        }
    }

    return args;
}

void setArgs(instNode_t *node, char **args){
    if(args[0] != NULL && isReg(args[0])){
        node->inputReg = strToReg(args[0]);
        if(args[1] != NULL){
            node->arg1 = malloc(sizeof(args[1])+1);
            strcpy(node->arg1, args[1]);
        }
    }
    else if(args[0] != NULL){
        node->arg0 = malloc(sizeof(args[0])+1);
        strcpy(node->arg0, args[0]);
        if(args[1] != NULL){
            node->arg1 = malloc(sizeof(args[1])+1);
            strcpy(node->arg1, args[1]);
        }
    }
    return;
}

bool isReg(char *arg) {
    // Check if the argument is a register
    if (strlen(arg) != 3 || arg[0] != 'r' || arg[1] != 'g' || arg[2] < '0' || arg[2] > '7') {
        return false;
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

void checkAOPFile(char* fileName, asm_error_t *errData) {
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