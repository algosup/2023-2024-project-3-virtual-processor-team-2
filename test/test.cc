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
const char *testErrorFile = const_cast<char *>("error.log");

// =========================================================================
// =============================  PARSER  ==================================
// =========================================================================


/*
 *  parseArgs
 */
TEST(parseArgs, help) {
    asm_error_t *errData = initErrorFile(testErrorFile);
    // Test help flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-h")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv, errData);
    ASSERT_TRUE(flags.help);
}
TEST(parseArgs, version) {
    asm_error_t *errData = initErrorFile(testErrorFile);
    // Test version flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-v")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv, errData);
    ASSERT_TRUE(flags.version);
}
TEST(parseArgs, verbose) {
    asm_error_t *errData = initErrorFile(testErrorFile);
    // Test verbose flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-V")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv, errData);
    ASSERT_TRUE(flags.verbose);
}
TEST(parseArgs, debug) {
    asm_error_t *errData = initErrorFile(testErrorFile);
    // Test debug flag
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-d")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv, errData);
    ASSERT_TRUE(flags.debug);
}

TEST(parseArgs, invalidFlag) {
    asm_error_t *errData = initErrorFile(testErrorFile);
    // Test false argv
    char *argv[] = {const_cast<char *>("test"), const_cast<char *>("-a")};
    int argc = sizeof(argv) / sizeof(argv[0]);
    flags_t flags = parseArgs(argc, argv, errData);
    ASSERT_FALSE(flags.help);
}
/*
 *  get isntruction
 */
TEST(getInst, normal) {
    asm_error_t *errData = initErrorFile(testErrorFile);
    char *line = const_cast<char *>("add r1, r2, r3\n");

    char *inst = getInst(line, 1, errData);
    ASSERT_STREQ(inst, "add");
}

TEST(getInst, noInst) {
    asm_error_t *errData = initErrorFile(testErrorFile);
    char *line = const_cast<char *>("r1, r2, r3\n");

    char *inst = getInst(line, 1, errData);
    ASSERT_STREQ(inst, "r1,");
}
/*
 *  get unstruction arguments
 */
TEST(getArgs, normal) {
    asm_error_t *errData = initErrorFile(testErrorFile);
    // Test input line
    char *line = const_cast<char *>("add r1, r2");
    // Call the function under test
    char **args = getInstArgs(line, 1, errData);

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
    asm_error_t *errData = initErrorFile(testErrorFile);
    // Test input line
    char *line = const_cast<char *>("add r1 r2");

    // Call the function under test
    char **args = getInstArgs(line, 1, errData);

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
    asm_error_t *errData = initErrorFile(testErrorFile);
    // Test input line
    char *line = const_cast<char *>("ret\n");

    // Call the function under test
    char **args = getInstArgs(line, 1, errData);

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
  asm_error_t *errData = initErrorFile(testErrorFile);
  char *inst = const_cast<char *>("add");

  instNode_t *newNode = createEmptyInstNode(errData);

  varList_t *varList = createEmptyVarList();
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_ADD);
}
TEST(isOp, sub) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("-");
  varList_t *varList = createEmptyVarList();
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_SUB);
}
TEST(isOp, mul) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("*");
  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_MUL);
}
TEST(isOp, div) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("/");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_DIV);
}
TEST(isOp, incOp) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("=");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_FALSE(isThatKind);
  ASSERT_FALSE(newNode->op == OP_ADD);
}
TEST(isOp, push) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("push");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_PUSH);
}
TEST(isOp, pop) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("pop");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_POP);
}
TEST(isOp, goto) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("goto");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_GOTO);
}
TEST(isOp, call) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("call");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_CALL);
}
TEST(isOp, and) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("&");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_B_AND);
}
TEST(isOp, or) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("|");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_B_OR);
}
TEST(isOp, not) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("!");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_B_NOT);
}
TEST(isOp, xor) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("^");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_B_XOR);
}
TEST(isOp, mod) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("%");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_MOD);
}
TEST(isOp, shr) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>(">>");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_R_SHIFT);
}
TEST(isOp, shl) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("<<");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_L_SHIFT);
}
TEST(isOp, inc) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("++");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_ADD);
}
TEST(isOp, dec) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("--");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_SUB);
}
TEST(isOp, lab) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("lab");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_LAB);
}
TEST(isOp, var) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("var");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_VAR);
}
TEST(isOp, ret) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("ret");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_RET);
}
TEST(isOp, int) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("int");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, ngr) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("ngr");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, draw) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("draw");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, ob1) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("ob1");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}

TEST(isOp, IntOR) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_or");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}

TEST(isOp, IntIF_AND) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_and");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_XOR) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_xor");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_LT) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_lt");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_LTE) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_lte");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_GT) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_gt");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_GTE) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_gte");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_EQ) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_eq");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, IntIF_NEQ) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("if_neq");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, pusha) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("pusha");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}
TEST(isOp, popa) {
  asm_error_t *errData = initErrorFile(fileName);
  char *inst = const_cast<char *>("popa");

  varList_t *varList = createEmptyVarList();  
  instNode_t *newNode = createEmptyInstNode(errData);
  labelList_t *labelList = createEmptyLabelList();
  bool isThatKind = isOp(inst, newNode, varList, labelList, errData);

  ASSERT_TRUE(isThatKind);
  ASSERT_TRUE(newNode->op == OP_INT);
}

TEST(parseFile, Parsing) {
  asm_error_t *errData = initErrorFile(fileName);
  varList_t *varList = createEmptyVarList();  
  instList_t *nodeList = createEmptyInstList();
  labelList_t *labelList = createEmptyLabelList();

  char *fileName = const_cast<char *>("../test/aop/test.aop");
  bool parsing = false;
  parseFile(nodeList, fileName, varList, labelList, errData);
  if (nodeList->head != NULL) {
    parsing = true;
  }
  ASSERT_TRUE(parsing == true);
  ASSERT_TRUE(nodeList->head->op == OP_MOV);
  ASSERT_TRUE(nodeList->head->inputReg == RG_0);
  ASSERT_STREQ(nodeList->head->arg1, "2");
}

// =========================================================================
// =============================  BUILDER  =================================
// =========================================================================


TEST(getRegKind, rg0) {
  asm_error_t *errData = initErrorFile(fileName);
  char *reg = const_cast<char *>("rg0");
  instNode_t *newNode = createEmptyInstNode(errData);

  newNode->inputReg = getRegKind(reg, 1, errData);

  ASSERT_TRUE(newNode->inputReg == RG_0);
}

TEST(getRegKind, rg8) {
  asm_error_t *errData = initErrorFile(fileName);
  char *reg = const_cast<char *>("rg8");
  instNode_t *newNode = createEmptyInstNode(errData);

  newNode->inputReg = getRegKind(reg, 1, errData);

  ASSERT_FALSE(newNode->inputReg == RG_7);
}

TEST(getRegKind, r3) {
  asm_error_t *errData = initErrorFile(fileName);
  char *reg = const_cast<char *>("r3");
  instNode_t *newNode = createEmptyInstNode(errData);

  newNode->inputReg = getRegKind(reg, 1, errData);

  ASSERT_FALSE(newNode->inputReg == RG_3);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}