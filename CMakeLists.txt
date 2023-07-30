cmake_minimum_required(VERSION 3.21)
project(SimpleNavigator LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)

enable_testing()
find_package(GTest REQUIRED)


file(GLOB_RECURSE SOURCES
        "src/graph/*.cc"
        "src/graph/*.h"
        "src/graph_algorithms/*.cc"
        "src/graph_algorithms/*.h"
        "src/utils/list/*.hpp"
        "src/utils/matrix/*.hpp"
        "src/utils/queue/*.hpp"
        "src/utils/stack/*.hpp"
        )

add_executable(Tests
        src/tests/test_runner.cc
        src/graph_algorithms/s21_graph_algorithms.cc
        src/graph_algorithms/s21_graph_algorithms_utils.cc
        src/graph/s21_graph.cc
        )

add_executable(GraphAlgorithmTests
        src/tests/graph_algorithms_test.cc

        src/graph/s21_graph.cc
        src/graph/s21_graph.h
        src/utils/s21_matrix.hpp
        src/tests/test_runner.cc)

add_executable(SimpleNavigator
        src/console_interface/console_interface.cc
        src/graph/s21_graph.cc
        src/graph_algorithms/s21_graph_algorithms.cc
        src/graph_algorithms/s21_graph_algorithms_utils.cc
        )


target_compile_options(SimpleNavigator PRIVATE -Wall -Wextra -Werror)
target_link_libraries(SimpleNavigator pthread)
target_link_libraries(Tests pthread gtest)

add_custom_target(Format
        COMMAND clang-format --style=google -n ${SOURCES}
        COMMENT "Check format C++ code in project"
        )

add_custom_target(pre-commit
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target Format
        COMMAND make test
        )

add_test(NAME RunTests COMMAND Tests)


