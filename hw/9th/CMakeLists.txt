cmake_minimum_required(VERSION 3.13)
project(9th)

set(CMAKE_CXX_STANDARD 11)

add_executable(9th main.cpp Rope.h Rope_provided.cpp Rope_student.cpp)