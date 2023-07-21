cmake_minimum_required(VERSION 3.25)
project(SimpleNavigator C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)
include_directories(src/include)

add_executable(SimpleNavigator
        src/include/graph/s21_graph.h)
