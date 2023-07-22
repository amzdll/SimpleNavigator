set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.21)
project(SimpleNavigator LANGUAGES CXX)

find_package(Curses REQUIRED)

include_directories(.)
include_directories(src)
include_directories(src/include)



include_directories(src/include)
include_directories(src/graph)
include_directories(src/graph_algorithms)

include_directories(src/include/list)
include_directories(src/include/matrix)
include_directories(src/include/queue)
include_directories(src/include/stack)

add_executable(SimpleNavigator
        src/graph/s21_graph.cc
        src/graph/s21_graph.h
        src/graph_algorithms/s21_graph_algorithms.cc
        src/graph_algorithms/s21_graph_algorithms.h
        src/include/list/s21_list.cc
        src/include/list/s21_list.h
        src/include/matrix/s21_matrix_oop.cpp
        src/include/matrix/s21_matrix_oop.h
        src/include/queue/s21_queue.cc
        src/include/queue/s21_queue.h
        src/include/stack/s21_stack.cc
        src/include/stack/s21_stack.h src/console_interface/console_interface.h src/console_interface/console_interface.cc)

target_link_libraries(SimpleNavigator pthread)
