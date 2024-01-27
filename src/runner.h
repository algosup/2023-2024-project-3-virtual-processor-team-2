#include "parser.h"

/*
    Run the instructions
    params:
        nodeList: pointer to the instruction list
        varList: pointer to the variables list
        labelList: pointer to the labels list
*/
void nodeReader(instList_t *nodeList, varList_t *varList, labelList_t *labelList);

/*
    Run a node
    params:
        node: pointer to the node to be run
        varList: pointer to the variables list
        labelList: pointer to the labels list
*/
void runNode(instNode_t *node, varList_t *varList, labelList_t *labelList);

/*
    Run an operation node
    params:
        node: pointer to the node to be run
        varList: pointer to the variables list
*/
void runOpNode(instNode_t *node, varList_t *varList, labelList_t *labelList);

/*
    Run an action node
    params:
        node: pointer to the node to be run
        varList: pointer to the variables list
        labelList: pointer to the labels list
*/
void runActNode(instNode_t *node, varList_t *varList, labelList_t *labelList);

/*
    Run a label node
    params:
        node: pointer to the node to be run
        labelList: pointer to the labels list
*/
void runLabelNode(instNode_t *node, labelList_t *labelList);

/*
    Run add operation
    params:
        node: pointer to the node to be run
        varList: pointer to the variables list
*/
void opAdd(instNode_t *node, varList_t *varList);

