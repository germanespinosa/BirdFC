cmake_minimum_required(VERSION 3.3)

project(BirdFC)
include_directories(src)
include(CMakeFunctions.txt)

add_program(mpu9250
    src/sensors/mpu9250.cpp
    sensors/MPU9250/sensor.cpp)

add_program(gamepad
    src/controls/gamepad.cpp)

add_program(screen
    src/actuators/screen.cpp)

add_program(pca9685
    src/actuators/pca9685.cpp)
