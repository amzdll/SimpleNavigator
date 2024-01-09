cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HEADERS
        include/*.h
        utils/*.h
        libs/*.h
)

file(GLOB_RECURSE SOURCES
        source/*.cc
        utils/*.cc
)

include_directories(source include utils libs)

add_executable(apps
        ${SOURCES}
)


add_library(GraphLibrary STATIC
        ${HEADERS}
        ${SOURCES}
)

target_include_directories(GraphLibrary PUBLIC libs include)
