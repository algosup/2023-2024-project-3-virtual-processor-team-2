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
    long lineNb = 1;

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

    // copy the line to tokenize it
    char* lineCopy = malloc((strlen(line) + 1) * sizeof(char));
    if (!lineCopy) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    strcpy(lineCopy, line);

    // Get the instruction
    char *inst = getInst(lineCopy);
    inst = cleanString(inst);

    // Get the arguments
    char **args = getInstArgs(lineCopy);

    free(lineCopy);

    instNode_t *newNode = malloc(sizeof(instNode_t));
    newNode->id = nodeId;
    newNode->lineNb = lineNb;

    newNode->next = NULL;

    // Set arguments
    setArgs(newNode, args);
    
    bool isThatKind = false;
    // Check if the instruction is an operation
    isThatKind = isOp(inst, newNode);
    if(isThatKind){
        return newNode;
    }

    // Check if the instruction is an action
    isThatKind = isAct(inst, newNode);
    if(isThatKind){
        return newNode;
    }

    // Check if the instruction is a comparison
    isThatKind = isCmp(inst, newNode, line);
    if(isThatKind){
        return newNode;
    }

    // Check if the instruction is a declaration
    isThatKind = isDecla(inst, newNode);
    if(isThatKind){
        return newNode;
    }

    // Trow error if the line is not an instruction
    fprintf(stderr, "\"%s\" Is not a valid instruction. line %ld\n", line, lineNb);
    exit(EXIT_FAILURE);
}

bool isOp(char *inst, instNode_t *newNode){
        // Check if the instruction is an operation
    if(strcmp(inst, "add") == 0 || strcmp(inst, "+") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_ADD;
        return true;
    }
    else if(strcmp(inst, "sub") == 0 || strcmp(inst, "-") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_SUB;
        return true;
    }
    else if(strcmp(inst, "mul") == 0 || strcmp(inst, "*") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_MUL;
        return true;
    }
    else if(strcmp(inst, "div") == 0 || strcmp(inst, "/") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_DIV;
        return true;
    }
    else if(strcmp(inst,"mod") == 0 || strcmp(inst,"%") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_MOD;
        return true;
    }
    else if(strcmp(inst, "shl") == 0 || strcmp(inst, "<<") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_L_SHIFT;
        return true;
    }
    else if(strcmp(inst, "and") == 0 || strcmp(inst, "&") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_AND;
        return true;
    }
    else if(strcmp(inst, "or") == 0 || strcmp(inst, "|") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_OR;
        return true;
        }
    else if(strcmp(inst, "xor") == 0 || strcmp(inst, "^") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_XOR;
        return true;
    }
    else if(strcmp(inst, "not") == 0 || strcmp(inst, "!") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_NOT;
        return true;
    }
    else if(strcmp(inst, "neg") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_B_NEG;
        return true;
    }
    else if(strcmp(inst, "inc") == 0 || strcmp(inst, "++") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_INC;
        return true;
    }
    else if(strcmp(inst, "dec") == 0 || strcmp(inst, "--") == 0){
        newNode->inst = INST_OP;
        newNode->nodeType.op = malloc(sizeof(opNode_t));
        // Set type of operation
        newNode->nodeType.op->op = OP_DEC;
        return true;
    }

    return false;
}

bool isAct(char *inst, instNode_t *newNode){
    if(strcmp(inst, "goto") == 0){
        // Set type of instruction
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_GOTO;
        return true;
    }
    else if(strcmp(inst, "mov") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_MOV;
        return true;
    }
    else if(strcmp(inst, "call") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_CALL;
        return true;
    }
    else if(strcmp(inst, "ret") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_RET;
        return true;
    }
    else if(strcmp(inst, "clok") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_CLOK;
        return true;
    }
    else if(strcmp(inst, "draw") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_DRAW;
        return true;
    }
    else if(strcmp(inst, "ngr") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_EXIT;
        return true;
    }
    else if(strcmp(inst, "push") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_PUSH;
        return true;
    }
    else if(strcmp(inst, "pop") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_POP;
        return true;
    }
    else if(strcmp(inst, "pusha") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_PUSH_A;
        return true;
    }
    else if(strcmp(inst, "popa") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_POP_A;
        return true;
    }
    else if(strcmp(inst, "ob1") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_OB1;
        return true;
    }

    return false;
}

bool isCmp(char *inst, instNode_t *newNode, char* line){
    if(strcmp(inst, "if") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_CMP;
        newNode->nodeType.act->cmp = malloc(sizeof(cmpNode_t));
        // Set type of comparison
        newNode->nodeType.act->cmp->statem = CMP_IF;
        char **args = getIfArgs(line);
        setCmpKind(newNode, args[0]);
        setArgs(newNode, args + 1);
        return true;
    }
    else if(strcmp(inst, "else") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_CMP;
        newNode->nodeType.act->cmp = malloc(sizeof(cmpNode_t));
        // Set type of comparison
        newNode->nodeType.act->cmp->statem = CMP_ELSE;
        return true;
    }

    else if(strcmp(inst, "end") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_CMP;
        newNode->nodeType.act->cmp = malloc(sizeof(cmpNode_t));
        // Set type of comparison
        newNode->nodeType.act->cmp->statem = CMP_END;
        return true;
    }

    return false;
}

