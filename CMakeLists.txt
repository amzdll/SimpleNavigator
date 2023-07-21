set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.25)
project(SimpleNavigator LANGUAGES CXX)

include_directories(.)
include_directories(src)
include_directories(src/include)



include_directories(src/include)
include_directories(src/include/graph)
include_directories(src/include/graph_algorithms)
include_directories(src/include/list)
include_directories(src/include/matrix)
include_directories(src/include/queue)
include_directories(src/include/stack)

add_executable(SimpleNavigator
        src/include/graph/s21_graph.cc
        src/include/graph/s21_graph.h
        src/include/graph_algorithms/s21_graph_algorithms.cc
        src/include/graph_algorithms/s21_graph_algorithms.h
        src/include/list/s21_list.cc
        src/include/list/s21_list.h
        src/include/matrix/s21_matrix_oop.cpp
        src/include/matrix/s21_matrix_oop.h
        src/include/queue/s21_queue.cc
        src/include/queue/s21_queue.h
        src/include/stack/s21_stack.cc
        src/include/stack/s21_stack.h)

