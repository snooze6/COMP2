cmake_minimum_required(VERSION 3.5)
project(P1___Comp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c definitions/definitions.h external/model/hash.c external/model/hash.h external/model/hash.h)
add_executable(P1___Comp ${SOURCE_FILES})