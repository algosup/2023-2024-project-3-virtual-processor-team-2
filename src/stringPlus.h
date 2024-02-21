#include <stdbool.h>
#include "error.h"

/*
    Convert a string to binary
    params:
        arg: string to be converted
    returns:
        int: binary number
*/
int strToBin(char *arg);

/*
    Convert a string to octal
    params:
        arg: string to be converted
    returns:
        int: octal number
*/
int strToOct(char *arg);

/*
    Convert a string to hexadecimal
    params:
        arg: string to be converted
    returns:
        int: hexadecimal number
*/
int strToHex(char *arg);

/*
    Remove quotes from a string to get the char
    params:
        arg: string to be converted
    returns:
        char: char
*/
char strToChar(char *arg);

/*
    Remove quotes at beginning and at the end of a string
    params:
        arg: string to be converted
        errData: error history
    returns:
        char*: string
*/
char *strToString(char *arg, asm_error_t *errData);

/*
    Remove spaces and back line at the beginning and at the end of a string
    params:
        str: string to be cleaned
        errData: error history
    returns:
        char*: cleaned string
*/
char *cleanString(char *str, asm_error_t *errData);

/*
    Check if the string is an unsigned int
    params:
        str: string to be checked
*/
bool isUnsignedInt(char *str);

/*
    Check if the string is a register
    params:
        str: string to be checked
*/
bool isFromReg(char *str);
