project(FakeFSW)
cmake_minimum_required(VERSION 3.14)

include_directories("../cspice/include")
find_library(CSPICE NAMES cspice.a PATHS "../cspice/lib")
find_library(CSUPPORT NAMES csupport.a PATHS "../cspice/lib")

# We need link-time optimization so everything fits nicely in one binary
# Also some functions can get inlined this way
add_compile_options(-O3 -flto -msse2)

add_library(datatypes datatypes.cpp)

add_library(stub stub.cpp)
target_link_libraries(stub datatypes)

add_library(pos_ctrl pos_ctrl.cpp)
target_link_libraries(pos_ctrl datatypes stub)

add_library(att_ctrl att_ctrl.cpp)
target_link_libraries(att_ctrl datatypes pos_ctrl)

add_library(servo_ctrl servo_ctrl.cpp)
target_link_libraries(servo_ctrl datatypes att_ctrl)

add_executable(fsw main.cpp)
target_link_libraries(fsw pos_ctrl att_ctrl servo_ctrl datatypes stub)
