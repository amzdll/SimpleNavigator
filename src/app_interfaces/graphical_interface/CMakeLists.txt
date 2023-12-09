cmake_minimum_required(VERSION 3.5)
project(graphical_interface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


file(GLOB_RECURSE SOURCES source/*.cc )
file(GLOB_RECURSE HEADERS  include/*.h )
file(GLOB_RECURSE FORMS  ui/*.ui)

set(GRAPHICAL_APPLICATION
        app_runner.cc

        ${HEADERS}
        ${SOURCES}
        ${FORMS}
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(graphical_interface MANUAL_FINALIZATION  ${GRAPHICAL_APPLICATION})
else ()
    add_executable(graphical_interface  ${GRAPHICAL_APPLICATION})
endif ()

target_link_libraries(graphical_interface PRIVATE Qt${QT_VERSION_MAJOR}::Widgets GraphLibrary)
target_include_directories(graphical_interface PUBLIC include ui)


if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(graphical_interface)
endif ()