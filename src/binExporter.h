#include <stdio.h>
#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    Export the AST to a binary file
    params:
        astNb *node: the root of the AST
        varList_t *varList: the list of variables
        labelList_t *labelList: the list of labels
        char *filename: the name of the file to export
    
*/
void exportAST(instList_t *ast, varList_t *varList, labelList_t *labelList, char *filename);

/*
    Write variable list to file in json format
    format exemple: 
    {"size": 2,"list": [{"name": "var1","type": "int","value": 5},{"name": "var2","type": "float","value": 3.14}]}
    params:
        varList_t *varList: the list of variables
        FILE *file: the file to write to
*/
void writeVarList(varList_t *varList, FILE *file);

/*
    Write label list to file in json format
    format exemple: 
    {"size": 2,"list": [{"name": "label1","nodeId": 5,"id": 1},{"name": "label2","nodeId": 10,"id": 2}]}
    params:
        labelList_t *labelList: the list of labels
        FILE *file: the file to write to
*/
void writeLabelList(labelList_t *labelList, FILE *file);

/*
    Write AST to file in json format
    format exemple: 
    [{"instKind": "ope", "nodeId": 4, "inst": "++", "args": [{"type": "float", "val": 3.14}, ..]}, {"instKind": "if", "inst": ">", "nodeId": 5, "args": [{"type": "int", "val": 5}, ..], "true": {"instKind": "ope", "inst": "++", "nodeId": 6, "args": [{"type": "float", "val": 3.14}, ..]
    params:
        instList_t *ast: the AST
        FILE *file: the file to write to
*/
void writeAST(instList_t *ast, FILE *file);

/*
    Get the string representation of an operation kind
    params:
        enum opKind kind: the kind of operation
    return:
        char *: the string representation
*/
char *getOpkindStr(enum opKind kind);

/*
    Get the string representation of an action kind
    params:
        enum actKind kind: the kind of action
    return:
        char *: the string representation
*/
char *getActkindStr(enum actKind kind);

/*
    Get the string representation of a comparison kind
    params:
        enum cmpKind kind: the kind of comparison
    return:
        char *: the string representation
*/
char *getCmpKindStr(enum cmpKind kind);

#ifdef __cplusplus
}
#endif
