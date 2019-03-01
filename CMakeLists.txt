cmake_minimum_required(VERSION 3.3)

project(BirdFC)

include(CMakeFunctions.txt)
add_program(bird
    src/utils.cpp
    src/control.cpp
    src/sensor.cpp
    src/actuator.cpp
    src/pid.cpp
    src/bird.cpp) 

add_test_program (test_bird 
    src/utils.cpp
    src/control.cpp
    src/sensor.cpp
    src/actuator.cpp
    src/pid.cpp
    tests/pid_test.cpp
    tests/sensor_test.cpp
    tests/actuator_test.cpp
    tests/utils_test.cpp )