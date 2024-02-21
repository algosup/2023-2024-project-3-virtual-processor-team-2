#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Struct of register's values
typedef struct {
    bool writable;
    uint16_t value;
} register_t;


/*
    Initialize the cache
    params:
        None
*/
void initCache();

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
void parseBinaryLine(char *line, long nodeId, long lineNb);

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
    params:
        int *arg:
        register_t currentRegister:
*/
void attributeOperand(int *arg, register_t currentRegister);

/*
    Allocate register
    params:
        int *arg:
    returns:
        register_t: the register
*/
register_t attributeRegister(int *arg);

/*
    Allocate immediate value
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeMov(int *arg, register_t currentRegister); // 00000

/*
    Go to label
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeGoto(int *arg, register_t currentRegister); // 00001

/*
    Call label
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeCall(int *arg, register_t currentRegister); // 00010

/*
    Interrupt
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeInt(int *arg, register_t currentRegister); // 00011

/*
    Push value to stack
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodePush(int *arg, register_t currentRegister); // 00100

/*
    XOR operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeXor(int *arg, register_t currentRegister); // 00101

/*
    Pop value from stack
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodePop(int *arg, register_t currentRegister); // 00110

/*
    Division operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeDiv(int *arg, register_t currentRegister); // 00111                    

/*
    Addition operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeAdd(int *arg, register_t currentRegister); // 01000                    

/*
    Substraction operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeSub(int *arg, register_t currentRegister); // 01001                    

/*
    Multiplication operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeMul(int *arg, register_t currentRegister); // 01010                    

/*
    Right shift operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeRsh(int *arg, register_t currentRegister); // 01011                    

/*
    Left shift operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeLsh(int *arg, register_t currentRegister); // 01100                    

/*
    AND operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeAnd(int *arg, register_t currentRegister); // 01101                    

/*
    OR operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeOr(int *arg, register_t currentRegister); // 01110                    

/*
    NOT operation
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeNot(int *arg, register_t currentRegister); // 01111                    

/*
    Use register
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeUseReg(int *arg, register_t currentRegister); // 10000                   

/*
    Use variable
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeUseVar(int *arg, register_t currentRegister); // 10001                   

/*
    Use label
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeLab(int *arg, register_t currentRegister); // 10010                    

/*
    Use variable as operand
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeVar(int *arg, register_t currentRegister); // 10011                    

/*
    Negate value
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeNeg(int *arg, register_t currentRegister); // 10100               

/*
    Modify value
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeMod(int *arg, register_t currentRegister); // 10101                    

/*
    Return value
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeRet(int *arg, register_t currentRegister); // 10110                                  

/*
    Call label
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeMovFromVar(int *arg, register_t currentRegister); // 10111         

/*
    Move value to variable
    params:
        int *arg:
        register_t currentRegister:
*/
void opCodeMovToVar(int *arg, register_t currentRegister); // 11000      

/*
    Get size from variables
    params:
        int *arg:
        register_t currentRegister:
*/                              
void opCodeVarSize(int *arg, register_t currentRegister); // 11001    

/*
    Get data from variables
    params:
        int *arg:
        register_t currentRegister:
*/                
void opCodeVarData(int *arg, register_t currentRegister); // 11010                    

/*
    Exit software
*/
int intNgr();          // 00000000                   

/*
    Print content of rg0
    params:
        int *arg:
        register_t currentRegister:
*/
void intDraw(int *arg, register_t currentRegister); // 00000001   

/*
    Print ??
    params:
        int *arg:
        register_t currentRegister:
*/
void intOb1(int *arg, register_t currentRegister); // 00000010   

/*
    Comparasion if with the operand OR
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfOr(int *arg, register_t currentRegister); // 00000011

/*
    Comparasion if with the operand AND
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfAnd(int *arg, register_t currentRegister); // 00000100

/*
    Comparasion if with the operand XOR
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfXor(int *arg, register_t currentRegister); // 00000101

/*
    Comparasion if less than
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfLt(int *arg, register_t currentRegister); // 00000110

/*
    Comparasion if less than or equal
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfLte(int *arg, register_t currentRegister); // 00000111

/*
    Comparasion if greater than
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfGt(int *arg, register_t currentRegister); // 00001000

/*
    Comparasion if greater than or equal
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfGte(int *arg, register_t currentRegister); // 00001001

/*
    Comparasion if equal
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfEq(int *arg, register_t currentRegister); // 00001010

/*
    Comparasion if not equal
    params:
        int *arg:
        register_t currentRegister:
*/
void intIfNeq(int *arg, register_t currentRegister); // 00001011

/*
    Push all registers in stack
    params:
        int *arg:
        register_t currentRegister:
*/
void intPusha(int *arg, register_t currentRegister); // 00001100

/*
    Pop all register from stack
    params:
        int *arg:
        register_t currentRegister:
*/
void intPopa(int *arg, register_t currentRegister); // 00001101

/*
    Get the value from register
    params:
        int *arg:
        register_t currentRegister:
*/
void intMovFReg(int *arg, register_t currentRegister); // 00001110

/*
    Else
    params:
        int *arg:
        register_t currentRegister:
*/
void intElse(int *arg, register_t currentRegister); // 00001111

/*
    Call after each if/else to end instructions
    params:
        int *arg:
        register_t currentRegister:
*/
void intEnd(int *arg, register_t currentRegister); // 00010000


#ifdef __cplusplus
}
#endif