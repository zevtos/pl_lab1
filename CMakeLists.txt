cmake_minimum_required(VERSION 3.5)
project(image_transform C)

set(CMAKE_C_STANDARD 99)

include_directories(solution/include)

file(GLOB SOURCES "solution/src/*.c")

add_executable(image_transform ${SOURCES}
        solution/include/image_io.h
        solution/src/image_io.c)
