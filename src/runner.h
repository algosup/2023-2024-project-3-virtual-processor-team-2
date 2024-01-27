#include "builder.h"

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