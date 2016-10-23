cmake_minimum_required(VERSION 3.2)
project(tk-core)

option(TK_BUILD_SHARED "TK_BUILD_SHARED" ON)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_definitions(-DTK_BUILD_CORE)

set(BUID_MODE STATIC)
if (TK_BUILD_SHARED)
    set(BUILD_MODE SHARED)
    add_definitions(-DTK_SHARED)
endif()

add_library(tk-core ${BUILD_MODE} ${SOURCES} ${HEADERS})
