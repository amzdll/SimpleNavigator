cmake_minimum_required(VERSION 3.21)
project(SimpleNavigator LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)

enable_testing()
find_package(GTest REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
set(INCLUDE_DIR ${SRC_DIR}/graph_algorithms/include)

include_directories(graph_algorithms)
include_directories(graph)
include_directories(console_interface)
include_directories(libs)
include_directories(${GTEST_INCLUDE_DIRS})


add_library(graph_lib
        graph/s21_graph.cc
        graph/s21_graph.h
)

add_library(graph_algorithms_lib
        graph_algorithms/include
        graph_algorithms/source/bfs_dfc.cc
        graph_algorithms/source/shortest_paths.cc
        graph_algorithms/source/minimum_spanning_tree.cc
        graph_algorithms/source/ant_algorithm.cc
)

add_executable(SimpleNavigator
        console_interface/console_interface.cc
        main.cc
)

add_executable(Tests
        tests/test_runner.cc
        graph_algorithms/source/s21_graph_algorithms.cc
        graph_algorithms/source/helpers.cc
        graph/s21_graph.cc
        )

add_executable(GraphAlgorithmTests
        tests/graph_algorithms_test.cc
        graph/s21_graph.cc
        graph/s21_graph.h
        libs/matrix.h
        tests/test_runner.cc
        graph_algorithms/source/shortest_paths.cc
        graph_algorithms/source/minimum_spanning_tree.cc
        graph_algorithms/source/ant_algorithm.cc)



target_compile_options(SimpleNavigator PRIVATE -Wall -Wextra -Werror)
#target_link_libraries(SimpleNavigator )
target_link_libraries(Tests pthread gtest)

#add_custom_target(Format
#        COMMAND clang-format --style=google -n ${SOURCES}
#        COMMENT "Check format C++ code in project"
#        )
#
#add_custom_target(pre-commit
#        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target Format
#        COMMAND make test
#        )

target_include_directories(graph_algorithms_lib PUBLIC ${INCLUDE_DIR})
target_include_directories(graph_lib PUBLIC ${INCLUDE_DIR})

target_link_libraries(SimpleNavigator PRIVATE
        graph_lib
        graph_algorithms_lib

        pthread
)

add_test(NAME RunTests COMMAND Tests)


