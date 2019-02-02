cmake_minimum_required(VERSION 3.12)
project(code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(code
        main.cpp
        Schedule.cpp
        Schedule.h ScheduleCollection.cpp ScheduleCollection.h SearchCollection.cpp SearchCollection.h Day.cpp Day.h)
