cmake_minimum_required(VERSION 3.2)
project (tk-core)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

add_library(tk-core SHARED ${SOURCES} ${HEADERS})