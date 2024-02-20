/*
  This file is part of the test suite of at2 project
*/

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <array>

#include "gtest/gtest.h"
#include "ast.h"
#include "parser.h"
#include "builder.h"
#include "error.h"

char * fileName = const_cast<char *>("test.cc");

/*
 *  parseArgs
 */

TEST(parseArgs, help) {
    asm_error_t *errData = initErrorFile("errors.log");
    // Test help flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-h")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.help);
}
TEST(parseArgs, version) {
    asm_error_t *errData = initErrorFile("errors.log");
    // Test version flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-v")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.version);
}
TEST(parseArgs, verbose) {
    asm_error_t *errData = initErrorFile("errors.log");
    // Test verbose flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-V")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.verbose);
}
TEST(parseArgs, debug) {
    asm_error_t *errData = initErrorFile("errors.log");
    // Test debug flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-d")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.debug);
}

TEST(parseArgs, invalidFlag) {
    asm_error_t *errData = initErrorFile("errors.log");
    // Test false argv
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-a")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_FALSE(flags.help);
}

/*
 *  get isntruction
 */

TEST(getInst, normal) {
    asm_error_t *errData = initErrorFile("errors.log");
    char *line = const_cast<char *>("add r1, r2, r3\n");

    char *inst = getInst(line, 1, errData);
    ASSERT_STREQ(inst, "add");
}

TEST(getInst, noInst) {
    asm_error_t *errData = initErrorFile("errors.log");
    char *line = const_cast<char *>("r1, r2, r3\n");

    char *inst = getInst(line, 1, errData);
    ASSERT_STREQ(inst, "r1,");
}

/*
 *  get unstruction arguments
 */

TEST(getArgs, normal) {
    // Test input line
    char *line = const_cast<char *>("add r1, r2");
    // Call the function under test
    char **args = getInstArgs(line);

    // Check each argument
    ASSERT_STREQ(args[0], "r1");
    ASSERT_STREQ(args[1], "r2");

    // Free dynamically allocated memory
    for (int i = 0; i < 2; ++i) {
        delete[] args[i];
    }
    delete[] args;
}

TEST(getArgs, noComma) {
    // Test input line
    char *line = const_cast<char *>("add r1 r2");

    // Call the function under test
    char **args = getInstArgs(line);

    // Check each argument
    ASSERT_STREQ(args[0], "r1 r2");
    ASSERT_TRUE(args[1] == NULL);

    // Free dynamically allocated memory
    for (int i = 0; i < 2; ++i) {
        delete[] args[i];
    }
    delete[] args;
}

TEST(getArgs, noArgs) {
    // Test input line
    char *line = const_cast<char *>("ret\n");

    // Call the function under test
    char **args = getInstArgs(line);

    std::cout << args[0] << std::endl;
    std::cout << args[1] << std::endl;

    // Check each argument
    ASSERT_TRUE(args[0] == NULL);
    ASSERT_TRUE(args[1] == NULL);

    // Free dynamically allocated memory
    for (int i = 0; i < 2; ++i) {
        delete[] args[i];
    }
    delete[] args;
}

/*
 *  is op
 */

TEST(isOp, add) {
  asm_error_t *errData = initErrorFile("errors.log");
  char *inst = const_cast<char *>("add");

  instNode_t *newNode = createEmptyInstNode();

  varList_t *varList = createEmptyVarList();
  bool isThatKind = isOp(inst, newNode, varList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_ADD);
}

// TODO: Do for all instructions

// TODO: test build instruction


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}