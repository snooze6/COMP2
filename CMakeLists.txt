set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/dist)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

cmake_minimum_required(VERSION 3.5)
project(P1___Comp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lfl")

# Recursive add folders
file(GLOB ENDF6_SRC_TOP)
file(GLOB_RECURSE ENDF6_SRC_NESTED
        src/external/*.c
        src/external/*.h
        src/helpers/*.c
        src/helpers/*.h
        src/input_system/*.c
        src/input_system/*.h
        src/lexycal_analyzer/*.c
        src/lexycal_analyzer/*.h
        src/config.c
        src/config.h
        src/main.c
        src/definitions/definitions.h
    )
set(ENDF6_SRC ${ENDF6_SRC_TOP} ${ENDF6_SRC_NESTED})

add_executable(P1___Comp ${ENDF6_SRC})