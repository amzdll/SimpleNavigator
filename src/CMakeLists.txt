set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.21)
project(SimpleNavigator LANGUAGES CXX)

enable_testing()
find_package(GTest REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
set(INCLUDE_DIR ${SRC_DIR}/graph_algorithms/include)

include_directories(
        libs
        graph
        graph_algorithms
        console_interface
)

add_library(data_structures INTERFACE)

add_library(graph_lib
        graph/s21_graph.cc
        graph/s21_graph.h)

add_library(graph_algorithms_lib
        graph_algorithms/include
        graph_algorithms/source/bfs_dfc.cc
        graph_algorithms/source/shortest_paths.cc
        graph_algorithms/source/minimum_spanning_tree.cc
        graph_algorithms/source/ant_algorithm.cc
        graph_algorithms/source/helpers.cc
)


add_executable(SimpleNavigator
        main.cc
        console_interface/console_interface.cc
)

add_executable(Tests
        tests/test_runner.cc
        tests/graph_test.cc
#        tests/graph_algorithms_test.cc
)

target_include_directories(graph_algorithms_lib PUBLIC ${INCLUDE_DIR})
target_include_directories(graph_lib PUBLIC ${INCLUDE_DIR})
target_include_directories(data_structures INTERFACE libs/)

target_link_libraries(Tests
        pthread
        gtest
        ${GTEST_LIBRARIES}
        graph_lib
        graph_algorithms_lib
        data_structures
)

target_compile_options(SimpleNavigator PRIVATE -Wall -Wextra -Werror)
target_link_libraries(SimpleNavigator PRIVATE
        graph_lib
        graph_algorithms_lib
        data_structures
        pthread
)

add_test(NAME RunTests COMMAND Tests)


