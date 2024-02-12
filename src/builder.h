#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

// // Lifo to build if/ else statements
// typedef struct lifoCmpNode{
//     cmpNode_t **list;
//     size_t size;
// } lifoCmpNode_t;


/*
    Read nodes from the instruction list and build the program
    params:
        nodeList: pointer to the instruction list
        labelList: pointer to the label list    
        varList: pointer to the variable list
*/
void build(instList_t *nodeList, labelList_t *labelList, varList_t *varList);

/*
    Build an operation node
    params:
        node: pointer to the instruction node
*/
// void buildOpNode(instNode_t *node);

// /*
//     Build an action node
//     params:
//         node: pointer to the instruction node
// */
// void buildActNode(instNode_t *node, lifoCmpNode_t *lifo);

// /*
//     Build a comparison node
//     params:
//         node: pointer to the instruction node
// */
// void buildCmpNode(instNode_t *node, lifoCmpNode_t *lifo);



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

/*
    Init the label list
    return:
        labelList_t: pointer to the label list
*/
labelList_t* initLabelList();

// /*
//     Add cmp node to the lifo (as new head)
//     params:
//         lifo: pointer to the lifo
//         node: pointer to the node
// */
// void pushCmpLifo(lifoCmpNode_t *lifo, cmpNode_t *node);

// /*
//     Remove cmp node from the lifo (as head)
//     params:
//         lifo: pointer to the lifo
//     return:
//         cmpNode_t: pointer to the node
// */
// cmpNode_t *popCmpLifo(lifoCmpNode_t *lifo);

/*
    Add variable to the variable list
    params:
        list: pointer to the variable list
        nide: instNode_t pointer
*/
void addVar(varList_t *list, instNode_t *node);

/*
    Upgrades the size of the variable list
    params:
        list: pointer to the variable list
*/
void incVarList(varList_t *list);

/*
    Init the variable list
    return:
        varList_t: pointer to the variable list
*/
varList_t* initVarList();

#ifdef __cplusplus
}
#endif