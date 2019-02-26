cmake_minimum_required(VERSION 3.3)

project(BirdFC)

include(CMakeFunctions.txt)
add_program(bird 
    src/bird.cpp) 

add_test_program (pid 
    tests/pid.cpp)