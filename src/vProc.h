#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

// Define the structure of mmu
typedef struct {
    int address;
    bool data[8];
    int maxSize;
} MMU_t;

// Struct of cache's values
typedef struct {
    uint8_t callId;
    uint16_t line;
    uint8_t labelId;
} cache_t;

// Define the structure of virtual processor
typedef struct {
   MMU_t mmu;
   cache_t cache;
   int maxSize;
} virtualProcessor_t;
    
// Struct of register's values
typedef struct {
    bool writable;
    uint16_t value;
} register_t;

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
FILE* readBinaryFile(char *filename);

/*
    Test the binary file extension
    params:
    char *filename: the name of the file tested 
*/
instNode_t parseBinaryLine(char *line, long nodeId, long lineNb);

/*


*/
int parserBinaryFile(char line, char *operand, char *reg, char *data, uint8_t *currentLine);
/*
    Print a decimal value in binary
    params:
        value: value to print
    returns:
        None
*/
void printBinary(uint16_t value);

void readBinaryInsctuction(cache_t *cache, char line, char *operand, char *reg, char *data, uint8_t *currentLine);
#ifdef __cplusplus
}
#endif