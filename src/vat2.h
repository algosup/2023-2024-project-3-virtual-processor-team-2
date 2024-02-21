#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

// Define the struct of the virtual processor
typedef struct {
    char ram[16384][8];
    char cache[504][8];
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
int* readBinaryInstruction(char *line, char *operand, char *reg, char *data, uint8_t currentLine);

/*
    Allocate operand
*/
void attributeOperand(int *arg, register_t currentRegister);

register_t attributeRegister(int *arg, register_t rg0, register_t rg1, register_t rg2, register_t rg3, register_t rg4, register_t rg5, register_t rg6, register_t rg7);

//   OpCode Function               5bits    For each time use without instruction after
void opCodeMov(int *arg, register_t currentRegister);       // 00000                    4/4
void opCodeGoto(int *arg, register_t currentRegister);                         // 00001                    1/1            
void opCodeCall(int *arg, register_t currentRegister);                         // 00010                    1/1
void opCodeInt(int *arg, register_t currentRegister);                          // 00011                    0/13             
void opCodePush(int *arg, register_t currentRegister);                         // 00100                    1/1
void opCodeXor(int *arg, register_t currentRegister);                          // 00101                    3/3
void opCodePop(int *arg, register_t currentRegister);                          // 00110                    1/1
void opCodeDiv(int *arg, register_t currentRegister);                          // 00111                    3/3
void opCodeAdd(int *arg, register_t currentRegister);                          // 01000                    3/3
void opCodeSub(int *arg, register_t currentRegister);                          // 01001                    3/3
void opCodeMul(int *arg, register_t currentRegister);                          // 01010                    3/3
void opCodeRsh(int *arg, register_t currentRegister);                          // 01011                    3/3
void opCodeLsh(int *arg, register_t currentRegister);                          // 01100                    
void opCodeAnd(int *arg, register_t currentRegister);                          // 01101                    3/3
void opCodeOr(int *arg, register_t currentRegister);                           // 01110                    3/3
void opCodeNot(int *arg, register_t currentRegister);                          // 01111                    3/3
void opCodeUseReg(int *arg, register_t currentRegister);                       // 10000                   
void opCodeUseVar(int *arg, register_t currentRegister);                       // 10001                   
void opCodeLab(int *arg, register_t currentRegister);                          // 10010                    1/1
void opCodeVar(int *arg, register_t currentRegister);                          // 10011                    0/2
void opCodeNeg(int *arg, register_t currentRegister);                          // 10100               
void opCodeMod(int *arg, register_t currentRegister);                          // 10101                    3/3
void opCodeRet(int *arg, register_t currentRegister);                          // 10110                    1/1              
void opCodeMovFromVar(int *arg, register_t currentRegister);                   // 10111                    0/13                       
void opCodeMovToVar(int *arg, register_t currentRegister);                     // 11000                    2/3                
void opCodeVarSize(int *arg, register_t currentRegister);                      // 11001                    0/2 
void opCodeVarData(int *arg, register_t currentRegister);                      // 11010                    tricky/6

int intNgr();          // 00000000                   
void intDraw(int *arg, register_t currentRegister);         // 00000001                 
void intOb1(int *arg, register_t currentRegister);          // 00000010                 
void intIfOr(int *arg, register_t currentRegister);         // 00000011                 
void intIfAnd(int *arg, register_t currentRegister);            // 00000100                    
void intIfXor(int *arg, register_t currentRegister);            // 00000101                    
void intIfLt(int *arg, register_t currentRegister);         // 00000110             
void intIfLte(int *arg, register_t currentRegister);            // 00000111                    
void intIfGt(int *arg, register_t currentRegister);         // 00001000             
void intIfGte(int *arg, register_t currentRegister);            // 00001001                    
void intIfEq(int *arg, register_t currentRegister);         // 00001010             
void intIfNeq(int *arg, register_t currentRegister);            // 00001011                    
void intPusha(int *arg, register_t currentRegister);            // 00001100                    
void intPopa(int *arg, register_t currentRegister);         // 00001101             
void intMovFReg(int *arg, register_t currentRegister);          // 00001110                  
void intElse(int *arg, register_t currentRegister);         // 00001111             
void intEnd(int *arg, register_t currentRegister);          // 00010000                  
#ifdef __cplusplus
}
#endif