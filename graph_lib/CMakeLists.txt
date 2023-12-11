set(CMAKE_CXX_COMPILER g++)
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

add_library(GraphLibrary STATIC
        ${HEADERS}
        ${SOURCES}
)

target_include_directories(GraphLibrary PUBLIC libs include)