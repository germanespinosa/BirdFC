cmake_minimum_required(VERSION 3.3)

project(BirdFC)

include(CMakeFunctions.txt)

add_test_program (test_bird 
    src/sensors/mpu9250.cpp
    tests/pid_test.cpp
    tests/sensor_test.cpp
    tests/actuator_test.cpp
    tests/utils_test.cpp )
    
add_program(mpu9250
    src/sensors/mpu9250.cpp
    sensors/MPU9250/sensor.cpp)

add_program(gamepad
    src/controls/gamepad.cpp)

