cmake_minimum_required(VERSION 3.3)

project(BirdFC)
find_library(wiringPi_LIB wiringPi)

include(CMakeFunctions.txt)
add_program(bird
    src/utils.cpp
    src/control.cpp
    src/sensor.cpp
    src/actuator.cpp
    src/pid.cpp
    src/bird.cpp
    src/sensors/mpu9250.cpp
    src/main.cpp)
target_link_libraries(bird ${wiringPi_LIB})

add_test_program (test_bird 
    src/utils.cpp
    src/control.cpp
    src/sensor.cpp
    src/actuator.cpp
    src/pid.cpp
    src/bird.cpp
    src/sensors/mpu9250.cpp
    tests/pid_test.cpp
    tests/sensor_test.cpp
    tests/actuator_test.cpp
    tests/utils_test.cpp )
target_link_libraries(test_bird ${wiringPi_LIB})

add_program(sensor
    src/utils.cpp
    src/control.cpp
    src/sensor.cpp
    src/actuator.cpp
    src/pid.cpp
    src/bird.cpp
    src/sensors/mpu9250.cpp
    sensors/MPU9250/sensor.cpp)
target_link_libraries(sensor ${wiringPi_LIB})
