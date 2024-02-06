/*
    This file is a part of the 2at2 project
    It will export the AST to a binary file
*/

#include <stdlib.h>
#include <string.h>

#include "binExporter.h"

void exportAST(instList_t *ast, varList_t *varList, labelList_t *labelList, char *filename){
    FILE *file = fopen(filename, "wb");
    if(file == NULL){
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "[");

    // write varList
    writeVarList(varList, file);


    // write labelList
    writeLabelList(labelList, file);


    // write ast
    writeAST(ast, file);
    
    fprintf(file, "]");

    fclose(file);
}

void writeVarList(varList_t *varList, FILE *file) {
    if (!varList || !file) {
        fprintf(stderr, "Invalid arguments\n");
        return;
    }

    fprintf(file, "{\"size\": %zu, \"list\": [", varList->size);

    for (size_t i = 0; i < varList->size; i++) {
        fprintf(file, "{\"name\": \"%s\", \"type\": \"%s\", \"value\": ",
                varList->list[i].name,
                varList->list[i].type == VAR_INT ? "int" :
                varList->list[i].type == VAR_FLOAT ? "float" :
                varList->list[i].type == VAR_CHAR ? "char" :
                varList->list[i].type == VAR_STRING ? "string" : "unknown");

        switch (varList->list[i].type) {
            case VAR_INT:
                fprintf(file, "%d", varList->list[i].value.i_value);
                break;
            case VAR_FLOAT:
                fprintf(file, "%f", varList->list[i].value.f_value);
                break;
            case VAR_CHAR:
                fprintf(file, "'%c'", varList->list[i].value.c_value);
                break;
            case VAR_STRING:
                fprintf(file, "\"%s\"", varList->list[i].value.s_value);
                break;
            default:
                fprintf(file, "null");
        }

        fprintf(file, "}");

        if (i < varList->size - 1) {
            fprintf(file, ",");
        }
    }

    fprintf(file, "]},\n");
}

void writeLabelList(labelList_t *labelList, FILE *file){
    if (!labelList || !file) {
        fprintf(stderr, "Invalid arguments\n");
        return;
    }

    fprintf(file, "{\"size\": %zu, \"list\": [", labelList->size);

    for (size_t i = 0; i < labelList->size; i++) {
        fprintf(file, "{\"name\": \"%s\", \"nodeId\": %ld, \"id\": %ld}",
                labelList->list[i].name,
                labelList->list[i].nodeId,
                labelList->list[i].id);

        if (i < labelList->size - 1) {
            fprintf(file, ",");
        }
    }

    fprintf(file, "]},\n");
}

void writeAST(instList_t *ast, FILE *file){
    if (!ast || !file) {
        fprintf(stderr, "Invalid arguments\n");
        return;
    }

    fprintf(file, "[");

    instNode_t *node = ast->head;
    while (node) {
        switch (node->inst)
        {
        case INST_OP:
            fprintf(file, "{\"instKind\": \"ope\",");
            break;
        case INST_ACT:
            fprintf(file, "{\"instKind\": \"act\",");
            break;
        case INST_VAR:
            fprintf(file, "{\"instKind\": \"var\",");
            break;
        case INST_LABEL:
            fprintf(file, "{\"instKind\": \"label\",");
            break;
        
        default:
            break;
        }

        fprintf(file, "\"nodeId\": %ld,", node->id);

        if(node->inst == INST_ACT){
            fprintf(file, "\"inst\": \"%s\",", node->nodeType.act->act == ACT_CMP ? "cmp" : "act");
        }
        else{
            fprintf(file, "\"inst\": \"%d\",", node->nodeType.op->op);
        }
        fprintf(file, "\n");
        node = node->next;
    }

    fprintf(file, "]");
}