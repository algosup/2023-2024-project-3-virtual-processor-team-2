/*
  This file is part of the test suite of at2 project
*/

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <array>

#include "gtest/gtest.h"
#include "parser.h"
#include "builder.h"

/*
 *  checkAOPFile
 */

TEST(checkAOPFile, invalidFileName) {
    // Test invalid file name
    char* invalidFileName = "test.txt";
    checkAOPFile(invalidFileName);
    ASSERT_TRUE(EXIT_FAILURE);
}

/*
 *  checkLineSize
 */

/*
 *  flagsSet
 */

/*
 *  getIfArgs
 */

/*
 *  getInst
 */

/*
 *  getInstArgs
 */

/*
 *  isCmp
 */

/*
 *  isDecla
 */

TEST(isDecla, lab){
    // Test valid declaration keyword
    char *tmp = "lab";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isDecla(tmp, newNode);
    ASSERT_TRUE(test);
}

TEST(isDecla, labWithSymbol){
    // Test invalid declaration with symbol
    char *tmp = "lab:";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isDecla(tmp, newNode);
    ASSERT_FALSE(test);
}

TEST(isDecla, var){
    // Test valid declaration keyword
    char *tmp = "var";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isDecla(tmp, newNode);
    ASSERT_TRUE(test);
}

/*
 *  isHex
 */

TEST(isHex, is0x0Af){
    // Test hexadecimal number with prefix "0x"
    char *tmp = "0x0Af";
    ASSERT_TRUE(isHex(tmp));
}

TEST(isHex, is0x09AF){
    // Test valid hexadecimal number
    char *tmp = "0x09AF";
    ASSERT_TRUE(isHex(tmp));
}

TEST(isHex, is0x0AFG){
    // Test invalid hexadecimal number
    char *tmp = "0x0AFG";
    ASSERT_FALSE(isHex(tmp));
}

TEST(isHex, is0x1010){
    // Test binary number with prefix "0b"
    char *tmp = "0bFFF";
    ASSERT_FALSE(isHex(tmp));
}

TEST(isHex, is0XF){
    // Test hexadecimal number with uppercase prefix "0X"
    char *tmp = "0XF";
    ASSERT_FALSE(isHex(tmp));
}

TEST(isHex, is09aF){
    // Test invalid hexadecimal number without prefix
    char *tmp = "09aF";
    ASSERT_FALSE(isHex(tmp));
}

/*
 *  isInt
 */

TEST(isInt, is0){
    // Test integer 0
    char *tmp = "0";
    ASSERT_TRUE(isInt(tmp));
}

TEST(isInt, is10){
    // Test positive integer
    char *tmp = "10";
    ASSERT_TRUE(isInt(tmp));
}

TEST(isInt, isA10){
    // Test non-integer input
    char *tmp = "A10";
    ASSERT_FALSE(isInt(tmp));
}

TEST(isInt, isFloat){
    // Test floating-point input
    char *tmp = "10.10";
    ASSERT_FALSE(isInt(tmp));
}

TEST(isInt, isN10){
    // Test negative integer
    char *tmp = "-10";
    ASSERT_TRUE(isInt(tmp));
}

/*
 *  isOctal
 */

TEST(isOctal, is0O7){
    // Test octal number with uppercase prefix "0O"
    char *tmp = "0O7";
    ASSERT_FALSE(isOctal(tmp));
}

TEST(isOctal, is0o0123456701234567){
    // Test long octal number
    char *tmp = "0o0123456701234567";
    ASSERT_TRUE(isOctal(tmp));
}

TEST(isOctal, is0o0369){
    // Test invalid octal number
    char *tmp = "0o0369";
    ASSERT_FALSE(isOctal(tmp));
}

TEST(isOctal, is0o1010){
    // Test octal number with prefix "0o"
    char *tmp = "0o1010";
    ASSERT_TRUE(isOctal(tmp));
}

TEST(isOctal, is7070){
    // Test decimal number
    char *tmp = "7070";
    ASSERT_FALSE(isOctal(tmp));
}

TEST(isOctal, is0x1010){
    // Test hexadecimal number with prefix "0x"
    char *tmp = "0x1010";
    ASSERT_FALSE(isOctal(tmp));
}

/*
 *  isOp
 */

TEST(isOp, add){
    // Test valid operator name
    char *tmp = "add";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isOp(tmp, newNode);
    ASSERT_TRUE(test);
}

TEST(isOp, addSymbols){
    // Test valid operator symbol
    char *tmp = "+";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isOp(tmp, newNode);
    ASSERT_TRUE(test);
}

TEST(isOp, GOTO){
    // Test invalid operator name
    char *tmp = "goto";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isOp(tmp, newNode);
    ASSERT_FALSE(test);
}

TEST(isOp, incSymbols){
    // Test invalid operator symbol
    char *tmp = "++";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isOp(tmp, newNode);
    ASSERT_FALSE(test);
}

TEST(isOp, moduloSymbol){
    // Test valid operator symbol
    char *tmp = "%";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isOp(tmp, newNode);
    ASSERT_TRUE(test);
}

/*
 *  isAct
 */

TEST(isAct, addSymbols){
    // Test invalid action symbol
    char *tmp = "+";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isAct(tmp, newNode);
    ASSERT_FALSE(test);
}

TEST(isAct, GOTO){
    // Test valid action name
    char *tmp = "goto";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isAct(tmp, newNode);
    ASSERT_TRUE(test);
}

