set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.21)
project(SimpleNavigator LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

enable_testing()
find_package(GTest REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs
        ${CMAKE_CURRENT_SOURCE_DIR}/graph
        ${CMAKE_CURRENT_SOURCE_DIR}/graph_algorithms
        ${CMAKE_CURRENT_SOURCE_DIR}/console_interface
)

set(PROJECT_SOURCES
        temp/1.cpp
        temp/2.cpp
        temp/2.h
        temp/2.ui
)

add_library(data_structures INTERFACE)

add_library(graph_lib
        source/graph/graph_file_manager.cc
        include/s21_graph.h)

add_library(graph_algorithms_lib
        include/s21_graph_algorithms.h
        source/graph_algorithms/bfs_dfc.cc
        source/graph_algorithms/shortest_paths.cc
        source/graph_algorithms/minimum_spanning_tree.cc
        source/graph_algorithms/traveling_salesman_problem.cc
        source/graph_algorithms/helpers.cc)

qt_add_executable(ui_ex
        ${PROJECT_SOURCES}
        MANUAL_FINALIZATION
)

add_executable(tests
        tests/graph_algorithms_test.cc
        tests/graph_test.cc)

add_executable(ant
        utils/ant_colony_optimization.cc
        utils/ant_colony_optimization.h)



target_link_libraries(ant PRIVATE
        pthread
        graph_lib
        graph_algorithms_lib
        data_structures)


target_include_directories(graph_algorithms_lib PUBLIC
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/graph
        ${CMAKE_CURRENT_SOURCE_DIR}/libs)

target_include_directories(graph_lib PUBLIC
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/graph
        ${CMAKE_CURRENT_SOURCE_DIR}/libs)

target_link_libraries(tests PRIVATE
        gtest_main
        pthread
        gtest
        ${GTEST_LIBRARIES}
        graph_lib
        graph_algorithms_lib
        data_structures)

target_link_libraries(ui_ex PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        gtest_main
        pthread
        gtest
        graph_lib
        graph_algorithms_lib
        data_structures)


if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ui_ex)
endif ()


add_test(NAME GraphTest COMMAND tests)
