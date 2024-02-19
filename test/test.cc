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

// =========================================================================
// =============================  PARSER  ==================================
// =========================================================================


/*
 *  parseArgs
 */
TEST(parseArgs, help) {
    asm_error_t *errData = initErrorFile("errors.log", fileName);
    // Test help flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-h")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.help);
}
TEST(parseArgs, version) {
    asm_error_t *errData = initErrorFile("errors.log", fileName);
    // Test version flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-v")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.version);
}
TEST(parseArgs, verbose) {
    asm_error_t *errData = initErrorFile("errors.log", fileName);
    // Test verbose flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-V")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.verbose);
}
TEST(parseArgs, debug) {
    asm_error_t *errData = initErrorFile("errors.log", fileName);
    // Test debug flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-d")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv);
    ASSERT_TRUE(flags.debug);
}

TEST(parseArgs, invalidFlag) {
    asm_error_t *errData = initErrorFile("errors.log", fileName);
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
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("+");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_ADD);
}
TEST(isOp, sub) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("-");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_SUB);
}
TEST(isOp, mul) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("*");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_MUL);
}
TEST(isOp, div) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("/");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_DIV);
}
TEST(isOp, incOp) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("=");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_FALSE(isThatKind);
  ASSERT_FALSE(newNode->op == OP_ADD);
}
TEST(isOp, push) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("push");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_PUSH);
}
TEST(isOp, pop) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("pop");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_POP);
}
TEST(isOp, goto) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("goto");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_GOTO);
}
TEST(isOp, call) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("call");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_CALL);
}
TEST(isOp, and) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("&");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_B_AND);
}
TEST(isOp, or) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("|");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_B_OR);
}
TEST(isOp, not) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("!");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_B_NOT);
}
TEST(isOp, xor) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("^");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_B_XOR);
}
TEST(isOp, mod) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("%");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_MOD);
}
TEST(isOp, shr) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>(">>");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_R_SHIFT);
}
TEST(isOp, shl) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("<<");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_L_SHIFT);
}
TEST(isOp, inc) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("++");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_ADD);
}
TEST(isOp, dec) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("--");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_SUB);
}
TEST(isOp, lab) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("lab");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_LAB);
}
TEST(isOp, var) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("var");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_VAR);
}
TEST(isOp, ret) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("ret");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_RET);
}
TEST(isOp, int) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("int");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, ngr) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("ngr");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, draw) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("draw");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, ob1) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("ob1");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}

TEST(isOp, IntOR) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("or");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}

TEST(isOp, IntIF_AND) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("if_and");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_XOR) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("if_xor");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_LT) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("if_lt");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_LTE) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("if_lte");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_GT) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("if_gt");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_GTE) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("if_gte");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_EQ) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("if_eq");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_NEQ) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("if_neq");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, pusha) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("pusha");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, popa) {
  asm_error_t *errData = initErrorFile("errors.log", fileName);
  char *inst = const_cast<char *>("popa");

  instNode_t *newNode = createEmptyInstNode();
  bool isThatKind = isOp(inst, newNode, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}


// =========================================================================
// =============================  BUILDER  =================================
// =========================================================================

TEST(buildProgram, CorrectBuild) {
//   asm_error_t *errData = initErrorFile("errors.log", fileName);
//   char *inst = const_cast<char *>("popa");

//   instNode_t *newNode = createEmptyInstNode();
//   bool isThatKind = isOp(inst, newNode, errData);

//   ASSERT_TRUE(isThatKind);
//   ASSERT_TRUE(newNode->op == OP_INT);
}



int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}