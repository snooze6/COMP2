cmake_minimum_required(VERSION 3.5)
project(P1___Comp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Recursive add folders
file(GLOB ENDF6_SRC_TOP src/*.c)
file(GLOB_RECURSE ENDF6_SRC_NESTED
        src/definitions/*.c
        src/definitions/*.h
        src/external/*.c
        src/external/*.
        src/lexical/*.c
        src/lexical/*.h
        src/helpers/*.c
        src/helpers/*.h)
set(ENDF6_SRC ${ENDF6_SRC_TOP} ${ENDF6_SRC_NESTED})

add_executable(P1___Comp ${ENDF6_SRC})