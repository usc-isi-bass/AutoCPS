project(FakeFSW)
cmake_minimum_required(VERSION 3.19)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

add_executable(fsw
  datatypes.cpp
  stub.cpp
  clock.cpp
  autocode.cpp
  seq.cpp
  imu.cpp
  sensor.cpp
  autonav.cpp
  kalman.cpp
  ivp.cpp
  pos_ctrl.cpp
  att_ctrl.cpp
  servo_ctrl.cpp
  main.cpp)

set_property(TARGET fsw PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
