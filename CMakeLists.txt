cmake_minimum_required(VERSION 3.5)
project(image_transform C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(image_transform ${SOURCES}
        include/image_io.h
        src/image_io.c)
