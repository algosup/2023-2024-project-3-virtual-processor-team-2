/*
    this file is used to define the functions of the ast.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "ast.h"

char *getIntCode(enum interruptKind kind){
    switch(kind){
        case INT_EXIT:
            return "0";
        case INT_DRAW:
            return "1";
        case INT_OB1:
            return "2";
        case INT_OR:
            return "3";
        case INT_AND:
            return "4";
        case INT_XOR:
            return "5";
        case INT_LT:
            return "6";
        case INT_LTE:
            return "7";
        case INT_GT:
            return "8";
        case INT_GTE:
            return "9";
        case INT_EQ:
            return "10";
        case INT_NEQ:
            return "11";
        case INT_PUSHA:
            return "12";
        case INT_POPA:
            return "13";
        case INT_MOV_F_REG:
            return "14";
        case INT_ELSE:
            return "15";
        case INT_END:
            return "16";
        default:
            // TODO: transform to error
            exit(EXIT_FAILURE);
    }
}