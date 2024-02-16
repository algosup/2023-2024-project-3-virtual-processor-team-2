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

char * fileName = const_cast<char *>("test.cc");

/*
 *  parseArgs
 */

TEST(parseArgs, help) {
    error_t *errData = initErrorFile("errors.log", fileName);
    // Test help flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-h")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.help);
}
TEST(parseArgs, version) {
    error_t *errData = initErrorFile("errors.log", fileName);
    // Test version flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-v")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.version);
}
TEST(parseArgs, verbose) {
    error_t *errData = initErrorFile("errors.log", fileName);
    // Test verbose flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-V")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.verbose);
}
TEST(parseArgs, debug) {
    error_t *errData = initErrorFile("errors.log", fileName);
    // Test debug flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-d")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.debug);
}

TEST(parseArgs, invalidFlag) {
    error_t *errData = initErrorFile("errors.log", fileName);
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
    char *line = const_cast<char *>("add r1, r2, r3\n");

    char *inst = getInst(line);
    ASSERT_STREQ(inst, "add");
}

TEST(getInst, noInst) {
    char *line = const_cast<char *>("r1, r2, r3\n");

    char *inst = getInst(line);
    ASSERT_STREQ(inst, "r1,");
}

/*
 *  get unstruction arguments
 */

TEST(getArgs, normal) {
    // Test input line
    std::string line = "add r1, r2";

    // Convert the string to a C-style string
    char *c_line = const_cast<char *>(line.c_str());

    // Call the function under test
    char **args = getInstArgs(c_line);

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
    std::string line = "add r1 r2";

    // Convert the string to a C-style string
    char *c_line = const_cast<char *>(line.c_str());

    // Call the function under test
    char **args = getInstArgs(c_line);

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
    std::string line = "ret\n";

    // Convert the string to a C-style string
    char *c_line = const_cast<char *>(line.c_str());

    // Call the function under test
    char **args = getInstArgs(c_line);

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
 *  parse line
 */

TEST(parseLine, normal) {
    error_t *errData = initErrorFile("errors.log", fileName);

    char* line = const_cast<char *>("add rg1, 7");
    
    instNode *node = parseLine(line, 1, 1, errData);
    ASSERT_TRUE(node->id == 1);
    ASSERT_TRUE(node->lineNb == 1);
    ASSERT_TRUE(node->op == OP_ADD);
    ASSERT_TRUE(node->inputReg == RG_1);
    ASSERT_FALSE(node->isInter);
    ASSERT_STREQ(node->arg0, NULL);
    ASSERT_STREQ(node->arg1, "7");
}

// TODO: Do for all instructions
TEST(parseLine, interrupt){
    error_t *errData = initErrorFile("errors.log", fileName);

    char* line = const_cast<char *>("draw \"test\"\n");
    
    instNode *node = parseLine(line, 1, 1, errData);
    ASSERT_TRUE(node->id == 1);
    ASSERT_TRUE(node->lineNb == 1);
    ASSERT_TRUE(node->op == OP_INT);
    ASSERT_TRUE(node->isInter);
    ASSERT_TRUE(node->inter == INT_DRAW);
    ASSERT_STREQ(node->arg0, NULL);
    ASSERT_STREQ(node->arg1, "test");
}
TEST(parseLine, opWithouArgs) {
    error_t *errData = initErrorFile("errors.log", fileName);

    char* line = const_cast<char *>("ret\n");
    
    instNode *node = parseLine(line, 1, 1, errData);
    ASSERT_TRUE(node->id == 1);
    ASSERT_TRUE(node->lineNb == 1);
    ASSERT_TRUE(node->op == OP_RET);
    ASSERT_TRUE(node->arg0 == NULL);
    ASSERT_TRUE(node->arg1 == NULL);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}