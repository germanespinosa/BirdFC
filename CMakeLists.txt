cmake_minimum_required(VERSION 3.3)

project(BirdFC)
include_directories(src)
include(CMakeFunctions.txt)

add_program(mpu9250
    sensors/MPU9250/sensor.cpp)
