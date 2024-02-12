#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

// need to raed the binary file
// look each line (limit of bits == 16 so if more than 16 error)
// cut each line in 3 parts
    // part 1 = 5 bits for the opcode
        // depending the opcode do action
    // part 2 = 3 bits for the register name (rg0 -> rg7)
    // part 3 = 8 bits for the immediate value (max size in int is 256)
        
/*
    Read the binary file
    params:
    char *filename: the name of the file to import

*/
void parseBinaryFile(char *filename);

/*
    Test the binary file extension
    params:
    char *filename: the name of the file tested 
*/
instNode_t parseBinaryLine(char *line, long nodeId, long lineNb);


#ifdef __cplusplus
}
#endif