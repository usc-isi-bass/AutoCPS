project(FakeFSW)
cmake_minimum_required(VERSION 3.14)

# We need link-time optimization so everything fits nicely in one binary
# Also some functions can get inlined this way
add_compile_options(-O3 -flto -msse2)

# We need to build SPICE for some important functions
include("cspice/CMakeLists.txt")
include_directories("cspice/include")

add_library(datatypes datatypes.cpp)
target_link_libraries(datatypes cspice)

add_library(stub stub.cpp)
target_link_libraries(stub datatypes)

add_library(seq seq.cpp)
target_link_libraries(seq stub datatypes)

add_library(imu imu.cpp)
target_link_libraries(imu stub datatypes)

add_library(sensor sensor.cpp)
target_link_libraries(sensor stub datatypes)

add_library(autonav autonav.cpp)
target_link_libraries(autonav seq)

add_library(kalman kalman.cpp)
target_link_libraries(kalman imu sensor)

add_library(ivp ivp.cpp)
target_link_libraries(ivp kalman sensor cspice)

add_library(pos_ctrl pos_ctrl.cpp)
target_link_libraries(pos_ctrl seq ivp kalman autonav sensor)

add_library(att_ctrl att_ctrl.cpp)
target_link_libraries(att_ctrl datatypes pos_ctrl)

add_library(servo_ctrl servo_ctrl.cpp)
target_link_libraries(servo_ctrl datatypes att_ctrl)

add_executable(fsw main.cpp)
target_link_libraries(fsw pos_ctrl att_ctrl servo_ctrl datatypes stub)
