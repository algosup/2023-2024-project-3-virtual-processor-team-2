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
    fprintf(file, "[\n");

    // write varList
    writeVarList(varList, file);


    // write labelList
    writeLabelList(labelList, file);


    // write ast
    writeAST(ast, file);
    
    fprintf(file, "\n]");

    fclose(file);
}

void writeVarList(varList_t *varList, FILE *file) {
    if (!varList || !file) {
        fprintf(stderr, "Invalid arguments\n");
        return;
    }

    fprintf(file, "{\"size\": %zu, \"vars\": [", varList->size);

    for (size_t i = 0; i < varList->size; i++) {
        fprintf(file, "\n{\"name\": \"%s\", \"type\": \"%s\", \"value\": ",
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

    fprintf(file, "\n]},\n");
}

void writeLabelList(labelList_t *labelList, FILE *file){
    if (!labelList || !file) {
        fprintf(stderr, "Invalid arguments\n");
        return;
    }

    fprintf(file, "{\"size\": %zu, \"labels\": [", labelList->size);

    for (size_t i = 0; i < labelList->size; i++) {
        fprintf(file, "\n{\"name\": \"%s\", \"nodeId\": %ld, \"id\": %ld}",
                labelList->list[i].name,
                labelList->list[i].nodeId,
                labelList->list[i].id);

        if (i < labelList->size - 1) {
            fprintf(file, ",");
        }
    }

    fprintf(file, "\n]},\n");
}

void writeAST(instList_t *ast, FILE *file){
    if (!ast || !file) {
        fprintf(stderr, "Invalid arguments\n");
        return;
    }

    fprintf(file, "{ \"nodes\": [");

    instNode_t *node = ast->head;
    while (node) {
        fprintf(file, "\n{\"nodeId\": %ld, ",node->id);

        // set instKind
        switch (node->inst)
        {
        case INST_OP:
            fprintf(file, "\"instKind\": \"ope\", \"inst\": \"%s\"", getOpkindStr(node->nodeType.op->op));
            break;
        case INST_ACT:
            fprintf(file, "\"instKind\": \"act\", \"inst\": \"%s\"", getActkindStr(node->nodeType.act->act));
            break;
        case INST_LABEL:
            fprintf(file, "\"instKind\": \"label\", \"label\": \"lab\"");
            break;
        case INST_VAR:
            fprintf(file, "\"instKind\": \"var\", \"var\": \"var\"");
            break;
        default:
            break;
        }

        //Add args
        fprintf(file, ", \"args\": [");
        if(node->inst == INST_ACT && node->nodeType.act->act == ACT_CMP && node->nodeType.act->cmp->statem == CMP_IF){
            fprintf(file, "{\"type\": \"cmp\", \"val\": %s},", getCmpKindStr(node->nodeType.act->cmp->cmp));
        }

        switch (node->arg0Type){
        case VAR_INT:
            fprintf(file, "{\"type\": \"int\", \"val\": %d},", node->arg0.i_value);
            break;
        case VAR_FLOAT:
            fprintf(file, "{\"type\": \"float\", \"val\": %f},", node->arg0.f_value);
            break;
        case VAR_CHAR:
            fprintf(file, "{\"type\": \"char\", \"val\": \"%c\"},", node->arg0.c_value);
            break;
        case VAR_STRING:
            fprintf(file, "{\"type\": \"string\", \"val\": \"%s\"},", node->arg0.s_value);
            break;
        case VAR_REG:
            fprintf(file, "{\"type\": \"reg\", \"val\": \"%s\"},", node->arg0.reg == RG_0 ? "r0" : node->arg0.reg == RG_1 ? "r1" : node->arg0.reg == RG_2 ? "r2" : node->arg0.reg == RG_3 ? "r3" : node->arg0.reg == RG_4 ? "r4" : node->arg0.reg == RG_5 ? "r5" : node->arg0.reg == RG_6 ? "r6" : node->arg0.reg == RG_7 ? "r7" : "unknown");
            break;
        case VAR_TARGET:
            fprintf(file, "{\"type\": \"target\", \"val\": \"%s\"},", node->arg0.target);
            break;
        
        default:
            break;
        }

        switch (node->arg1Type){
        case VAR_INT:
            fprintf(file, "{\"type\": \"int\", \"val\": %d}", node->arg1.i_value);
            break;
        case VAR_FLOAT:
            fprintf(file, "{\"type\": \"float\", \"val\": %f}", node->arg1.f_value);
            break;
        case VAR_CHAR:
            fprintf(file, "{\"type\": \"char\", \"val\": \"%c\"}", node->arg1.c_value);
            break;
        case VAR_STRING:
            fprintf(file, "{\"type\": \"string\", \"val\": \"%s\"}", node->arg1.s_value);
            break;
        case VAR_REG:
            fprintf(file, "{\"type\": \"reg\", \"val\": \"%s\"}", node->arg1.reg == RG_0 ? "r0" : node->arg0.reg == RG_1 ? "r1" : node->arg0.reg == RG_2 ? "r2" : node->arg0.reg == RG_3 ? "r3" : node->arg0.reg == RG_4 ? "r4" : node->arg0.reg == RG_5 ? "r5" : node->arg0.reg == RG_6 ? "r6" : node->arg0.reg == RG_7 ? "r7" : "unknown");
            break;
        case VAR_TARGET:
            fprintf(file, "{\"type\": \"target\", \"val\": \"%s\"}", node->arg1.target);
            break;
        
        default:
            break;
        }
        fprintf(file, "]");

        fprintf(file, "}");
        if (node->next) {
            fprintf(file, ",");
        }
        node = node->next;
    }


    fprintf(file, "\n]}");
}

char *getOpkindStr(enum opKind kind){
    switch (kind)
    {
    case OP_ADD:
        return "add";
    case OP_SUB:
        return "sub";
    case OP_MUL:
        return "mul";
    case OP_DIV:
        return "div";
    case OP_MOD:
        return "mod";
    case OP_INC:
        return "inc";
    case OP_DEC:
        return "dec";
    case OP_B_AND:
        return "and";
    case OP_B_OR:
        return "or";
    case OP_B_XOR:
        return "xor";
    case OP_B_NOT:
        return "not";
    case OP_L_SHIFT:
        return "shl";
    case OP_R_SHIFT:
        return "shr";
    case OP_B_NEG:
        return "neg";
    default:
        return "unknown";
    }
}

char *getActkindStr(enum actKind kind){
    switch (kind)
    {
    case ACT_MOV:
        return "mov";
    case ACT_GOTO:
        return "goto";
    case ACT_CALL:
        return "call";
    case ACT_RET:
        return "ret";
    case ACT_CLOK:
        return "clok";
    case ACT_DRAW:
        return "draw";
    case ACT_CMP:
        return "cmp";
    case ACT_EXIT:
        return "exit";
    case ACT_PUSH:
        return "push";
    case ACT_POP:
        return "pop";
    case ACT_PUSH_A:
        return "pusha";
    case ACT_POP_A:
        return "popa";
    case ACT_OB1:
        return "ob1";
    default:
        return "unknown";
    }
}

char *getCmpKindStr(enum cmpKind kind){
    switch (kind)
    {
    case CMP_OR:
        return "or";
    case CMP_AND:
        return "and";
    case CMP_NOT:
        return "not";
    case CMP_XOR:
        return "xor";
    case CMP_LT:
        return "lt";
    case CMP_GT:
        return "gt";
    case CMP_LTE:
        return "lte";
    case CMP_GTE:
        return "gte";
    case CMP_EQ:
        return "eq";
    case CMP_NEQ:
        return "neq";
    default:
        return "unknown";
    }
}