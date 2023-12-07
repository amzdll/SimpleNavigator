set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.21)
project(SimpleNavigator LANGUAGES CXX)

enable_testing()
#find_package(GTest REQUIRED)
#find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(graph_lib)
add_subdirectory(app_interfaces/graphical_interface)
