project(FakeFSW)
cmake_minimum_required(VERSION 3.14)

# We need link-time optimization so everything fits nicely in one binary
# Also some functions can get inlined this way
add_compile_options(-O3 -flto -msse2)

add_library(datatypes datatypes.cpp)

add_library(stub stub.cpp)
target_link_libraries(stub datatypes)

add_library(clock clock.cpp)
target_link_libraries(clock datatypes)

add_library(autocode autocode.cpp)
target_link_libraries(autocode datatypes)

add_library(seq seq.cpp)
target_link_libraries(seq datatypes stub autocode)

add_library(imu imu.cpp)
target_link_libraries(imu datatypes stub)

add_library(sensor sensor.cpp)
target_link_libraries(sensor datatypes stub)

add_library(autonav autonav.cpp)
target_link_libraries(autonav datatypes seq)

add_library(kalman kalman.cpp)
target_link_libraries(kalman datatypes imu sensor)

add_library(ivp ivp.cpp)
target_link_libraries(ivp datatypes kalman sensor)

add_library(pos_ctrl pos_ctrl.cpp)
target_link_libraries(pos_ctrl datatypes ivp kalman autonav sensor autocode)

add_library(att_ctrl att_ctrl.cpp)
target_link_libraries(att_ctrl datatypes pos_ctrl autocode)

add_library(servo_ctrl servo_ctrl.cpp)
target_link_libraries(servo_ctrl datatypes att_ctrl)

add_executable(fsw main.cpp)
target_link_libraries(fsw datatypes att_ctrl servo_ctrl datatypes stub clock)