void setCmpKind(instNode_t *newNode, char *cmp){
    if(strcmp(cmp, "eq") == 0 || strcmp(cmp, "==") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_EQ;
    }
    else if(strcmp(cmp, "neq") == 0 || strcmp(cmp, "!=") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_NEQ;
    }
    else if(strcmp(cmp, "lt") == 0 || strcmp(cmp, "<") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_LT;
    }
    else if(strcmp(cmp, "lte") == 0 || strcmp(cmp, "<=") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_LTE;
    }
    else if(strcmp(cmp, "gt") == 0 || strcmp(cmp, ">") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_GT;
    }
    else if(strcmp(cmp, "gte") == 0 || strcmp(cmp, ">=") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_GTE;
    }
    else if(strcmp(cmp, "and") == 0 || strcmp(cmp, "&&") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_AND;
    }
    else if(strcmp(cmp, "or") == 0 || strcmp(cmp, "||") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_OR;
    }
    else if(strcmp(cmp, "xor") == 0 || strcmp(cmp, "^^") == 0){
        newNode->nodeType.act->cmp->cmp = CMP_XOR;
    }
  \
    else{
        fprintf(stderr, "Invalid comparison\n");
        exit(EXIT_FAILURE);
    }
}

bool isDecla(char *inst, instNode_t *newNode){
    if(strcmp(inst, "lab") == 0){
        newNode->inst = INST_LABEL;
        return true;
    }
    else if(strcmp(inst, "var") == 0){
        newNode->inst = INST_VAR;
        return true;
    }

    return false;
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

    return inst;
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

char** getIfArgs(char* line){
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
    for (int i = 0; i < 3; i++) {
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
            args[i] = cleanString(args[i]);
        }
    }
    return args;

}

void setArgs(instNode_t *node, char **args) {
    // Clean the arguments
    for (int i = 0; i < 2; i++) {
        if (args[i] != NULL) {
            args[i] = cleanString(args[i]);
        }
    }

    // Check type of the arguments
    if (args[0] == NULL) {
        node->arg0.i_value = 0;
    }
    else{
        if (isInt(args[0])) {
            node->arg0.i_value = atoi(args[0]);
            node->arg0Type = VAR_INT;
        }
        else if(isBinary(args[0])){
            node->arg0.i_value = strToBin(args[0]);
            node->arg0Type = VAR_INT;
        }
        else if(isOctal(args[0])){
            node->arg0.i_value = strToOct(args[0]);
            node->arg0Type = VAR_INT;
        }
        else if(isHex(args[0])){
            node->arg0.i_value = strToHex(args[0]);
            node->arg0Type = VAR_INT;
        }
        else if(isFloat(args[0])){
            node->arg0.f_value = strtof(args[0], NULL);
            node->arg0Type = VAR_FLOAT;
        }
        else if(isChar(args[0])){
            node->arg0.c_value = strToChar(args[0]);
            node->arg0Type = VAR_CHAR;
        }
        else if(isString(args[0])){
            node->arg0.s_value = strToString(args[0]);
            node->arg0Type = VAR_STRING;
        }
        else if(isReg(args[0])){
            node->arg0.reg = strToReg(args[0]);
            node->arg0Type = VAR_REG;
        }
        else if(isTarget(args[0])){
            node->arg0.target = args[0];
            node->arg0Type = VAR_TARGET;
        }
        else{            
            node->arg0.s_value = NULL;
            node->arg0Type = VAR_NONE;
            return;
        }
    }

    if (args[1] == NULL) {
        node->arg1.i_value = 0;
    }
    else{
        if (isInt(args[1])) {
            node->arg1.i_value = atoi(args[1]);
            node->arg1Type = VAR_INT;
        }
        else if(isBinary(args[1])){
            node->arg1.i_value = strToBin(args[1]);
            node->arg1Type = VAR_INT;
        }
        else if(isOctal(args[1])){
            node->arg1.i_value = strToOct(args[1]);
            node->arg1Type = VAR_INT;
        }
        else if(isHex(args[1])){
            node->arg1.i_value = strToHex(args[1]);
            node->arg1Type = VAR_INT;
        }
        else if(isFloat(args[1])){
            node->arg1.f_value = strtof(args[1], NULL);
            node->arg1Type = VAR_FLOAT;
        }
        else if(isChar(args[1])){
            node->arg1.c_value = strToChar(args[1]);
            node->arg1Type = VAR_CHAR;
        }
        else if(isString(args[1])){
            node->arg1.s_value = strToString(args[1]);
            node->arg1Type = VAR_STRING;
        }
        else if(isReg(args[1])){
            node->arg1.reg = strToReg(args[1]);
            node->arg1Type = VAR_REG;
        }
        else if(isTarget(args[1])){
            node->arg1.target = args[1];
            node->arg1Type = VAR_TARGET;
        }
        else{
            node->arg1.s_value = NULL;
            node->arg1Type = VAR_NONE;
            return;
        }
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

void checkAOPFile(char* fileName) {
    size_t size = strlen(fileName);

    if (size < 5 || fileName[size - 4] != '.' || fileName[size - 3] != 'a' || fileName[size - 2] != 'o' || fileName[size - 1] != 'p') {
        // throw error
        fprintf(stderr, "The file extension is invalid. Please enter a valid .aop file extension.\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf(".aop file recognized.\n");
        exit(EXIT_SUCCESS);
    }
}