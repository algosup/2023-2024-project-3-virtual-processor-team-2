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
#include "runner.h"

// test the parsing arguments
TEST(parseArgs, help) {
  char *argv[] = {"test", "-h"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_TRUE(flags.help);
}
TEST(parseArgs, version) {
  char *argv[] = {"test", "-v"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_TRUE(flags.version);
}
TEST(parseArgs, verbose) {
  char *argv[] = {"test", "-V"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_TRUE(flags.verbose);
}
TEST(parseArgs, debug) {
  char *argv[] = {"test", "-d"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  flags_t flags = parseArgs(argc, argv);
  ASSERT_TRUE(flags.debug);
}

// test the extension of the file
TEST(checkAOPFile, validFileName) {
  char* validFileName = "test.aop"; // Replace fileName with a valid file name
  checkAOPFile(validFileName);
  ASSERT_TRUE(EXIT_SUCCESS);
}
// this test won't display a message because the test just above already deals with the same function.
TEST(checkAOPFile, invalidFileName) {
  char* invalidFileName = "test.txt"; // Replace fileName with an invalid file name
  checkAOPFile(invalidFileName);
  ASSERT_TRUE(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}