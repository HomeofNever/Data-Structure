cmake_minimum_required(VERSION 3.13)
project(12th)

set(CMAKE_CXX_STANDARD 11)

add_executable(12th main.cpp TimeQueue.h UrgentQueue.h Job.h Job.cpp TimeQueue.cpp UrgentQueue.cpp)