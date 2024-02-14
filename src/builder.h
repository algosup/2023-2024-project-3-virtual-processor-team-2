#include "ast.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    Build the program
    params:
        nodeList: pointer to the instruction list
        errData: pointer to the error struct
*/
void buildProgram(instList_t *nodeList, error_t *errData);

/*
    Build a node
    params:
        node: pointer to the instruction node
        errData: pointer to the error struct
*/
void buildNode(instNode_t *node, error_t *errData);


#ifdef __cplusplus
}
#endif