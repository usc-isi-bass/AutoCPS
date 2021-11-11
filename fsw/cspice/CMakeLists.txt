project(cspice)
cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CSPICE_SOURCES src/cspice RELATIVE ${PROJECT_SOURCE_DIR} *.c)

file(GLOB_RECURSE CSUPPORT_SOURCES src/csupport RELATIVE ${PROJECT_SOURCE_DIR} *.c)

include_directories(include)

add_library(csupport ${CSUPPORT_SOURCES})

add_library(cspice ${CSPICE_SOURCES})
target_link_libraries(cspice csupport)
