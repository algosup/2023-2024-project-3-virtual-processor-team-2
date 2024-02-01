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

TEST(parseArgs, help) {
  char *argv[] = {"test", "-h"};
  int argc = 2;
  flags_t flags = parseArgs(argc, argv);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}