# How to use with mingw: (Windows)
#   cmake -S . -B Build -G "MinGW Makefiles"
#   cd Build
#   mingw32-make

# How to use with msys2: (Windows)
#   cmake -S . -B Build -G "MSYS Makefiles"
#   cd Build
#   make
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

project(
  Interpreter-AT2
  VERSION 1.0
  LANGUAGES CXX C
)

find_package(Threads REQUIRED)

add_executable(tests
  parser.c
  builder.c
  runner.c
  tests.cc
  googletest/googletest/src/gtest-all.cc
)

target_include_directories(tests
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/test"
)

target_link_libraries(tests
  PRIVATE
    Threads::Threads
)

target_compile_options(tests
  PRIVATE
    -Wall -Wextra -pedantic -g -O2
)

set_target_properties(tests
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

add_executable(iat2
    parser.c
    builder.c
    runner.c
    iat2.c
)

target_include_directories(iat2
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_options(iat2
  PRIVATE
    -Wall -Wextra -pedantic -g -O2
)

set_target_properties(iat2
  PROPERTIES
    C_STANDARD 99
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)