cmake_minimum_required(VERSION 3.3)

project(BirdFC)
include_directories(src)
include(CMakeFunctions.txt)

add_test_program (pid_test tests/pid_test.cpp)
add_test_program (sensor_test tests/sensor_test.cpp)
add_test_program (actuator_test tests/actuator_test.cpp)
add_test_program (utils_test tests/utils_test.cpp)

add_program(mpu9250
    src/sensors/mpu9250.cpp
    sensors/MPU9250/sensor.cpp)

add_program(gamepad
    src/controls/gamepad.cpp)

add_program(screen
    src/actuators/screen.cpp)

add_program(pca9685
    src/actuators/pca9685.cpp)
