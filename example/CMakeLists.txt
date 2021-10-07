project(FakeFSW)
cmake_minimum_required(VERSION 3.14)

include_directories("../cspice/include")
find_library(CSPICE NAMES cspice.a PATHS "../cspice/lib")
find_library(CSUPPORT NAMES csupport.a PATHS "../cspice/lib")

add_compile_options(-O3 -flto -msse2)

add_library(datatypes datatypes.cpp)

add_library(imu imu.cpp)
target_link_libraries(imu datatypes)

add_library(stub fsw_stub.cpp)
target_link_libraries(stub imu datatypes)

add_executable(fsw main.cpp)
target_link_libraries(fsw imu datatypes stub)
