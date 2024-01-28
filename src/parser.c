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
    // Get the instruction
    char *inst = getInst(line);
    // Get the arguments
    char **args = getInstArgs(line);
    instNode_t *newNode = malloc(sizeof(instNode_t));
    newNode->id = nodeId;

    // Set arguments
    newNode->arg0 = args[0];
    newNode->arg1 = args[1];
    // Set target register
    newNode->targetReg = targetReg;

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
    else if(strcmp(inst, "if") == 0){
        instNode_t *newNode = malloc(sizeof(instNode_t));
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_IF;
        return true;
    }
    else if(strcmp(inst, "else") == 0){
        newNode->inst = INST_ACT;
        newNode->nodeType.act = malloc(sizeof(actNode_t));
        // Set type of action
        newNode->nodeType.act->act = ACT_ELSE;
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


void checkAOPFile(char* fileName) {
    size_t size = strlen(fileName);

    if (size < 5 || fileName[size - 4] != '.' || fileName[size - 3] != 'a' || fileName[size - 2] != 'o' || fileName[size - 1] != 'p') {
        // trow error
        fprintf(stderr, "The filename is invalid. Please enter a valid .aop filename.\n");
        exit(EXIT_FAILURE);
    }
}