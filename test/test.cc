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

TEST(ParseArgs, SetsHelpFlagWhenHelpOptionIsProvided) {
    // Arrange
    char *argv[] = {"test", "-h"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    // Act
    flags_t flags = parseArgs(argc, argv);

    // Assert
    ASSERT_TRUE(flags.help);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}