cmake_minimum_required(VERSION 3.2)
project(tk-core)

option(TK_BUILD_SHARED "TK_BUILD_SHARED" ON)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

set(BUID_MODE STATIC)
if (TK_BUILD_SHARED)
    set(BUILD_MODE SHARED)
endif()

add_library(tk-core ${BUILD_MODE} ${SOURCES} ${HEADERS})