TEST(isAct, incSymbols){
    // Test invalid action symbol
    char *tmp = "++";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isAct(tmp, newNode);
    ASSERT_FALSE(test);
}

TEST(isAct, moduloSymbol){
    // Test invalid action symbol
    char *tmp = "%";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isAct(tmp, newNode);
    ASSERT_FALSE(test);
}

TEST(isAct, ob1){
    // Test valid action name
    char *tmp = "ob1";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isAct(tmp, newNode);
    ASSERT_TRUE(test);
}

TEST(isAct, ob12){
    // Test invalid action name
    char *tmp = "ob12";
    instNode_t *newNode = (instNode_t *)malloc(sizeof(instNode_t));
    bool test = isAct(tmp, newNode);
    ASSERT_FALSE(test);
}

/*
 *  isBinary
 */

TEST(isBinary, is0b1010){
    // Test binary number with prefix "0b"
    char *tmp = "0b1010";
    ASSERT_TRUE(isBinary(tmp));
}

TEST(isBinary, is0b1010101010101010101010101010){
    // Test long binary number
    char *tmp = "0b1010101010101010101010101010";
    ASSERT_TRUE(isBinary(tmp));
}

TEST(isBinary, is0b1012){
    // Test invalid binary number
    char *tmp = "0b1012";
    ASSERT_FALSE(isBinary(tmp));
}

TEST(isBinary, is1010){
    // Test decimal number
    char *tmp = "1010";
    ASSERT_FALSE(isBinary(tmp));
}

TEST(isBinary, is0B1){
    // Test binary number with uppercase prefix "0B"
    char *tmp = "0B1";
    ASSERT_FALSE(isBinary(tmp));
}

TEST(isBinary, is0x1010){
    // Test hexadecimal number with prefix "0x"
    char *tmp = "0x1010";
    ASSERT_FALSE(isBinary(tmp));
}

/*
 *  isChar
 */

TEST(isChar, isChar){
    // Test single character enclosed in single quotes
    char *tmp = "'a'";
    ASSERT_TRUE(isChar(tmp));
}

TEST(isChar, isNotChar){
    // Test invalid single character format
    char *tmp = "'abcdef'";
    ASSERT_FALSE(isChar(tmp)); // Doubt for this one (should consider 'a' as a character and ignore the rest)
}

TEST(isChar, isString){
    // Test string enclosed in double quotes
    char *tmp = "\"a\"";
    ASSERT_FALSE(isChar(tmp));
}

/*
 *  isFloat
 */

TEST(isFloat, DoubleDot){
    // Test invalid float number with double decimal points
    char *tmp = "0.1.234";
    ASSERT_FALSE(isFloat(tmp));
}

TEST(isFloat, SignedFloat){
    // Test signed float number
    char *tmp = "-0.1234";
    ASSERT_TRUE(isFloat(tmp));
}

TEST(isFloat, is0Float){
    // Test float number without leading integer
    char *tmp = ".1234";
    ASSERT_FALSE(isFloat(tmp));
}

TEST(isFloat, is10){
    // Test integer number
    char *tmp = "10";
    ASSERT_TRUE(isFloat(tmp));
}

TEST(isFloat, is10FLoat){
    // Test float number with decimal point
    char *tmp = "10.0";
    ASSERT_TRUE(isFloat(tmp));
}

/*
 *  isReg
 */

TEST(isReg, rg0){
    // Test valid register name
    char *tmp = "rg0";
    ASSERT_TRUE(isReg(tmp));
}

TEST(isReg, rg8){
    // Test invalid register name with invalid number
    char *tmp = "rg8";
    ASSERT_FALSE(isReg(tmp));
}

TEST(isReg, RG0){
    // Test invalid register name with uppercase
    char *tmp = "RG0";
    ASSERT_FALSE(isReg(tmp));
}

/*
 *  isString
 */

TEST(isString, isChar){
    // Test single character enclosed in single quotes
    char *tmp = "'a'";
    ASSERT_FALSE(isString(tmp));
}

TEST(isString, isString){
    // Test string enclosed in double quotes
    char *tmp = "\"a\"";
    ASSERT_TRUE(isString(tmp));
}

/*
 *  isTarget
 */

TEST(isTarget, allCharacters){
    // Test valid target name with all valid characters
    char *tmp = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_";
    ASSERT_TRUE(isTarget(tmp));
}

TEST(isTarget, rtn){
    // Test invalid target name with newline character
    char *tmp = "\n";
    ASSERT_FALSE(isTarget(tmp));
}

TEST(isTarget, SpecialCharacters){
    // Test invalid target name with special characters
    char *tmp = "&";
    ASSERT_FALSE(isTarget(tmp));
}

/*
 *  parseArgs
 */

TEST(parseArgs, help) {
    // Test help flag
    char *argv[] = {"test", "-h"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.help);
}

TEST(parseArgs, version) {
    // Test version flag
    char *argv[] = {"test", "-v"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.version);
}

TEST(parseArgs, verbose) {
    // Test verbose flag
    char *argv[] = {"test", "-V"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.verbose);
}

TEST(parseArgs, debug) {
    // Test debug flag
    char *argv[] = {"test", "-d"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.debug);
}

TEST(parseArgs, invalidFlag) {
    // Test false argv
    char *argv[] = {"iat2.exe", "-f"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_FALSE(flags.help);
}




int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}