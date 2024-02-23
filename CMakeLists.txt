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
  VERSION 1.1.1
  LANGUAGES CXX C
)

find_package(Threads REQUIRED)

add_executable(tests
  src/stringPlus.c
  src/parser.c
  src/builder.c
  src/debug.c
  src/error.c
  src/binExporter.c
  src/vProc.c
  src/vTerminal.c
  test/test.cc
  src/ast.c
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

add_executable(2at2
  src/stringPlus.c
  src/parser.c
  src/builder.c
  src/debug.c
  src/error.c
  src/binExporter.c
  src/2at2.c
  src/ast.c
)

target_include_directories(2at2
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_options(2at2
  PRIVATE
    -Wall -Wextra -pedantic -g -O2
)

set_target_properties(2at2
  PROPERTIES
    C_STANDARD 99
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

add_executable(vat2
    src/stringPlus.c
    src/debug.c
    src/error.c
    src/vat2.c
    src/vProc.c
    src/vTerminal.c
)

target_include_directories(vat2
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_options(vat2
  PRIVATE
    -Wall -Wextra -pedantic -g -O2
)

set_target_properties(vat2
  PROPERTIES
    C_STANDARD 99
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)