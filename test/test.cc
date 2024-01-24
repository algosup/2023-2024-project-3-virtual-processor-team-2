#include <cassert>
#include <cstdlib>
#include <cstring>

#include "gtest/gtest.h"
#include "parser.h"
#include "runner.h"

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}