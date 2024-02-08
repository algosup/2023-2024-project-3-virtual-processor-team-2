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
 *  parseArgs
 */

// Test help flag
TEST(parseArgs, help) {
char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-h")};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_TRUE(flags.help);
}
// Test version flag
TEST(parseArgs, version) {
  char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-v")};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_TRUE(flags.version);
}
// Test verbose flag
TEST(parseArgs, verbose) {
  char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-V")};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_TRUE(flags.verbose);
}
// Test debug flag
TEST(parseArgs, debug) {
  char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-d")};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_TRUE(flags.debug);
}
// Test false argv
TEST(parseArgs, invalidFlag) {
  char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-a")};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_FALSE(flags.help);
}

/*
 *  checkAOPFile
 */

// this test won't display a message because the test just above already deals with the same function.
TEST(checkAOPFile, invalidFileName) {
  char* invalidFileName = const_cast<char *>("test.txt"); // Replace fileName with an invalid file name
  checkAOPFile(invalidFileName);
  ASSERT_TRUE(EXIT_FAILURE);
}
/*
 *  isInt
 */

TEST(isInt, is0){
  char *tmp = const_cast<char *>("0");
  ASSERT_TRUE(isInt(tmp));
}
TEST(isInt, is10){
  char *tmp = const_cast<char *>("10");
  ASSERT_TRUE(isInt(tmp));
}
TEST(isInt, isN10){
  char *tmp = const_cast<char *>("-10");
  ASSERT_TRUE(isInt(tmp));
}
TEST(isInt, isA10){
  char *tmp = const_cast<char *>("A10");
  ASSERT_FALSE(isInt(tmp));
}
TEST(isInt, isFloat){
  char *tmp = const_cast<char *>("10.10");
  ASSERT_FALSE(isInt(tmp));
}

/*
 *  isBinary
 */

TEST(isBinary, is0b1010){
  char *tmp = const_cast<char *>("0b1010");
  ASSERT_TRUE(isBinary(tmp));
}
TEST(isBinary, is0B1){
  char *tmp = const_cast<char *>("0B1");
  ASSERT_FALSE(isBinary(tmp));
}
TEST(isBinary, is0x1010){
  char *tmp = const_cast<char *>("0x1010");
  ASSERT_FALSE(isBinary(tmp));
}
TEST(isBinary, is0b1012){
  char *tmp = const_cast<char *>("0b1012");
  ASSERT_FALSE(isBinary(tmp));
}
TEST(isBinary, is0b1010101010101010101010101010){
  char *tmp = const_cast<char *>("0b1010101010101010101010101010");
  ASSERT_TRUE(isBinary(tmp));
}
TEST(isBinary, is1010){
  char *tmp = const_cast<char *>("1010");
  ASSERT_FALSE(isBinary(tmp));
}

/*
 *  isOctal
 */

TEST(isOctal, is0o1010){
  char *tmp = const_cast<char *>("0o1010");
  ASSERT_TRUE(isOctal(tmp));
}
TEST(isOctal, is0O7){
  char *tmp = const_cast<char *>("0O7");
  ASSERT_FALSE(isOctal(tmp));
}
TEST(isOctal, is0x1010){
  char *tmp = const_cast<char *>("0x1010");
  ASSERT_FALSE(isOctal(tmp));
}
TEST(isOctal, is0o0369){
  char *tmp = const_cast<char *>("0o0369");
  ASSERT_FALSE(isOctal(tmp));
}
TEST(isOctal, is0o0123456701234567){
  char *tmp = const_cast<char *>("0o0123456701234567");
  ASSERT_TRUE(isOctal(tmp));
}
TEST(isOctal, is7070){
  char *tmp = const_cast<char *>("7070");
  ASSERT_FALSE(isOctal(tmp));
}

/*
 *  isHex
 */

TEST(isHex, is0x0Af){
  char *tmp = const_cast<char *>("0x0Af");
  ASSERT_TRUE(isHex(tmp));
}
TEST(isHex, is0XF){
  char *tmp = const_cast<char *>("0XF");
  ASSERT_FALSE(isHex(tmp));
}
TEST(isHex, is0x1010){
  char *tmp = const_cast<char *>("0bFFF");
  ASSERT_FALSE(isHex(tmp));
}
TEST(isHex, is0x0AFG){
  char *tmp = const_cast<char *>("0x0AFG");
  ASSERT_FALSE(isHex(tmp));
}
TEST(isHex, is0x09AF){
  char *tmp = const_cast<char *>("0x09AF");
  ASSERT_TRUE(isHex(tmp));
}
TEST(isHex, is09aF){
  char *tmp = const_cast<char *>("09aF");
  ASSERT_FALSE(isHex(tmp));
}

/*
 *  isFloat
 */
TEST(isFloat, is10FLoat){
  char *tmp = const_cast<char *>("10.0");
  ASSERT_TRUE(isFloat(tmp));
}
TEST(isFloat, is0Float){
  char *tmp = const_cast<char *>("0.1234");
  ASSERT_TRUE(isFloat(tmp));
}
TEST(isFloat, isDotFirst){
  char *tmp = const_cast<char *>(".1234");
  ASSERT_FALSE(isFloat(tmp));
}
TEST(isFloat, DoubleDot){
  char *tmp = const_cast<char *>("0.1.234");
  ASSERT_FALSE(isFloat(tmp));
}
TEST(isFloat, SignedFloat){
  char *tmp = const_cast<char *>("-0.1234");
  ASSERT_TRUE(isFloat(tmp));
}

/*
 *  isChar
 */

TEST(isChar, isString){
  char *tmp = const_cast<char *>("\"a\"");
  ASSERT_FALSE(isChar(tmp));
}
TEST(isChar, isChar){
  char *tmp = const_cast<char *>("'a'");
  ASSERT_TRUE(isChar(tmp));
}
TEST(isChar, isNotChar){
  char *tmp = const_cast<char *>("'abcdef'"); // Doubt for this one (should concider a as char and ignore the rest)
  ASSERT_FALSE(isChar(tmp));
}

/*
 *  isString
 */

TEST(isString, isString){
  char *tmp = const_cast<char *>("\"a\"");
  ASSERT_TRUE(isString(tmp));
}
TEST(isString, isChar){
  char *tmp = const_cast<char *>("'a'");
  ASSERT_FALSE(isString(tmp));
}

/*
 *  isReg
 */

TEST(isReg, rg0){
  char *tmp = const_cast<char *>("rg0");
  ASSERT_TRUE(isReg(tmp));
}
TEST(isReg, RG0){
  char *tmp = const_cast<char *>("RG0");
  ASSERT_FALSE(isReg(tmp));
}
TEST(isReg, rg8){
  char *tmp = const_cast<char *>("rg8");
  ASSERT_FALSE(isReg(tmp));
}

/*
 *  isTarget
 */

TEST(isTarget, allCharacters){
  char *tmp = const_cast<char *>("azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_\0");  // Is it ok to start or finish by _ ?
  ASSERT_TRUE(isTarget(tmp));
}
TEST(isTarget, SpecialCharacters){
  char *tmp = const_cast<char *>("&");
  ASSERT_FALSE(isTarget(tmp));
}
TEST(isTarget, rtn){
  char *tmp = const_cast<char *>("\n");
  ASSERT_FALSE(isTarget(tmp));
}



int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}