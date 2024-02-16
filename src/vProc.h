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
    Set the speed of the clock based on ticks
    params:
    int time: Time passed when the application is running
    int lastTime: The last time that the clock have been updated
    int latentTicks:
*/
void setClock(int time, int lastTime, int latentTicks);

/*
    Test the binary file extension
    params:
    char *filename: the name of the file tested 
*/
instNode_t parseBinaryLine(char *line, long nodeId, long lineNb);

/*
    Parse the binary file to and transform char in int
    params:
    char *line:
    char *operand:
    char *reg:
    char *data:
    uint8_t currentLine:
*/
int* parserBinaryFile(char *line, char *operand, char *reg, char *data, uint8_t currentLine);

/*
    Print a decimal value in binary
    params:
        value: value to print
    returns:
        None
*/
void printBinary(uint16_t value);

/*
    Attribute value to operands, registers and immediate values
    params:
    cache_t *cache:
    char *line:
    char *operand:
    char *reg:
    char *data:
    uint8_t currentLine:
*/
void readBinaryInstruction(cache_t *cache, char *line, char *operand, char *reg, char *data, uint8_t currentLine, MMU_t processing);

/*
    Allocate operand
*/
void attributeOperand(int *arg);

register_t attributeRegister(int *arg);

//   OpCode Function               5bits    For each time use without instruction after
void opCodeMov(int *arg);       // 00000                    4/4
void opCodeGoto(int *arg);                         // 00001                    1/1            
void opCodeCall(int *arg);                         // 00010                    1/1
void opCodeInt(int *arg);                          // 00011                    0/13             
void opCodePush(int *arg);                         // 00100                    1/1
void opCodeXor(int *arg);                          // 00101                    3/3
void opCodePop(int *arg);                          // 00110                    1/1
void opCodeDiv(int *arg);                          // 00111                    3/3
void opCodeAdd(int *arg);                          // 01000                    3/3
void opCodeSub(int *arg);                          // 01001                    3/3
void opCodeMul(int *arg);                          // 01010                    3/3
void opCodeRsh(int *arg);                          // 01011                    3/3
void opCodeLsh(int *arg);                          // 01100                    
void opCodeAnd(int *arg);                          // 01101                    3/3
void opCodeOr(int *arg);                           // 01110                    3/3
void opCodeNot(int *arg);                          // 01111                    3/3
void opCodeUseReg(int *arg);                       // 10000                   
void opCodeUseVar(int *arg);                       // 10001                   
void opCodeLab(int *arg);                          // 10010                    1/1
void opCodeVar(int *arg);                          // 10011                    0/2
void opCodeNeg(int *arg);                          // 10100               
void opCodeMod(int *arg);                          // 10101                    3/3
void opCodeRet(int *arg);                          // 10110                    1/1              
void opCodeMovFromVar(int *arg);                   // 10111                    0/13                       
void opCodeMovToVar(int *arg);                     // 11000                    2/3                
void opCodeVarSize(int *arg);                      // 11001                    0/2 
void opCodeVarData(int *arg);                      // 11010                    tricky/6

void intNgr();
void intDraw();
void intOb1();
void intIfOr();
void intIfAnd();
void intIfXor();
void intIfLt();
void intIfLte();
void intIfGt();
void intIfGte();
void intIfEq();
void intIfNeq();
void intPusha();
void intPopa();
void intMovFReg();
void intElse();
void intEnd();
#ifdef __cplusplus
}
#endif