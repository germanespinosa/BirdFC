cmake_minimum_required(VERSION 3.3)

project(BirdFC)
include_directories(src)
include(CMakeFunctions.txt)

#add_test_program (pid_test tests/pid_test.cpp)
#add_test_program (sensor_test tests/sensor_test.cpp)
#add_test_program (actuator_test tests/actuator_test.cpp)
#add_test_program (utils_test tests/utils_test.cpp)
#add_test_program (control_test tests/control_test.cpp)
#add_test_program (actuator_std_out_test tests/actuator_std_out_test.cpp)

add_program(mpu9250
    sensors/MPU9250/sensor.cpp)
    
add_program(mpu9250_std_out
    examples/mpu9250_std_out/mpu9250_std_out.cpp)