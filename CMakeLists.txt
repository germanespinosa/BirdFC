cmake_minimum_required(VERSION 3.3)

project(BirdFC)

include(CMakeFunctions.txt)
add_program(bird
    src/control.cpp
    src/sensor.cpp
    src/actuation.cpp
    src/pid.cpp
    src/bird.cpp) 

add_test_program (test_bird 
    src/control.cpp
    src/sensor.cpp
    src/actuation.cpp
    src/pid.cpp
    tests/pid_test.cpp
    tests/sensor_test.cpp
    tests/configuration_test.cpp
    tests/utils_test.cpp )