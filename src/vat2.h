#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    char cache[504][8];
} cache_t;

typedef struct{
    char stack[2016][8];
    char processing[2016][8];
    char memory[8320][8];
    char graphic[4032][8];
} ram_t;

// Define the struct of the ram
typedef struct {
    ram_t;
    cache_t;
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
void readBinaryInstruction(char *line, char *operand, char *reg, char *data, uint8_t currentLine);

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

int intNgr();          // 00000000                   
void intDraw(int *arg);         // 00000001                 
void intOb1(int *arg);          // 00000010                 
void intIfOr(int *arg);         // 00000011                 
void intIfAnd(int *arg);            // 00000100                    
void intIfXor(int *arg);            // 00000101                    
void intIfLt(int *arg);         // 00000110             
void intIfLte(int *arg);            // 00000111                    
void intIfGt(int *arg);         // 00001000             
void intIfGte(int *arg);            // 00001001                    
void intIfEq(int *arg);         // 00001010             
void intIfNeq(int *arg);            // 00001011                    
void intPusha(int *arg);            // 00001100                    
void intPopa(int *arg);         // 00001101             
void intMovFReg(int *arg);          // 00001110                  
void intElse(int *arg);         // 00001111             
void intEnd(int *arg);          // 00010000                  
#ifdef __cplusplus
}
#endif