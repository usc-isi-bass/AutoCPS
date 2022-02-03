project(FakeFSW)
cmake_minimum_required(VERSION 3.14)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

# Try to inline some functions for more binary analysis fun
set(CMAKE_C_FLAGS "-O3 -flto")
set(CMAKE_CXX_FLAGS "-O3 -flto")

add_library(datatypes STATIC datatypes.cpp)
target_link_libraries(datatypes)

add_library(stub STATIC stub.cpp)
target_link_libraries(stub datatypes)

add_library(clock STATIC clock.cpp)
target_link_libraries(clock datatypes)

add_library(autocode STATIC autocode.cpp)
target_link_libraries(autocode datatypes)

add_library(seq STATIC seq.cpp)
target_link_libraries(seq datatypes stub autocode)

add_library(imu STATIC imu.cpp)
target_link_libraries(imu datatypes stub)

add_library(sensor STATIC sensor.cpp)
target_link_libraries(sensor datatypes stub)

add_library(autonav STATIC autonav.cpp)
target_link_libraries(autonav datatypes seq)

add_library(kalman STATIC kalman.cpp)
target_link_libraries(kalman datatypes imu sensor)

add_library(ivp STATIC ivp.cpp)
target_link_libraries(ivp datatypes kalman sensor)

add_library(pos_ctrl STATIC pos_ctrl.cpp)
target_link_libraries(pos_ctrl datatypes ivp kalman autonav sensor autocode)

add_library(att_ctrl STATIC att_ctrl.cpp)
target_link_libraries(att_ctrl datatypes pos_ctrl autocode)

add_library(servo_ctrl STATIC servo_ctrl.cpp)
target_link_libraries(servo_ctrl datatypes att_ctrl)

add_executable(fsw main.cpp)

set_property(TARGET fsw PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

target_link_libraries(fsw -static datatypes pos_ctrl att_ctrl servo_ctrl stub clock)
