#include "ast.h"

/*
    Read nodes from the instruction list and build the program
    params:
        nodeList: pointer to the instruction list
        labelList: pointer to the label list    
*/
void build(instList_t *nodeList, labelList_t *labelList);

/*
    Build an operation node
    params:
        node: pointer to the instruction node
*/
void buildOpNode(instNode_t *node);

/*
    Build an action node
    params:
        node: pointer to the instruction node
*/
void buildActNode(instNode_t *node);

/*
    Build a comparison node
    params:
        node: pointer to the instruction node
*/
void buildCmpNode(instNode_t *node);



/*
    Build a label node
    params:
        node: pointer to the instruction node
        labelList: pointer to the label list
*/
void buildLabelNode(instNode_t *node, labelList_t *labelList);

/*
    Add a label to the label list
    params:
        list: pointer to the label list
        name: label name
        nodeId: node id
*/
void addLabel(labelList_t *list, char *name, long nodeId);

/*
    Upgrades the size of the variable list
    params:
        list: pointer to the variable list
*/
void incLabelList(labelList_t *list);